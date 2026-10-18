
#ifndef SENTRY_BASICS
#define SENTRY_BASICS
#include "basics.c"
#endif

static ALWAYS_INLINE void naive_memcpy(void *restrict dst, const void *restrict src, UPTR len)
{
	char *p_dst;
	char *p_src;

	assert(len == (UPTR)len);
	ALWAYS(dst != NULL);
	ALWAYS(src != NULL);
	ALWAYS(len > 0);

	p_dst = (char *)dst;
	p_src = (char *)src;

	while (len != 0) {
		*p_dst = *p_src;
		++p_dst;
		++p_src;
		--len;
	}
}

static ALWAYS_INLINE void naive_memmove(void *dst, const void *src, UPTR nbytes)
{
	if ((UPTR)dst < (UPTR)src) {
		while (nbytes) {
			*(char *)dst = *(char *)src;
			--nbytes;
			dst = (char *)dst + 1;
			src = (char *)src + 1;
		}
	} else {
		dst = (char *)dst + nbytes;
		src = (char *)src + nbytes;
		while (nbytes) {
			dst = (char *)dst - 1;
			src = (char *)src - 1;
			*(char *)dst = *(char *)src;
			--nbytes;
		}
	}
}

static ALWAYS_INLINE UPTR naive_strlen(const char *str)
{
	UPTR res = 0;
	while (*str != '\0') {
		++res;
		++str;
	}
	return res;
}
