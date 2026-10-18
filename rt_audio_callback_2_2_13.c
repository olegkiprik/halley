
#include "rt_audio_callback.c"

GENERATE_rt_audio_callback(s16, s16, 13, 16, 16, 2, 2);
GENERATE_rt_audio_callback(s24, s16, 13, 24, 16, 2, 2);
GENERATE_rt_audio_callback(s32, s16, 13, 32, 16, 2, 2);
GENERATE_rt_audio_callback(f32, s16, 13, 32, 16, 2, 2);
GENERATE_rt_audio_callback(s16, s24, 13, 16, 24, 2, 2);
GENERATE_rt_audio_callback(s24, s24, 13, 24, 24, 2, 2);
GENERATE_rt_audio_callback(s32, s24, 13, 32, 24, 2, 2);
GENERATE_rt_audio_callback(f32, s24, 13, 32, 24, 2, 2);
GENERATE_rt_audio_callback(s16, s32, 13, 16, 32, 2, 2);
GENERATE_rt_audio_callback(s24, s32, 13, 24, 32, 2, 2);
GENERATE_rt_audio_callback(s32, s32, 13, 32, 32, 2, 2);
GENERATE_rt_audio_callback(f32, s32, 13, 32, 32, 2, 2);
GENERATE_rt_audio_callback(s16, f32, 13, 16, 32, 2, 2);
GENERATE_rt_audio_callback(s24, f32, 13, 24, 32, 2, 2);
GENERATE_rt_audio_callback(s32, f32, 13, 32, 32, 2, 2);
GENERATE_rt_audio_callback(f32, f32, 13, 32, 32, 2, 2);
