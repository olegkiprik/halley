
#include "rt_audio_callback.c"

GENERATE_rt_audio_callback(s16, s16, 11, 16, 16, 1, 2);
GENERATE_rt_audio_callback(s24, s16, 11, 24, 16, 1, 2);
GENERATE_rt_audio_callback(s32, s16, 11, 32, 16, 1, 2);
GENERATE_rt_audio_callback(f32, s16, 11, 32, 16, 1, 2);
GENERATE_rt_audio_callback(s16, s24, 11, 16, 24, 1, 2);
GENERATE_rt_audio_callback(s24, s24, 11, 24, 24, 1, 2);
GENERATE_rt_audio_callback(s32, s24, 11, 32, 24, 1, 2);
GENERATE_rt_audio_callback(f32, s24, 11, 32, 24, 1, 2);
GENERATE_rt_audio_callback(s16, s32, 11, 16, 32, 1, 2);
GENERATE_rt_audio_callback(s24, s32, 11, 24, 32, 1, 2);
GENERATE_rt_audio_callback(s32, s32, 11, 32, 32, 1, 2);
GENERATE_rt_audio_callback(f32, s32, 11, 32, 32, 1, 2);
GENERATE_rt_audio_callback(s16, f32, 11, 16, 32, 1, 2);
GENERATE_rt_audio_callback(s24, f32, 11, 24, 32, 1, 2);
GENERATE_rt_audio_callback(s32, f32, 11, 32, 32, 1, 2);
GENERATE_rt_audio_callback(f32, f32, 11, 32, 32, 1, 2);
