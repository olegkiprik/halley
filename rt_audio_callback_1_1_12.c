
#include "rt_audio_callback.c"

GENERATE_rt_audio_callback(s16, s16, 12, 16, 16, 1, 1);
GENERATE_rt_audio_callback(s24, s16, 12, 24, 16, 1, 1);
GENERATE_rt_audio_callback(s32, s16, 12, 32, 16, 1, 1);
GENERATE_rt_audio_callback(f32, s16, 12, 32, 16, 1, 1);
GENERATE_rt_audio_callback(s16, s24, 12, 16, 24, 1, 1);
GENERATE_rt_audio_callback(s24, s24, 12, 24, 24, 1, 1);
GENERATE_rt_audio_callback(s32, s24, 12, 32, 24, 1, 1);
GENERATE_rt_audio_callback(f32, s24, 12, 32, 24, 1, 1);
GENERATE_rt_audio_callback(s16, s32, 12, 16, 32, 1, 1);
GENERATE_rt_audio_callback(s24, s32, 12, 24, 32, 1, 1);
GENERATE_rt_audio_callback(s32, s32, 12, 32, 32, 1, 1);
GENERATE_rt_audio_callback(f32, s32, 12, 32, 32, 1, 1);
GENERATE_rt_audio_callback(s16, f32, 12, 16, 32, 1, 1);
GENERATE_rt_audio_callback(s24, f32, 12, 24, 32, 1, 1);
GENERATE_rt_audio_callback(s32, f32, 12, 32, 32, 1, 1);
GENERATE_rt_audio_callback(f32, f32, 12, 32, 32, 1, 1);
