#include <assert.h>
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

typedef enum enum_state_ {
	STATE_IDENT,
	STATE_NOT_IDENT,
	STATE_NONE,
} enum_state;

#ifndef RARELY
#define RARELY(x) __builtin_expect_with_probability(x, 0, 0.9)
#endif

#ifndef OFTEN
#define OFTEN(x) __builtin_expect_with_probability(x, 1, 0.9)
#endif

int parse(FILE *file, char *restrict words, void (*op)(char *mem, const char *word))
{
	char buf[4096];
	char *p;
	enum_state state;
	int r;

	p = buf;
	state = STATE_NONE;

	while (1 == 1) {
		r = fread_unlocked(p, 1, 1, file);
		if (RARELY(r != 1)) {
			goto l_finish;
		}

		int az_us = (int)(*p == '_') | ((int)(*p >= 'a') & (int)(*p <= 'z')) | ((int)(*p >= 'A') & (int)(*p <= 'Z'));
		int digit = (int)(*p >= '0') & (int)(*p <= '9');
		int alphanum = az_us | digit;
		int other = 1 ^ alphanum;

		if (state == STATE_IDENT) {
			if (RARELY(other)) {
				*p = '\0';
				p = buf;
				(*op)(words, buf);
			} else {
				if (RARELY(p - buf == sizeof buf - 1)) {
					goto l_failure;
				}
			}
		}

		int ident_curr = az_us & (int)(state == STATE_NONE) | alphanum & (int)(state == STATE_IDENT);

		p += ident_curr;

		state = STATE_NONE &
			    -other |
			(STATE_NOT_IDENT ^ (STATE_NOT_IDENT ^ STATE_IDENT) & -ident_curr) &
			    -alphanum;
	}

l_finish:
	if (state == STATE_IDENT) {
		*p = '\0';
		(*op)(words, buf);
	}
	return 0;
l_failure:
	return 1;
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

	if (0 != parse(blacklist_file, words, erase)) {
		funlockfile(blacklist_file);
		fclose(blacklist_file);
		fprintf(stderr, "Failed %s:%d", __FILE__, __LINE__);
		return 1;
	}
	funlockfile(blacklist_file);
	fclose(blacklist_file);

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
