
#ifndef SENTRY_SYSCALL
#define SENTRY_SYSCALL
#include "syscall.c"
#endif

typedef struct {
	U8 e_ident[16];	 /* Magic number and other info */
	U16 e_type;	 /* Object file type */
	U16 e_machine;	 /* Architecture */
	U32 e_version;	 /* Object file version */
	U64 e_entry;	 /* Entry point virtual address */
	U64 e_phoff;	 /* Program header table file offset */
	U64 e_shoff;	 /* Section header table file offset */
	U32 e_flags;	 /* Processor-specific flags */
	U16 e_ehsize;	 /* ELF header size in bytes */
	U16 e_phentsize; /* Program header table entry size */
	U16 e_phnum;	 /* Program header table entry count */
	U16 e_shentsize; /* Section header table entry size */
	U16 e_shnum;	 /* Section header table entry count */
	U16 e_shstrndx;	 /* Section header string table index */
} Elf64_Ehdr;

typedef struct {
	U32 p_type;   /* Segment type */
	U32 p_flags;  /* Segment flags */
	U64 p_offset; /* Segment file offset */
	U64 p_vaddr;  /* Segment virtual address */
	U64 p_paddr;  /* Segment physical address */
	U64 p_filesz; /* Segment size in file */
	U64 p_memsz;  /* Segment size in memory */
	U64 p_align;  /* Segment alignment */
} Elf64_Phdr;

typedef struct {
	U32 st_name;  /* Symbol name (string tbl index) */
	U8 st_info;   /* Symbol type and binding */
	U8 st_other;  /* Symbol visibility */
	U16 st_shndx; /* Section index */
	U64 st_value; /* Symbol value */
	U64 st_size;  /* Symbol size */
} Elf64_Sym;

typedef struct {
	S64 d_tag;     /* Dynamic entry type */
	U64 d_ptr_val; /* Address or integer value */
} Elf64_Dyn;

/* In-memory ELF helpers */
typedef struct {
	Elf64_Ehdr *eh;
	Elf64_Phdr *ph;
	Elf64_Dyn *dyn;
	U64 base;
	U64 nbucket;
	U64 nchain;
	U32 *buckets;
	U32 *chains;
	U32 *gnu_buckets;
	U32 *gnu_chain;
	U32 gnu_maskwords;
	U32 gnu_shift2;
	U32 *gnu_bloom; /* unsigned long, but effective type is unsigned int */
	U32 gnu_nbucket;
	U32 gnu_symoffset;
	Elf64_Sym *dynsym;
	const char *dynstr;
	void *versym; /* unsigned short */
} mod_t;

static S32 read_all(S32 fd, char *buf, S32 sz)
{
	S32 off;
	S32 n;
	S64 tmpres;

	off = 0;
	while (1) {
		if (off >= sz) {
			break;
		}

		if (0 > sys_read(fd, buf + off, sz - off, &tmpres) || tmpres <= 0) {
			break;
		}

		n = tmpres;
		off += n;
	}

	return off;
}

static const char *elf_strstr(const char *h, const char *n)
{
	const char *p;
	const char *q;

	if (*n == '\0') {
		return h;
	}
	for (; *h != '\0'; ++h) {
		p = h;
		q = n;
		while ((int)(*p != '\0') & (int)(*q != '\0') & (int)(*p == *q)) {
			++p;
			++q;
		}
		if (*q == '\0') {
			return h;
		}
	}
	return NULL;
}

/* parse one /proc/self/maps line; returns 0 on success */
static S32 parse_maps_line(const char *line, U64 *start, char *perms_out, U64 *offset,
			   const char **path_out)
{
	const char *p;
	U64 v;
	S32 i;

	p = line;
	v = 0;

	/* start */
	v = 0;
	while ((int)(*p >= '0') & (int)(*p <= '9') |
	       (int)(*p >= 'a') & (int)(*p <= 'f') |
	       (int)(*p >= 'A') & (int)(*p <= 'F')) {
		v = v << 4 | (U64)(*p <= '9' ? *p - '0' : *p >= 'a' ? 10 + *p - 'a'
								    : 10 + *p - 'A');
		++p;
	}
	if (*p != '-') {
		return -1;
	}
	*start = v;
	++p;

	/* end (skip) */
	while ((int)(*p >= '0') & (int)(*p <= '9') |
	       (int)(*p >= 'a') & (int)(*p <= 'f') |
	       (int)(*p >= 'A') & (int)(*p <= 'F')) {
		++p;
	}
	while (*p == ' ') {
		++p;
	}

	/* perms (4 chars) */
	for (i = 0; i < 4; ++i) {
		if (p[i] == '\0') {
			return -1;
		}
		perms_out[i] = p[i];
	}

	perms_out[4] = 0;
	p += 4;
	while (*p == ' ') {
		++p;
	}

	/* offset */
	v = 0;
	while ((int)(*p >= '0') & (int)(*p <= '9') |
	       (int)(*p >= 'a') & (int)(*p <= 'f') |
	       (int)(*p >= 'A') & (int)(*p <= 'F')) {
		v = v << 4 | (U64)(*p <= '9' ? *p - '0' : *p >= 'a' ? 10 + *p - 'a'
								    : 10 + *p - 'A');
		++p;
	}
	*offset = v;

	/* skip dev */
	while ((int)(*p != '\0') & (int)(*p != ' ')) {
		++p;
	}
	while (*p == ' ') {
		++p;
	}

	/* skip inode */
	while ((int)(*p != '\0') & (int)(*p != ' ')) {
		++p;
	}
	while (*p == ' ') {
		++p;
	}

	/* path (may be empty) */
	*path_out = *p != '\0' ? p : NULL;
	return 0;
}

/* Parse /proc/self/maps to find libc mapping with offset 0 */
static S64 find_libc_base(S32 *restrict cached, void **restrict text_base, const char **restrict cached_name,
			  void **restrict cached_base, const char **restrict soname)
{
	S64 res;
	S32 fd;
	char buf[65536];
	S32 n;
	char *p;
	char *line;
	char save;
	U64 start;
	U64 off;
	char perms[5];
	const char *path;
	void *resp;
	U64 resp_ul;

	if (*cached) {
		*text_base = *cached_base;
		*soname = *cached_name;
		return 0;
	}

	if (0 > (res = sys_openat(AT_FDCWD, "/proc/self/maps", O_RDONLY, &fd))) {
		return res;
	}

	n = read_all(fd, buf, sizeof buf - 1);
	(void)sys_close(fd);

	if (n <= 0) {
		return -1;
	}

	buf[n] = 0;
	p = buf;

	while (*p != '\0') {
		line = p;
		while ((unsigned int)(*p != '\0') & (unsigned int)(*p != '\n')) {
			++p;
		}
		save = *p;
		*p = 0;

		start = 0;
		off = 0;
		path = NULL;
		if (NULL != elf_strstr(line, "libc")) {
			if (0 == parse_maps_line(line, &start, perms, &off, &path) &&
			    ((unsigned int)(path != NULL) & (unsigned int)(off == 0))) {
				resp_ul = start;
				asm volatile("mov %1, %0" : "=r"(resp) : "r"(resp_ul) : "memory");
				*text_base = resp;
				*soname = path;
				*cached = 1;
				*cached_base = *text_base;
				*cached_name = *soname;
				*p = save;
				return 0;
			}
		}

		*p = save;
		if (*p != '\0') {
			++p;
		}
	}
	return -1;
}

/* helper: turn a DT_* pointer/offset into an absolute VA */
static void *dyn_ptr(void *base, U64 lo, U64 hi, U64 p)
{
	U64 res_ul;
	void *res;

	res_ul = p;
	/* if it's not already inside this module's mapped range, treat as offset */
	if ((int)(res_ul < lo) | (int)(res_ul >= hi)) {
		res_ul += (U64)base;
	}
	asm volatile("mov %1, %0" : "=r"(res) : "r"(res_ul) : "memory");
	return res;
}

#if defined(DT_STRTAB) || defined(DT_SYMTAB) || defined(DT_HASH) || defined(DT_GNU_HASH) || defined(DT_VERSYM)
#error "!"
#endif

#define DT_STRTAB 5	       /* Address of string table */
#define DT_SYMTAB 6	       /* Address of symbol table */
#define DT_HASH 4	       /* Address of symbol hash table */
#define DT_GNU_HASH 0x6ffffef5 /* GNU-style hash table.  */
#define DT_VERSYM \
	0x6ffffff0 /* The versioning entry types.  The next are defined as part of the GNU extension.  */

static S32 mod_init(mod_t *restrict m, void *restrict base)
{
	const U64 dt_NULL = 0;	  /* Marks end of dynamic section */
	const U64 pt_LOAD = 1;	  /* Loadable program segment */
	const U64 pt_DYNAMIC = 2; /* Dynamic linking information */
	U32 *h;
	U32 *gh;
	U64 lo;
	U64 hi;
	U64 seg_lo;
	U64 seg_hi;
	void *dyn_addr;
	S32 i;

	m->base = (U64)base;
	m->eh = (Elf64_Ehdr *)base;
	if (RARELY((int)(m->eh->e_ident[0] != 0x7f) | (int)(m->eh->e_ident[1] != 'E') |
		   (int)(m->eh->e_ident[2] != 'L') | (int)(m->eh->e_ident[3] != 'F'))) {
		return -1;
	}

	m->ph = (Elf64_Phdr *)((char *)base + m->eh->e_phoff);

	lo = ~0UL;
	hi = 0;
	for (i = 0; i < m->eh->e_phnum; ++i) {
		Elf64_Phdr *ph = &m->ph[i];
		if (ph->p_type == pt_LOAD) {
			seg_lo = (U64)base + ph->p_vaddr;
			seg_hi = (U64)seg_lo + ph->p_memsz;
			if (seg_lo < lo) {
				lo = seg_lo;
			}
			if (seg_hi > hi) {
				hi = seg_hi;
			}
		}
	}

	m->dyn = NULL;
	for (i = 0; i < m->eh->e_phnum; ++i) {
		if (m->ph[i].p_type == pt_DYNAMIC) {
			dyn_addr = (char *)base + m->ph[i].p_vaddr;
			if ((int)((U64)dyn_addr < lo) |
			    (int)((U64)dyn_addr + sizeof(Elf64_Dyn) > hi)) {
				return -1;
			}
			m->dyn = (Elf64_Dyn *)dyn_addr;
			break;
		}
	}
	if (RARELY(!m->dyn)) {
		return -1;
	}

	for (Elf64_Dyn *d = m->dyn; d->d_tag != dt_NULL; ++d) {
		switch (d->d_tag) {
		case DT_STRTAB:
			m->dynstr = (const char *)dyn_ptr(base, lo, hi, d->d_ptr_val);
			break;
		case DT_SYMTAB:
			m->dynsym = (Elf64_Sym *)dyn_ptr(base, lo, hi, d->d_ptr_val);
			break;
		case DT_HASH:
			h = (U32 *)dyn_ptr(base, lo, hi, d->d_ptr_val);
			m->nbucket = h[0];
			m->nchain = h[1];
			m->buckets = h + 2;
			m->chains = h + 2 + m->nbucket;
			break;
		case DT_GNU_HASH:
			gh = (U32 *)dyn_ptr(base, lo, hi, d->d_ptr_val);
			m->gnu_nbucket = gh[0];
			m->gnu_symoffset = gh[1];
			m->gnu_maskwords = gh[2];
			m->gnu_shift2 = gh[3];
			m->gnu_bloom = gh + 4;
			m->gnu_buckets = m->gnu_bloom + 2ull * m->gnu_maskwords;
			m->gnu_chain = m->gnu_buckets + m->gnu_nbucket;
			break;
		case DT_VERSYM:
			m->versym = dyn_ptr(base, lo, hi, d->d_ptr_val);
			break;
		default:
			break;
		}
	}

	return (U64)(m->dynsym) & (U64)(m->dynstr) ? 0 : -1;
}

#undef DT_STRTAB
#undef DT_SYMTAB
#undef DT_HASH
#undef DT_GNU_HASH
#undef DT_VERSYM

static U32 gnu_hash_str(const char *s)
{
	U32 h;
	U8 c;

	h = 5381;

	while (1 == 1) {
		c = *s;
		++s;
		if (c == 0) {
			break;
		}
		h = (h * 33) + c;
	}

	return h;
}

static S32 naive_strcmp(const char *a, const char *b)
{
	while ((int)(*a != '\0') & (int)(*a == *b)) {
		++a;
		++b;
	}
	return (char)*a - (char)*b;
}

/* GNU hash lookup */
static Elf64_Sym *lookup_gnu(mod_t *restrict m, const char *restrict name)
{
	U32 h;
	U64 bloom_idx;
	U64 bitmask;
	U64 tmp;
	U32 idx;
	U32 hv;
	Elf64_Sym *sym;

	if (m->gnu_buckets == NULL) {
		return NULL;
	}

	h = gnu_hash_str(name);
	bloom_idx = h / (sizeof(S64) * 8) & m->gnu_maskwords - 1;
	bitmask = 1ull << h % (sizeof(S64) * 8) | 1ull << (h >> m->gnu_shift2) % (sizeof(S64) * 8);

	tmp = m->gnu_bloom[bloom_idx * 2 + 1];
	tmp <<= 32;
	tmp |= m->gnu_bloom[bloom_idx * 2];

	if ((tmp & bitmask) != bitmask) {
		return NULL;
	}

	idx = m->gnu_buckets[m->gnu_nbucket == 0 ? 0 : h % m->gnu_nbucket];
	if (!idx) {
		return NULL;
	}

	while (1 == 1) {
		hv = m->gnu_chain[idx - m->gnu_symoffset];
		if ((hv | 1u) == (h | 1u)) {
			sym = m->dynsym + idx;
			if (sym->st_name != 0 && 0 == naive_strcmp(m->dynstr + sym->st_name, name)) {
				return sym;
			}
		}
		if (hv & 1u) {
			break;
		}
		++idx;
	}
	return NULL;
}

static U32 sysv_hash(const char *s)
{
	U32 h;
	U32 g;

	h = 0;
	while (*s != '\0') {
		h = (h << 4) + (U8)*s;
		++s;
		g = h & 0xF0000000U;
		if (g != 0) {
			h ^= g >> 24;
		}
		h &= ~g;
	}
	return h;
}

/* SysV hash lookup */
static Elf64_Sym *lookup_sysv(mod_t *restrict m, const char *restrict name)
{
	U32 i;
	U32 h;
	Elf64_Sym *sym;

	if (!m->buckets) {
		return NULL;
	}

	h = sysv_hash(name);
	for (i = m->buckets[m->nbucket == 0 ? 0 : h % m->nbucket]; i != 0; i = m->chains[i]) {
		sym = &m->dynsym[i];
		if (sym->st_name != 0 && 0 == naive_strcmp(m->dynstr + sym->st_name, name)) {
			return sym;
		}
	}
	return NULL;
}

static void *resolve_sym(mod_t *restrict m, const char *restrict name)
{
	Elf64_Sym *s;
	const U64 stt_GNU_IFUNC = 10; /* Symbol is indirect code object */
	const U64 stt_FUNC = 2;	      /* Symbol is a code object */
	void *res;
	U64 res_ul;

	s = lookup_gnu(m, name);
	if (s == NULL) {
		s = lookup_sysv(m, name);
	}

	if (RARELY(s == NULL)) {
		return NULL;
	}

	if (RARELY((U32)((s->st_info & 0xF) != stt_FUNC) &
		   (U32)((s->st_info & 0xF) != stt_GNU_IFUNC))) {
		return NULL;
	}

	res_ul = m->base + s->st_value;
	asm volatile("mov %1, %0" : "=r"(res) : "r"(res_ul) : "memory");
	return res;
}

extern void *gl_interp_base;

static ALWAYS_INLINE int submain(void);

#ifndef SENTRY_FOREIGN_DLOPEN
#define SENTRY_FOREIGN_DLOPEN
#include "foreign_dlopen.c"
#endif

/* MUST ensure that stack is 16 byte aligned for calls to external functions */
/* especially ones with variadic arguments. We do this via the elf_fdlentry.S wrapper */
void fdl_entry_impl(void)
{
	S32 cached;
	void *text_base;
	const char *cached_name;
	void *cached_base;
	const char *soname;

	void *tmp_dlopen;
	void *tmp_dlsym;
	void *tmp_dlclose;

	S32 exit_status;

	mod_t M;
	char *p;
	char *e;

	cached = 0;
	exit_status = 0;
	text_base = NULL;
	cached_name = NULL;
	cached_base = NULL;
	soname = NULL;

	if (0 > find_libc_base(&cached, &text_base, &cached_name, &cached_base, &soname)) {
		if (gl_interp_base != 0) {
			text_base = gl_interp_base;
		} else {
			goto l_exit_failure;
		}
	}

	p = (void *)&M;
	e = p + sizeof M;
	while (p < e) {
		*p = 0;
		++p;
	}

	if (RARELY(mod_init(&M, text_base) < 0)) {
		goto l_exit_failure;
	}

	/* glibc: prefer __libc_dlopen_mode; fallback to dlopen/dlsym */

	tmp_dlopen = resolve_sym(&M, "__libc_dlopen_mode");
	if (tmp_dlopen == NULL) {
		tmp_dlopen = resolve_sym(&M, "dlopen");
	}

	tmp_dlsym = resolve_sym(&M, "dlsym");
	tmp_dlclose = resolve_sym(&M, "dlclose");

	if ((int)!tmp_dlopen | (int)!tmp_dlsym | (int)!tmp_dlclose) {
		goto l_exit_failure;
	}

	my_dlopen = tmp_dlopen;
	my_dlsym = tmp_dlsym;
	my_dlclose = tmp_dlclose;

l_exit:
	/* X11 window becomes zombie with simple 'exit' */
	sys_exit_group(exit_status == 0 ? submain() : exit_status);

l_exit_failure:
	exit_status = 1;
	goto l_exit;
}

/* heavily modified foreign-dlopen */

/*
 * MIT License
 *
 * Copyright (c) 2018 Mikhail Ilyin
 * Copyright (c) 2020 Paul Sokolovsky
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
