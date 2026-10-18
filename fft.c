
#ifndef SENTRY_NAIVE_MATH
#define SENTRY_NAIVE_MATH
#include "naive_math.c"
#endif

static ALWAYS_INLINE U32 bit_rev32_impl(U32 a, U8 k)
{
	assert(a == (U32)a);
	assert(k <= 32);
	return bitreverse_32(a) >> (32 - k);
}

static ALWAYS_INLINE void bit_reverse_copy_32_impl(void *dst,
						   void *src,
						   U64_IN stride,
						   U8_IN k,
						   void (*assign)(void *dst, void *src),
						   U32 (*bitrev)(U32_IN a, U8_IN k))
{
	U64 n;
	U64 i;
	U64 br;

	assert(k > 0);
	assert(k <= 32);

	n = 1uLL << k;

	for (i = 0; i < n; ++i) {
		br = (*bitrev)(i, k);
		(*assign)((char *)dst + stride * br, (char *)src + stride * i);
	}
}

/*
 * The inverse is not divided by N
 *
 * http
 * en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm#Data_reordering,_bit_reversal,_and_in-place_algorithms
 */
static ALWAYS_INLINE void fft_f32_impl(F32 *dstri,
				       F32 *srcri,
				       U8_IN k,
				       BOOL_IN rev,
				       void (*revcopy)(void *dst, void *src, U8_IN k),
				       void (*fpsincosf)(F32 x, F32 *sin, F32 *cos),
				       BOOL_OUT (*cplx_mult)(F32 *r, F32 *i, F32 r1, F32 i1, F32 r2, F32 i2))
{
	S64 n;

	ALWAYS(k < 63);
	ALWAYS(k >= 0);

	n = (S64)(1uLL << k);
	(*revcopy)(dstri, srcri, k);

	for (U32 s = 1; s <= k; ++s) {
		S64 m = (S64)(1uLL << s);
		F32 tmpsin;
		F32 tmpcos;
		(*fpsincosf)(2 * M_PIf / m, &tmpsin, &tmpcos);
		F32 omega_mr = (rev ? +1 : +1) * tmpcos;
		F32 omega_mi = (rev ? +1 : -1) * tmpsin;
		for (S64 i = 0; i < n; i += m) {
			F32 omega_r = 1;
			F32 omega_i = 0;
			for (S64 j = 0; j <= m / 2 - 1; ++j) {
				F32 *dstpr = dstri + (i + j) * 2 + 0;
				F32 *dstpi = dstri + (i + j) * 2 + 1;
				F32 *dstpmr = dstri + (i + j + m / 2) * 2 + 0;
				F32 *dstpmi = dstri + (i + j + m / 2) * 2 + 1;
				F32 tr;
				F32 ti;
				(*cplx_mult)(&tr, &ti, omega_r, omega_i, *dstpmr, *dstpmi);
				F32 ur = *dstpr;
				F32 ui = *dstpi;
				*dstpr = ur + tr;
				*dstpi = ui + ti;
				*dstpmr = ur - tr;
				*dstpmi = ui - ti;
				(*cplx_mult)(&omega_r, &omega_i, omega_r, omega_i, omega_mr, omega_mi);
			}
		}
	}
}

static ALWAYS_INLINE void memmove_bytes_8(void *dst, void *src)
{
	for (U32 i = 0; i < 8; ++i) {
		*((char *)dst + i) = *((char *)src + i);
	}
}

static ALWAYS_INLINE void bit32_reverse_copy_8(void *dst, void *src, U8 k)
{
	bit_reverse_copy_32_impl(dst, src, 8, k, memmove_bytes_8, bit_rev32_impl);
}

void fft_f32_outofplace_10_impl(F32 *restrict dstri,
				F32 *restrict srcri,
				BOOL_IN rev)
{
	fft_f32_impl(dstri, srcri, 10, rev, bit32_reverse_copy_8, naive_sincos_wrapped_fft_f32, cplx_mul_f32);
}

void fft_f32_outofplace_11_impl(F32 *restrict dstri,
				F32 *restrict srcri,
				BOOL_IN rev)
{
	fft_f32_impl(dstri, srcri, 11, rev, bit32_reverse_copy_8, naive_sincos_wrapped_fft_f32, cplx_mul_f32);
}

void fft_f32_outofplace_12_impl(F32 *restrict dstri,
				F32 *restrict srcri,
				BOOL_IN rev)
{
	fft_f32_impl(dstri, srcri, 12, rev, bit32_reverse_copy_8, naive_sincos_wrapped_fft_f32, cplx_mul_f32);
}

void fft_f32_outofplace_13_impl(F32 *restrict dstri,
				F32 *restrict srcri,
				BOOL_IN rev)
{
	fft_f32_impl(dstri, srcri, 13, rev, bit32_reverse_copy_8, naive_sincos_wrapped_fft_f32, cplx_mul_f32);
}
