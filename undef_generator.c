#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define NBYTES_HASH_K 22
#define NBYTES_WORDS_K 23
#define NBYTES_ALIGNMENT (1 << 3)

static unsigned long bench_inserts = 0;
static unsigned long bench_collisions = 0;
static unsigned long bench_perfect_inserts = 0;

static unsigned int rol_32(unsigned int x, unsigned int y)
{
	return x << y | x >> (32 - y);
}

static unsigned int hash1(const char *s, size_t len)
{
	if (len <= 1) {
		return (unsigned int)len ^ (unsigned int)s[0] << 8;
	} else {
		return (unsigned int)len ^ (unsigned int)s[0] << 8 ^ (unsigned int)s[1] << 16;
	}
	return 0;
}

static unsigned int hash2(const char *s, size_t len)
{
	size_t i;
	unsigned int res;

	res = (unsigned int)len;
	res = rol_32(res, 17);

	for (i = 0; i < len; ++i) {
		res ^= s[i];
		res = rol_32(res, 7);
	}

	return res;
}

static unsigned int hash(const char *s, size_t len)
{
	unsigned int res;

	res = hash2(s, len);
	res &= (1u << NBYTES_HASH_K) - 1;
	res /= NBYTES_ALIGNMENT;
	res *= NBYTES_ALIGNMENT;
	return res;
}

static void insert(char *restrict mem, const char *restrict word)
{
	size_t len;
	size_t len_full;
	size_t l;
	size_t i;
	unsigned int h;
	int found;
	int perfect;

	perfect = 1;
	++bench_inserts;

	len = strlen(word);
	len_full = (len / NBYTES_ALIGNMENT + 1) * NBYTES_ALIGNMENT;
	h = hash(word, len);

	while (1 == 1) {
		while (mem[h] != 0) {
			l = strlen(mem + h);
			if (mem[h] != 1 && len == l && 0 == memcmp(mem + h, word, l)) {
				if (perfect) {
					++bench_perfect_inserts;
				}
				return;
			}
			perfect = 0;
			++bench_collisions;
			l = (l / NBYTES_ALIGNMENT + 1) * NBYTES_ALIGNMENT;
			h += l;
		}
		found = 1;
		for (i = 0; i < len_full; ++i) {
			if (mem[h + i] != 0) {
				h += i;
				found = 0;
				break;
			}
		}
		if (found) {
			break;
		}
	}

	memcpy(mem + h, word, len);
}

static void erase(char *restrict mem, const char *restrict word)
{
	size_t len;
	size_t l;
	size_t i;
	unsigned int h;

	len = strlen(word);
	h = hash(word, len);

	while (mem[h] != 0) {
		l = strlen(mem + h);
		if (mem[h] != 1 && len == l && 0 == memcmp(mem + h, word, l)) {
			for (i = 0; i < l; ++i) {
				mem[h + i] = 1;
			}
			return;
		}
		l = (l / NBYTES_ALIGNMENT + 1) * NBYTES_ALIGNMENT;
		h += l;
	}
}

static int parse(FILE *file, char *restrict words, void (*op)(char *mem, const char *word))
{
	char buf[4096];
	char *p;
	int state;
	int r;

	p = buf;
	state = 0;

	while (1 == 1) {
		r = fread_unlocked(p, 1, 1, file);
		if (r != 1) {
			if (state == 1) {
				*p = '\0';
				(*op)(words, buf);
			}
			break;
		}
		if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || *p == '_' || (*p >= '0' && *p <= '9')) {
			if (state == 0) {
				if (*p < '0' || *p > '9') {
					state = 1;
					++p;
				}
			} else if (state == 1) {
				if (p - buf == sizeof buf - 1) {
					return 1;
				}
				++p;
			}
		} else {
			if (state == 0) {

			} else if (state == 1) {
				*p = '\0';
				p = buf;
				state = 0;
				(*op)(words, buf);
			}
		}
	}

	return 0;
}

static volatile FILE *gl_blacklist_file = NULL;

static void sigsegv_handler(int sig)
{
	(void)sig;
	if (gl_blacklist_file != NULL) {
		funlockfile((FILE *)gl_blacklist_file);
		fclose((FILE *)gl_blacklist_file);
	}
	fflush(stdout);
	fprintf(stderr, "Caught SIGSEGV\n");
	_exit(1);
}

static int set_signal_hander(void (*f)(int), int signo)
{
	struct sigaction act;

	memset(&act, 0, sizeof act);
	act.sa_handler = f;

	if (0 != sigaction(signo, &act, NULL)) {
		return 1;
	}

	return 0;
}

int main(int argc, char **argv)
{
	FILE *blacklist_file;
	char *words;
	char *s;
	unsigned int page_size;
	char *last_p;

	if (argc < 2) {
		fprintf(stderr, "Failed %s:%d", __FILE__, __LINE__);
		return 1;
	}

	if (0 != set_signal_hander(sigsegv_handler, SIGSEGV)) {
		fprintf(stderr, "Failed %s:%d", __FILE__, __LINE__);
		return 1;
	}

	page_size = sysconf(_SC_PAGE_SIZE);

	words = mmap(NULL, (1u << NBYTES_WORDS_K) + page_size * 4, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!~(size_t)words) {
		fprintf(stderr, "Failed %s:%d", __FILE__, __LINE__);
		return 1;
	}

	words += page_size * 2;
	mprotect(words, 1u << NBYTES_WORDS_K, PROT_READ | PROT_WRITE);
	madvise(words, 1u << NBYTES_HASH_K, MADV_WILLNEED);

	for (s = words; s - words != 1u << NBYTES_WORDS_K; ++s) {
		*s = 0;
	}

	flockfile(stdin);
	if (0 != parse(stdin, words, insert)) {
		funlockfile(stdin);
		fprintf(stderr, "Failed %s:%d", __FILE__, __LINE__);
		return 1;
	}
	funlockfile(stdin);

	blacklist_file = fopen(argv[1], "r");
	if (blacklist_file == NULL) {
		fprintf(stderr, "Failed %s:%d", __FILE__, __LINE__);
		return 1;
	}

	flockfile(blacklist_file);
	gl_blacklist_file = blacklist_file;

	if (0 != parse(blacklist_file, words, erase)) {
		funlockfile(blacklist_file);
		fclose(blacklist_file);
		fprintf(stderr, "Failed %s:%d", __FILE__, __LINE__);
		return 1;
	}
	funlockfile(blacklist_file);
	fclose(blacklist_file);

	gl_blacklist_file = NULL;
	s = words;
	do {
		if (*s != 0 && *s != 1) {
			printf("#undef %s\n", s);
			do {
				last_p = s;
				++s;
			} while (*s != 0);

			while ((size_t)(s - words) % NBYTES_ALIGNMENT != 0) {
				++s;
			}
		} else {
			s += NBYTES_ALIGNMENT;
		}
	} while (s - words != 1u << NBYTES_WORDS_K);

#if 0
	fprintf(stderr, "inserts:               %30lu\n"
			"perfect inserts:       %30lu\n"
			"collisions:            %30lu\n"
			"\n"
			"%% base memory range:   %lf\n"
			"%% total memory range:  %lf\n"
			"%% perfect              %lf\n"
			"coll/imperf            %lf\n",
		bench_inserts, bench_perfect_inserts, bench_collisions,
		(double)(last_p - words) / (1 << NBYTES_HASH_K) * 100,
		(double)(last_p - words) / (1 << NBYTES_WORDS_K) * 100,
		(double)bench_perfect_inserts / bench_inserts * 100,
		(double)bench_collisions / (bench_inserts - bench_perfect_inserts));
#else
	(void)last_p;
#endif
	return 0;
}

/*
 * Copyright 2026 Oleh Kiprik
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
