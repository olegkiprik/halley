
#include <bits/types/FILE.h>
#include <dirent.h>
#include <dlfcn.h>
#include <endian.h>
#include <errno.h>
#include <fcntl.h>
#include <float.h>
#include <limits.h>
#include <linux/kd.h>
#include <poll.h>
#include <pthread.h>
#include <sched.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/eventfd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

#if !defined(CLOCK_REALTIME)
#define CLOCK_REALTIME 0
#endif _

#if !defined(CLOCK_MONOTONIC)
#define CLOCK_MONOTONIC 1
#endif _

struct timezone;

static void *priv_extra_naive_memcpy(void *restrict dst, const void *src, size_t nbytes)
{
	void *res = dst;
	while (nbytes) {
		*(char *)dst = *(char *)src;
		--nbytes;
		dst = (char *)dst + 1;
		src = (char *)src + 1;
	}
	return res;
}

static void *priv_extra_naive_memmove(void *dst, const void *src, size_t nbytes)
{
	void *res = dst;
	if ((size_t)dst < (size_t)src) {
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
	return res;
}

static char *priv_extra_naive_strncpy(char *restrict dst, const char *restrict src, size_t n)
{
	char *res;
	res = dst;

	if (n == 0) {
		return res;
	}

	while (1 == 1) {
		--n;
		*dst = *src;

		if (n == 0) {
			return res;
		}

		if (*src != '\0') {
			++src;
		}
		++dst;
	}

	return res;
}

static size_t priv_extra_naive_strlen(const char *str)
{
	size_t res = 0;
	while (*str) {
		++res;
		++str;
	}
	return res;
}

static const char *priv_extra_naive_strstr(const char *haystack, const char *needle)
{
	size_t h_nbytes;
	size_t n_nbytes;

	h_nbytes = priv_extra_naive_strlen(haystack);
	n_nbytes = priv_extra_naive_strlen(needle);

	if (n_nbytes == 0) {
		return haystack;
	}

	if (h_nbytes < n_nbytes) {
		return NULL;
	}

	for (size_t i = 0; i < h_nbytes - n_nbytes + 1; ++i) {
		int found = 1;
		for (size_t j = 0; j < n_nbytes; ++j) {
			if (haystack[i + j] != needle[j]) {
				found = 0;
			}
		}
		if (found) {
			return haystack + i;
		}
	}

	return NULL;
}

#ifndef SENTRY_FOREIGN_DLOPEN
#define SENTRY_FOREIGN_DLOPEN
#include "foreign_dlopen.c"
#endif

void (*my_pthread_attr_init)(void);
void (*my_pthread_attr_destroy)(void);
void (*my_pthread_cond_init)(void);
void (*my_pthread_cond_signal)(void);
void (*my_pthread_cond_wait)(void);
void (*my_pthread_cond_destroy)(void);
void (*my_pthread_create)(void);
void (*my_pthread_attr_setschedpolicy)(void);
void (*my_pthread_attr_setstacksize)(void);
void (*my_pthread_mutex_lock)(void);
void (*my_pthread_mutex_try_lock)(void);
void (*my_pthread_mutex_unlock)(void);
void (*my_pthread_mutex_init)(void);
void (*my_pthread_mutex_destroy)(void);
void (*my_pthread_join)(void);
int (*my_pthread_attr_setschedparam)(pthread_attr_t *restrict, const struct sched_param *restrict);
int (*my_pthread_attr_getschedparam)(const pthread_attr_t *restrict, struct sched_param *restrict);
int (*my_pthread_attr_setinheritsched)(pthread_attr_t *, int);

int (*my_poll)(struct pollfd *, nfds_t, int);
ssize_t (*my_read)(int, void *, size_t);
ssize_t (*my_write)(int, const void *, size_t);
int (*my_clock_gettime)(clockid_t, struct timespec *);
int (*my_pipe)(int *);
int (*my_fcntl)(int, int, ...);
long (*my_strtol)(const char *restrict, char **restrict, int);
double (*my_atof)(const char *);
int (*my_close)(int);
int (*my_eventfd)(unsigned int, int);
int (*my_sched_getscheduler)(int);
int (*my_sched_get_priority_max)(int);
int (*my_sched_get_priority_min)(int);
int (*my_fileno)(FILE *);
int (*my_strncmp)(const char *a, const char *b, size_t n);
int (*my_vsnprintf)(char *restrict, size_t, const char *restrict, __builtin_va_list);
int (*my_snprintf)(char *restrict, size_t, const char *restrict, ...);
void *(*my_memset)(void *, int, size_t);
int *(*my_errno_location)(void);

#define dlopen(filename, flags) (*(void *(*)(const char *, int))my_dlopen)(filename, flags)
#define dlsym(handle, symbol) (*(void *(*)(void *restrict, const char *restrict))my_dlsym)(handle, symbol)
#define dlclose(handle) (*(int (*)(void *))my_dlclose)(handle)

#define pthread_join(thread, retval) (*(int (*)(pthread_t, void **))my_pthread_join)(thread, retval)
#define pthread_mutex_lock(mutex) (*(int (*)(void *))my_pthread_mutex_lock)(mutex)
#define pthread_mutex_try_lock(mutex) (*(int (*)(void *))my_pthread_mutex_try_lock)(mutex)
#define pthread_mutex_unlock(mutex) (*(int (*)(void *))my_pthread_mutex_unlock)(mutex)
#define pthread_mutex_init(mutex, mutexattr) \
	(*(int (*)(void *, const void *))my_pthread_mutex_init)(mutex, mutexattr)
#define pthread_mutex_destroy(mutex) (*(int (*)(void *))my_pthread_mutex_destroy)(mutex)
#define pthread_attr_init(attr) (*(int (*)(void *))my_pthread_attr_init)(attr)
#define pthread_attr_destroy(attr) (*(int (*)(void *))my_pthread_attr_destroy)(attr)
#define pthread_cond_init(cond, cond_attr) (*(int (*)(void *, void *))my_pthread_cond_init)(cond, cond_attr)
#define pthread_cond_signal(cond) (*(int (*)(void *))my_pthread_cond_signal)(cond)
#define pthread_cond_wait(cond, mutex) (*(int (*)(void *, void *))my_pthread_cond_wait)(cond, mutex)
#define pthread_cond_destroy(cond) (*(int (*)(void *))my_pthread_cond_destroy)(cond)
#define pthread_create(thread, attr, start_routine, arg)                                             \
	(*(int (*)(void *, const void *, void *(*)(void *), void *))my_pthread_create)(thread, attr, \
										       start_routine, arg)
#define pthread_attr_setschedpolicy(attr, policy) \
	(*(int (*)(pthread_attr_t *, int))my_pthread_attr_setschedpolicy)(attr, policy)
#define pthread_attr_setstacksize(attr, stacksize) \
	(*(int (*)(pthread_attr_t *, size_t))my_pthread_attr_setstacksize)(attr, stacksize)
#define pthread_attr_getschedparam(x, y) (*my_pthread_attr_getschedparam)(x, y)
#define pthread_attr_setschedparam(x, y) (*my_pthread_attr_setschedparam)(x, y)
#define pthread_attr_setinheritsched(x, y) (*my_pthread_attr_setinheritsched)(x, y)

#if 1
static void *priv_wrapped_malloc(size_t nbytes);
static void *priv_wrapped_realloc(void *oldptr, size_t nbytes);
static void priv_wrapped_free(void *ptr);
#endif

#define malloc(x) priv_wrapped_malloc((x))
#define realloc(x, y) priv_wrapped_realloc((x), (y))
#define free(x) priv_wrapped_free((x))
#define close(x) (*my_close)((x))
#define eventfd(x, y) (*my_eventfd)((x), (y))
#define poll(x, y, z) (*my_poll)((x), (y), (z))
#define read(x, y, z) (*my_read)(x, y, z)
#define write(x, y, z) (*my_write)(x, y, z)
#define sched_getscheduler(x) (*my_sched_getscheduler)(x)
#define sched_get_priority_min(x) (*my_sched_get_priority_min)(x)
#define sched_get_priority_max(x) (*my_sched_get_priority_max)(x)
#define clock_gettime(x, y) (*my_clock_gettime)(x, y)
#define fileno(x) (*my_fileno)(x)
#define vsnprintf(x, y, z, w) (*my_vsnprintf)(x, y, z, w)
#define strstr(x, y) priv_extra_naive_strstr(x, y)
#define pipe(x) (*my_pipe)(x)
#define fcntl(x, y, z) (*my_fcntl)(x, y, z)
#define strtol(x, y, z) (*my_strtol)(x, y, z)
#define atof(x) (*my_atof)(x)
#define strncpy(x, y, z) priv_extra_naive_strncpy(x, y, z)
#ifdef errno
#undef errno
#endif
#define errno (*(*my_errno_location)())
#ifndef assert
#define assert(x)
#endif
#define memset(x, y, z) (*my_memset)((x), (y), (z))
#define memmove(x, y, z) priv_extra_naive_memmove(x, y, z)
#define strlen(x) priv_extra_naive_strlen(x)
#define memcpy(x, y, z) priv_extra_naive_memcpy((x), (y), (z))
#define strncmp(x, y, z) (*my_strncmp)(x, y, z)

#define MINIAUDIO_IMPLEMENTATION
#define MA_ENABLE_ONLY_SPECIFIC_BACKENDS
#define MA_ENABLE_ALSA
#define MA_NO_DECODING
#define MA_NO_ENCODING
#define MA_NO_RESOURCE_MANAGER
#define MA_NO_NODE_GRAPH
#define MA_NO_ENGINE
#define MA_NO_WAV
#define MA_NO_FLAC
#define MA_NO_MP3
#define MA_NO_GENERATION
#define MA_API static
#if 0
#define MA_NO_SSE
#define MA_NO_SSE2
#define MA_NO_AVX
#define MA_NO_AVX2
#define MA_NO_NEON
#endif
#include "miniaudio.h"
#undef MINIAUDIO_IMPLEMENTATION
#undef MA_ENABLE_ONLY_SPECIFIC_BACKENDS
#undef MA_ENABLE_ALSA
#undef MA_NO_DECODING
#undef MA_NO_ENCODING
#undef MA_NO_RESOURCE_MANAGER
#undef MA_NO_NODE_GRAPH
#undef MA_NO_ENGINE
#undef MA_NO_WAV
#undef MA_NO_FLAC
#undef MA_NO_MP3
#undef MA_NO_GENERATION
#undef MA_API

#define XDL_IMPLEMENTATION
#include "xdl.h"
#undef XDL_IMPLEMENTATION

#define RGFW_PRINTF_3(x, x1, x2, x3) (*my_printf)(x, x1, x2, x3)
#define RGFW_PRINTF_0(x) (*my_printf)(x)
#define RGFW_SNPRINTF_5(x, y, z, x1, x2, x3, x4, x5) (*my_snprintf)(x, y, z, x1, x2, x3, x4, x5)
#define RGFW_SNPRINTF_1(x, y, z, x1) (*my_snprintf)(x, y, z, x1)
#define RGFW_OPENGL
#define RGFW_USE_XDL
#define RGFW_ALLOC_DROPFILES
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#if 0
#define RGFW_DEBUG
#endif
#define GL_SILENCE_DEPRECATION
#define RGFW_API static
#include "rgfw.h"
#undef RGFW_OPENGL
#undef RGFW_USE_XDL
#undef RGFW_ALLOC_DROPFILES
#undef RGFW_IMPLEMENTATION
#undef RGFW_PRINT_ERRORS
#undef RGFW_DEBUG
#undef GL_SILENCE_DEPRECATION
#undef RGFW_PRINTF_3
#undef RGFW_PRINTF_0
#undef RGFW_SNPRINTF_5
#undef RGFW_SNPRINTF_1

#include <GL/gl.h>

#define DO_NOT_BLACKLIST
