
#ifndef SENTRY_BASICS_MACROS
#define SENTRY_BASICS_MACROS
#include "basics_macros.c"
#endif

#ifndef SENTRY_COMMON_AUDIO
#define SENTRY_COMMON_AUDIO
#include "common_audio.c"
#endif

#ifndef SENTRY_NAIVE
#define SENTRY_NAIVE
#include "naive.c"
#endif

#ifndef SENTRY_NAIVE_MATH
#define SENTRY_NAIVE_MATH
#include "naive_math.c"
#endif

typedef struct ma_device ma_device;
typedef U32 ma_uint32;

STATIC_ASSERT(REQUESTED_PLAYBACK_NR_CHANNELS <= 2);
extern OPTIONAL_ALIGNAS(SIMD_NBYTES) F32 fft_buffer_original[(1uLL << MAX_K) * 2];  /* soa 2 channels */
extern OPTIONAL_ALIGNAS(SIMD_NBYTES) F32 fft_buffer_processed[(1uLL << MAX_K) * 2]; /* soa 2 channels */
extern OPTIONAL_ALIGNAS(SIMD_NBYTES) F32 buffer_for_visualization[1uLL << MAX_K];
extern U32 fft_phase_frames[2]; /* 2 channels */
extern union pthread_mutex_t vert_mutex;

extern struct isolated_audio_vertices_ audio_vert;
extern struct isolated_audio_thread_data_ audio_thread_data;

extern void (*my_pthread_mutex_try_lock)(void);
extern void (*my_pthread_mutex_unlock)(void);

#if 0
#define DEBUG_TEST_AUDIO_OUTPUT
#endif
extern int tmpphase;

void fft_f32_outofplace_10_impl(F32 *restrict dstri,
				F32 *restrict srcri,
				BOOL_IN rev);
void fft_f32_outofplace_11_impl(F32 *restrict dstri,
				F32 *restrict srcri,
				BOOL_IN rev);
void fft_f32_outofplace_12_impl(F32 *restrict dstri,
				F32 *restrict srcri,
				BOOL_IN rev);
void fft_f32_outofplace_13_impl(F32 *restrict dstri,
				F32 *restrict srcri,
				BOOL_IN rev);

static ALWAYS_INLINE void fft_f32_outofplace(F32 *restrict dstri,
					     F32 *restrict srcri,
					     U8_IN k,
					     BOOL_IN rev)
{
	switch (k) {
	case 10:
		fft_f32_outofplace_10_impl(dstri, srcri, rev);
		break;
	case 11:
		fft_f32_outofplace_11_impl(dstri, srcri, rev);
		break;
	case 12:
		fft_f32_outofplace_12_impl(dstri, srcri, rev);
		break;
	case 13:
		fft_f32_outofplace_13_impl(dstri, srcri, rev);
		break;
	default:
		NEVER(0);
		break;
	}
}

static ALWAYS_INLINE void audio_process(void *p_output, const void *p_input, UPTR o_stride_bytes, UPTR i_stride_bytes, U32 o_duplication, U32 frame_count_ma, BOOL_IN do_visualize,
					U8 callbackdata,
					U32 fft_k, F32 *p_samples_ri, F32 *p_dft_ri, F32 *p_invsamples_ri, F32 *p_tmp_inv_samples, F32 *p_extended_dft, F32 *p_fft_buffer_original, F32 *p_fft_buffer_processed, U32 *p_fft_phase_frames,
					UPTR o_sizeof,
					F32 (*load)(const void *), F32 (*load_back)(const void *), void (*store)(void *, F32))
{

#if 0
	OPTIONAL_ALIGNAS(SIMD_NBYTES)
	F32 samples_ri[(1uLL << FFT_K) * 2];

	OPTIONAL_ALIGNAS(SIMD_NBYTES)
	F32 dft_ri[(1uLL << FFT_K) * 2];

	OPTIONAL_ALIGNAS(SIMD_NBYTES)
	F32 invsamples_ri[(1uLL << FFT_K) * 2];
#endif

	U32 nn = 1uLL << fft_k;
	U32 nn4 = nn / 4;

	for (U32 i = 0; i < nn; ++i) {
		p_samples_ri[i * 2 + 1] = 0;
	}

	void *p_output_iter = p_output;
	const void *p_input_iter = p_input;
	U32 frame_count_iter = frame_count_ma;
	F32 *playback_iter;
	F32 *capture_iter;

	while (*p_fft_phase_frames % nn4 + frame_count_iter >= nn4) {
		U32 nr_curr_frames = nn4 - *p_fft_phase_frames % nn4;

		playback_iter = p_fft_buffer_processed + (*p_fft_phase_frames / nn4 + 2) % 3 * nn4 + *p_fft_phase_frames % nn4;
		capture_iter = p_fft_buffer_original + nn4 + (*p_fft_phase_frames / nn4 + 2) % 3 * nn4 + *p_fft_phase_frames % nn4;

		for (U32 i = 0; i < nr_curr_frames; ++i) {
			capture_iter[i] = (*load)((const char *)p_input_iter + i * i_stride_bytes);
		}
		for (U32 i = 0; i < nr_curr_frames; ++i) {
			for (U32 j = 0; j < o_duplication; ++j) {
				(*store)((char *)p_output_iter + i * o_stride_bytes + j * o_sizeof, min_f32(max_f32(playback_iter[i], -1), 1));
			}
		}

		if (do_visualize) {
			naive_memmove(buffer_for_visualization, buffer_for_visualization + nr_curr_frames, (ARRAY_LENGTH(buffer_for_visualization) - nr_curr_frames) * sizeof *buffer_for_visualization);
			for (U32 i = 0; i < nr_curr_frames; ++i) {
				buffer_for_visualization[ARRAY_LENGTH(buffer_for_visualization) + i - nr_curr_frames] =
				    (*load_back)((char *)p_output_iter + i * o_stride_bytes);
			}
		}

		p_output_iter = (char *)p_output_iter + nr_curr_frames * o_stride_bytes;
		p_input_iter = (const char *)p_input_iter + nr_curr_frames * i_stride_bytes;
		frame_count_iter -= nr_curr_frames;

		U32 prev_phase = *p_fft_phase_frames / nn4;

		*p_fft_phase_frames += nr_curr_frames;
		*p_fft_phase_frames %= nn4 * 3;

		if (*p_fft_phase_frames / nn4 == 1 && prev_phase == 0) {
			for (U32 i = 0; i < nn; ++i) {
				p_samples_ri[i * 2 + 0] = p_fft_buffer_original[i];
			}

			if (callbackdata & 1) {
				for (U32 i = 0; i < nn4; ++i) {
					p_samples_ri[i * 2 + 0] *= (naive_sin_f32((F32)i / nn4 * M_PIf + M_PIf * 2 - M_PI_2f, 7) + 1) / 2;
				}
				for (U32 i = 0; i < nn4; ++i) {
					p_samples_ri[(i + nn4 * 3) * 2 + 0] -= p_samples_ri[(i + nn4 * 3) * 2 + 0] * (naive_sin_f32((F32)i / nn4 * M_PIf + M_PIf * 2 - M_PI_2f, 7) + 1) / 2;
				}
			}
#if 0
			fft_k_outofplace(p_dft_ri, samples_ri, 0);
#endif
			fft_f32_outofplace(p_dft_ri, p_samples_ri, fft_k, 0);

			/* including! */
			U32 n = (1uLL << fft_k) / 2;

			U8 do_shift = ((7 << 1) & callbackdata) >> 1;

			switch (do_shift) {
			case 1: {
				for (U32 i = 0; i < n / 3; ++i) {
					p_dft_ri[i * 2 + 0] = p_dft_ri[(i * 3 + 0) * 2 + 0] + p_dft_ri[(i * 3 + 1) * 2 + 0] + p_dft_ri[(i * 3 + 2) * 2 + 0];
					p_dft_ri[i * 2 + 1] = p_dft_ri[(i * 3 + 0) * 2 + 1] + p_dft_ri[(i * 3 + 1) * 2 + 1] + p_dft_ri[(i * 3 + 2) * 2 + 1];
				}
				for (U32 i = n / 3; i <= n; ++i) {
					p_dft_ri[i * 2 + 0] = 0;
					p_dft_ri[i * 2 + 1] = 0;
				}
				break;
			}
			case 2: {
				for (U32 i = 0; i < n / 2; ++i) {
					p_dft_ri[i * 2 + 0] = p_dft_ri[(i * 2 + 0) * 2 + 0] + p_dft_ri[(i * 2 + 1) * 2 + 0];
					p_dft_ri[i * 2 + 1] = p_dft_ri[(i * 2 + 0) * 2 + 1] + p_dft_ri[(i * 2 + 1) * 2 + 1];
				}
				for (U32 i = n / 2; i <= n; ++i) {
					p_dft_ri[i * 2 + 0] = 0;
					p_dft_ri[i * 2 + 1] = 0;
				}
				break;
			}
			case 3: {
				for (U32 i = 0; i < n; ++i) {
					p_extended_dft[(i * 2 + 0) * 2 + 0] = p_dft_ri[i * 2 + 0];
					p_extended_dft[(i * 2 + 1) * 2 + 0] = p_dft_ri[i * 2 + 0];
					p_extended_dft[(i * 2 + 0) * 2 + 1] = p_dft_ri[i * 2 + 1];
					p_extended_dft[(i * 2 + 1) * 2 + 1] = p_dft_ri[i * 2 + 1];
				}
				for (U32 i = 0; i < n / 3 * 2; ++i) {
					p_dft_ri[i * 2 + 0] = p_extended_dft[(i * 3 + 0) * 2 + 0] + p_extended_dft[(i * 3 + 1) * 2 + 0] + p_extended_dft[(i * 3 + 2) * 2 + 0];
					p_dft_ri[i * 2 + 1] = p_extended_dft[(i * 3 + 0) * 2 + 1] + p_extended_dft[(i * 3 + 1) * 2 + 1] + p_extended_dft[(i * 3 + 2) * 2 + 1];
					p_dft_ri[i * 2 + 0] /= 2;
					p_dft_ri[i * 2 + 1] /= 2;
				}
				for (U32 i = n / 3 * 2; i <= n; ++i) {
					p_dft_ri[i * 2 + 0] = 0;
					p_dft_ri[i * 2 + 1] = 0;
				}
				break;
			}
			case 4: {
				for (U32 i = 0; i < n; ++i) {
					p_extended_dft[(i * 3 + 0) * 2 + 0] = p_dft_ri[i * 2 + 0];
					p_extended_dft[(i * 3 + 1) * 2 + 0] = p_dft_ri[i * 2 + 0];
					p_extended_dft[(i * 3 + 2) * 2 + 0] = p_dft_ri[i * 2 + 0];
					p_extended_dft[(i * 3 + 0) * 2 + 1] = p_dft_ri[i * 2 + 1];
					p_extended_dft[(i * 3 + 1) * 2 + 1] = p_dft_ri[i * 2 + 1];
					p_extended_dft[(i * 3 + 2) * 2 + 1] = p_dft_ri[i * 2 + 1];
				}
				for (U32 i = 0; i < n / 4 * 3; ++i) {
					p_dft_ri[i * 2 + 0] = p_extended_dft[(i * 4 + 0) * 2 + 0] + p_extended_dft[(i * 4 + 1) * 2 + 0] + p_extended_dft[(i * 4 + 2) * 2 + 0] + p_extended_dft[(i * 4 + 3) * 2 + 0];
					p_dft_ri[i * 2 + 1] = p_extended_dft[(i * 4 + 0) * 2 + 1] + p_extended_dft[(i * 4 + 1) * 2 + 1] + p_extended_dft[(i * 4 + 2) * 2 + 1] + p_extended_dft[(i * 4 + 3) * 2 + 1];
					p_dft_ri[i * 2 + 0] /= 3;
					p_dft_ri[i * 2 + 1] /= 3;
				}
				for (U32 i = n / 4 * 3; i <= n; ++i) {
					p_dft_ri[i * 2 + 0] = 0;
					p_dft_ri[i * 2 + 1] = 0;
				}
				break;
			}
			case 5: {
				for (U32 i = 0; i < n; ++i) {
					p_extended_dft[(i * 4 + 0) * 2 + 0] = p_dft_ri[i * 2 + 0];
					p_extended_dft[(i * 4 + 1) * 2 + 0] = p_dft_ri[i * 2 + 0];
					p_extended_dft[(i * 4 + 2) * 2 + 0] = p_dft_ri[i * 2 + 0];
					p_extended_dft[(i * 4 + 3) * 2 + 0] = p_dft_ri[i * 2 + 0];
					p_extended_dft[(i * 4 + 0) * 2 + 1] = p_dft_ri[i * 2 + 1];
					p_extended_dft[(i * 4 + 1) * 2 + 1] = p_dft_ri[i * 2 + 1];
					p_extended_dft[(i * 4 + 2) * 2 + 1] = p_dft_ri[i * 2 + 1];
					p_extended_dft[(i * 4 + 3) * 2 + 1] = p_dft_ri[i * 2 + 1];
				}
				for (U32 i = 0; i < n / 5 * 4; ++i) {
					p_dft_ri[i * 2 + 0] = p_extended_dft[(i * 5 + 0) * 2 + 0] + p_extended_dft[(i * 5 + 1) * 2 + 0] + p_extended_dft[(i * 5 + 2) * 2 + 0] + p_extended_dft[(i * 5 + 3) * 2 + 0] + p_extended_dft[(i * 5 + 4) * 2 + 0];
					p_dft_ri[i * 2 + 1] = p_extended_dft[(i * 5 + 0) * 2 + 1] + p_extended_dft[(i * 5 + 1) * 2 + 1] + p_extended_dft[(i * 5 + 2) * 2 + 1] + p_extended_dft[(i * 5 + 3) * 2 + 1] + p_extended_dft[(i * 5 + 4) * 2 + 1];
					p_dft_ri[i * 2 + 0] /= 4;
					p_dft_ri[i * 2 + 1] /= 4;
				}
				for (U32 i = n / 5 * 4; i <= n; ++i) {
					p_dft_ri[i * 2 + 0] = 0;
					p_dft_ri[i * 2 + 1] = 0;
				}
				break;
			}
			case 6: {
				for (S32 i = n; i >= 0; --i) {
					if (i % 2 == 0 || 1) {
						p_dft_ri[i * 2 + 0] = p_dft_ri[(i / 2) * 2 + 0] / 2 / 1;
						p_dft_ri[i * 2 + 1] = p_dft_ri[(i / 2) * 2 + 1] / 2 / 1;
					} else {
						p_dft_ri[i * 2 + 0] = 0;
						p_dft_ri[i * 2 + 1] = 0;
					}
				}
				break;
			}
			case 7: {
				for (S32 i = n; i >= 0; --i) {
					p_dft_ri[i * 2 + 0] = p_dft_ri[(i * 8 / 9) * 2 + 0] * 8 / 9;
					p_dft_ri[i * 2 + 1] = p_dft_ri[(i * 8 / 9) * 2 + 1] * 8 / 9;
				}
				break;
			}
			default: {
				break;
			}
			}

			for (U32 i = nn / 2 + 1; i < nn; ++i) {
				p_dft_ri[i * 2 + 0] = +p_dft_ri[(nn - i) * 2 + 0];
				p_dft_ri[i * 2 + 1] = -p_dft_ri[(nn - i) * 2 + 1];
			}
#if 0
			fft_k_outofplace(invsamples_ri, p_dft_ri, 1);
#endif
			fft_f32_outofplace(p_invsamples_ri, p_dft_ri, fft_k, 1);

#if 0
			OPTIONAL_ALIGNAS(SIMD_NBYTES_FAST)
			F32 tmp_inv_samples[(1uLL << FFT_K) / 4];
#endif
			for (U32 i = 0; i < nn4; ++i) {
				p_tmp_inv_samples[i] = p_invsamples_ri[i * 2 + 0];
#if defined(DEBUG_TEST_AUDIO_OUTPUT)
				if (tmpphase == 0)
					tmp_inv_samples[i] = 0;
				if (tmpphase == 1)
					tmp_inv_samples[i] = 0.5 * nn;
				if (tmpphase == 2)
					tmp_inv_samples[i] = -0.5 * nn;
#endif
			}

			for (U32 i = 0; i < nn4; ++i) {
				p_tmp_inv_samples[i] /= nn;
			}

			assert(nn4 >= SIMD_N_32);
			for (U32 i = 0; i < nn4; i += SIMD_N_32) {
				F32_VEC res;
				F32_VEC tmp0;

				for (U32 j = 0; j < SIMD_N_32; ++j) {
					tmp0[j] = (F32)(i + j) / nn4 * M_PIf + M_PIf * 2 - M_PI_2f;
				}

				res = simd_load_f32x(p_fft_buffer_processed + i + nn4 * 3) + (naive_sin_iter_f32x(tmp0, 7) + simd_f32x(1)) / simd_f32x(2) * (simd_load_f32x(p_tmp_inv_samples + i) - simd_load_f32x(p_fft_buffer_processed + i + nn4 * 3));
				simd_store_f32x(p_tmp_inv_samples + i, res);
			}

			naive_memcpy(p_fft_buffer_processed, p_tmp_inv_samples, nn4 * sizeof *p_fft_buffer_processed);

			for (U32 i = nn4; i < nn; ++i) {
				p_fft_buffer_processed[i] = p_invsamples_ri[i * 2 + 0];
#if defined(DEBUG_TEST_AUDIO_OUTPUT)
				if (tmpphase == 0)
					p_fft_buffer_processed[i] = 0;
				if (tmpphase == 1)
					p_fft_buffer_processed[i] = 0.5 * nn;
				if (tmpphase == 2)
					p_fft_buffer_processed[i] = -0.5 * nn;
#endif
			}

			tmpphase++;
			tmpphase %= 3;

			for (U32 i = nn4; i < nn; ++i) {
				p_fft_buffer_processed[i] /= nn;
			}

			naive_memmove(p_fft_buffer_original, p_fft_buffer_original + nn4 * 3, nn4 * sizeof *p_fft_buffer_original);
		}
	}

	if (frame_count_iter != 0) {
		playback_iter = p_fft_buffer_processed + (*p_fft_phase_frames / nn4 + 2) % 3 * nn4 + *p_fft_phase_frames % nn4;
		capture_iter = p_fft_buffer_original + nn4 + (*p_fft_phase_frames / nn4 + 2) % 3 * nn4 + *p_fft_phase_frames % nn4;

		for (U32 i = 0; i < frame_count_iter; ++i) {
			capture_iter[i] = (*load)((const char *)p_input_iter + i * i_stride_bytes);
		}
		for (U32 i = 0; i < frame_count_iter; ++i) {
			for (U32 j = 0; j < o_duplication; ++j) {
				(*store)((char *)p_output_iter + i * o_stride_bytes + j * o_sizeof, min_f32(max_f32(playback_iter[i], -1), 1));
			}
		}

		if (do_visualize) {
			naive_memmove(buffer_for_visualization, buffer_for_visualization + frame_count_iter, (ARRAY_LENGTH(buffer_for_visualization) - frame_count_iter) * sizeof *buffer_for_visualization);
			for (U32 i = 0; i < frame_count_iter; ++i) {
				buffer_for_visualization[ARRAY_LENGTH(buffer_for_visualization) + i - frame_count_iter] = (*load_back)((char *)p_output_iter + i * o_stride_bytes);
			}
		}

		*p_fft_phase_frames += frame_count_iter;
		*p_fft_phase_frames %= nn4 * 3;
	}
}

static ALWAYS_INLINE void rt_audio_callback_impl(ma_device *restrict p_device,
						 void *restrict p_output,
						 const void *restrict p_input,
						 ma_uint32 frame_count_ma_param,
						 U32 fft_k, F32 *p_samples_ri, F32 *p_dft_ri, F32 *p_invsamples_ri,
						 F32 *p_tmp_inv_samples, F32 *p_extended_dft, U32 nr_active_channels, U32 nr_all_channels, UPTR o_sizeof, UPTR i_sizeof,
						 F32 (*load)(const void *), F32 (*load_back)(const void *), void (*store)(void *, F32))
{
	U8 callbackdata = ATOMIC_FETCH_OR(8, &audio_thread_data.data, 1u << 7, ATOMIC_ACQ_REL);
	full_memory_fence();

	U32 frame_count_ma = frame_count_ma_param;

	(void)p_device;

	U32 nn = 1uLL << fft_k;

	if (nr_active_channels == 1) {
		audio_process(p_output, p_input, REQUESTED_PLAYBACK_NR_CHANNELS * o_sizeof, nr_all_channels * i_sizeof, REQUESTED_PLAYBACK_NR_CHANNELS, frame_count_ma, 1,
			      callbackdata,
			      fft_k, p_samples_ri, p_dft_ri, p_invsamples_ri, p_tmp_inv_samples, p_extended_dft, fft_buffer_original, fft_buffer_processed, fft_phase_frames, o_sizeof, load, load_back, store);
	} else if (nr_active_channels == REQUESTED_PLAYBACK_NR_CHANNELS) {
		for (U32 i = 0; i < REQUESTED_PLAYBACK_NR_CHANNELS; ++i) {
			audio_process((char *)p_output + o_sizeof * i, (char *)p_input + i_sizeof * i,
				      REQUESTED_PLAYBACK_NR_CHANNELS * o_sizeof, nr_all_channels * i_sizeof, 1, frame_count_ma, i == 0, callbackdata,
				      fft_k, p_samples_ri, p_dft_ri, p_invsamples_ri, p_tmp_inv_samples, p_extended_dft, fft_buffer_original + i * (1uLL << MAX_K), fft_buffer_processed + i * (1uLL << MAX_K), fft_phase_frames + i, o_sizeof, load, load_back, store);
		}
	} else {
		assert(0);
	}

	int upd_graphics = 1;
	if (0 != (*(int (*)(union pthread_mutex_t *))my_pthread_mutex_try_lock)(&vert_mutex)) {
		upd_graphics = 0;
	}

	if (upd_graphics) {
		for (U64 i = 0; i < (1 << MAX_K); ++i) {
			audio_vert.time[i * 2 + 1] = -buffer_for_visualization[ARRAY_LENGTH(buffer_for_visualization) - nn + i * nn / (1 << MAX_K)];
		}
		for (U32 i = 0; i < nn; ++i) {
			p_samples_ri[i * 2 + 0] = buffer_for_visualization[ARRAY_LENGTH(buffer_for_visualization) - nn + i];
			p_samples_ri[i * 2 + 1] = 0;
		}
		fft_f32_outofplace(p_dft_ri, p_samples_ri, fft_k, 0);

		for (U32 i = 0; i < (1 << 10); i += SIMD_N_32) {
			F32_VEC result;
			F32_VEC tmp0;
			F32_VEC tmp1;
			for (U32 j = 0; j < SIMD_N_32; ++j) {
				tmp0[j] = p_dft_ri[(i + j) * 2 + 0];
			}
			for (U32 j = 0; j < SIMD_N_32; ++j) {
				tmp1[j] = p_dft_ri[(i + j) * 2 + 1];
			}

			result = sqrt_f32x(tmp0 * tmp0 + tmp1 * tmp1) / simd_f32x(1024) * simd_f32x((F32)(S32)((1 << MAX_K) / (1 << fft_k))) - simd_f32x(1);

			for (U32 j = 0; j < SIMD_N_32; ++j) {
				for (U32 k = 0; k < (1 << MAX_K) / (1 << 10); ++k) {
					audio_vert.freq[((i + j) * ((1 << MAX_K) / (1 << 10)) + k) * 2 + 1] = result[j];
				}
			}
		}

		(*(void (*)(union pthread_mutex_t *))my_pthread_mutex_unlock)(&vert_mutex);
		upd_graphics = 0;
	}

	/* No -flto! */
	/* x86_64 and AArch64 */

	full_memory_fence();
	ATOMIC_FETCH_AND(8, &audio_thread_data.data, (U8) ~(1u << 7), ATOMIC_ACQ_REL);
}

static ALWAYS_INLINE U8 raw_load_u8(const void *p)
{
	U8 res;
	asm volatile("movb (%1), %0" : "=r"(res) : "r"(p) : "memory");
	return res;
}

static ALWAYS_INLINE void raw_store_u8(void *p, U8 v)
{
	asm volatile("movb %1, (%0)" ::"r"(p), "r"((U8)v) : "memory");
}

static ALWAYS_INLINE F32 audio_load_s16(const void *p)
{
	return (F32) * (S16 *)p / -(S32)S16_MIN;
}

static ALWAYS_INLINE F32 audio_load_s24(const void *p)
{
	STATIC_ASSERT(CHAR_BIT == 8);

	U8 bytes[3];
	bytes[0] = raw_load_u8((const char *)p + 0);
	bytes[1] = raw_load_u8((const char *)p + 1);
	bytes[2] = raw_load_u8((const char *)p + 2);

	U32 data_raw = 0;
	/* little endian */
	data_raw |= (U32)bytes[0] << CHAR_BIT * 0;
	data_raw |= (U32)bytes[1] << CHAR_BIT * 1;
	data_raw |= (U32)bytes[2] << CHAR_BIT * 2;

	S32 data_int;
	if (data_raw & 0x800000) {
		data_raw |= 0xff000000u;
		data_int = ~data_raw;
		data_int = -data_int - 1;
	} else {
		data_int = data_raw;
	}

	return (F32)((F64)data_int / 0x800000);
}

static ALWAYS_INLINE F32 audio_load_s32(const void *p)
{
	return (F32)((F64) * (S32 *)p / -(S64)S32_MIN);
}

static ALWAYS_INLINE F32 audio_load_f32(const void *p)
{
	return *(F32 *)p;
}

static ALWAYS_INLINE void audio_store_s16(void *p, F32 v)
{
	*(S16 *)p = (S16)((F64)v * S16_MAX);
}

static ALWAYS_INLINE void audio_store_s24(void *p, F32 v)
{
	STATIC_ASSERT(CHAR_BIT == 8);

	S32 data_int = (S32)((F64)v * 0x7fffff);
	U32 data_raw = 0;

	if (data_int < 0) {
		data_raw = -data_int;
		data_raw -= 1;
		data_raw = ~data_raw;
	} else {
		data_raw = data_int;
	}

	/* little endian */
	raw_store_u8((char *)p + 0, data_raw >> CHAR_BIT * 0);
	raw_store_u8((char *)p + 1, data_raw >> CHAR_BIT * 1);
	raw_store_u8((char *)p + 2, data_raw >> CHAR_BIT * 2);
}

static ALWAYS_INLINE void audio_store_s32(void *p, F32 v)
{
	*(S32 *)p = (S32)((F64)v * S32_MAX);
}

static ALWAYS_INLINE void audio_store_f32(void *p, F32 v)
{
	*(F32 *)p = v;
}

#define GENERATE_rt_audio_callback(in, out, fft_k, i_sizeofbits, o_sizeofbits, nr_active_channels, nr_all_channels)              \
	void rt_audio_callback_##in##_##out##_##fft_k##_##nr_active_channels##_##nr_all_channels(ma_device *restrict p_device,   \
												 void *restrict p_output,        \
												 const void *restrict p_input,   \
												 ma_uint32 frame_count_ma_param) \
	{                                                                                                                        \
		OPTIONAL_ALIGNAS(SIMD_NBYTES)                                                                                    \
		F32 samples_ri[(1uLL << fft_k) * 2];                                                                             \
                                                                                                                                 \
		OPTIONAL_ALIGNAS(SIMD_NBYTES)                                                                                    \
		F32 dft_ri[(1uLL << fft_k) * 2];                                                                                 \
                                                                                                                                 \
		OPTIONAL_ALIGNAS(SIMD_NBYTES)                                                                                    \
		F32 invsamples_ri[(1uLL << fft_k) * 2];                                                                          \
                                                                                                                                 \
		OPTIONAL_ALIGNAS(SIMD_NBYTES)                                                                                    \
		F32 tmp_inv_samples[(1uLL << fft_k) / 4];                                                                        \
                                                                                                                                 \
		F32 extended_dft[(1uLL << fft_k) / 2 * 4 * 2];                                                                   \
                                                                                                                                 \
		/* clang-format off */ \
		rt_audio_callback_impl(p_device, \
			p_output, \
			p_input, \
			frame_count_ma_param, \
			fft_k, \
			samples_ri, \
			dft_ri, \
			invsamples_ri, \
			tmp_inv_samples, \
			extended_dft, \
			nr_active_channels, \
			nr_all_channels, \
			o_sizeofbits / CHAR_BIT, \
			i_sizeofbits / CHAR_BIT, \
			audio_load_##in, \
			audio_load_##out, \
			audio_store_##out);                                                                                         \
		/* clang-format on */                                                                                            \
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
