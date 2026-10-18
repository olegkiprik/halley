
#ifndef SENTRY_BASICS_MACROS
#define SENTRY_BASICS_MACROS
#include "basics_macros.c"
#endif

#define MAX_K 13
#define REQUESTED_PLAYBACK_NR_CHANNELS 2

struct isolated_audio_thread_data_ {
	char padding0[DESTRUCTIVE_INTERFERENCE_NBYTES];
	ATOMIC U8 data; /* 1,2,3 active pitch shift, 0 apply window function on input fft, 7 callback on */
	char padding1[DESTRUCTIVE_INTERFERENCE_NBYTES];
};

struct isolated_audio_vertices_ {
	char padding0[DESTRUCTIVE_INTERFERENCE_NBYTES];
	F32 time[(1uLL << MAX_K) * 2];
	F32 freq[(1uLL << MAX_K) * 2];
	F32 phase[(1uLL << MAX_K) * 2];
	char padding1[DESTRUCTIVE_INTERFERENCE_NBYTES];
};
