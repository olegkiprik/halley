
#ifndef SENTRY_MATH
#define SENTRY_MATH
#include "math.c"
#endif

/* [0, pi/2] -> [0, 1) */
static ALWAYS_INLINE F32 naive_sin_base_iter_f32(F32 x, U32 iter_x2)
{
	F32 result;
	F32 a;
	S32 sign;
	U64 b;
	U32 i;

	assert(x == x);
	assert(x < F32_MAX);
	assert(x > -F32_MAX);
	assert(x >= 0);
	assert(x <= M_PI_2f);

	a = x;
	b = 1;
	sign = 1;
	result = 0;

	for (i = 0; i < iter_x2 * 2; i += 2) {
		result += a / b * sign;
		a *= x * x;
		b *= (i + 2) * (i + 3);
		sign = -sign;
	}

	assert(result == result);
	assert(result < F32_MAX);
	assert(result > -F32_MAX);
	assert(result >= 0);
	assert(result < 1);
	return result;
}

/* [0, pi/2] -> [0, 1) */
static ALWAYS_INLINE F32_VEC naive_sin_base_f32x(F32_VEC x, U32 iter_x2)
{
	F32_VEC result;
	F32_VEC a;
	S32 sign;
	S32 b;
	U32 i;

	a = x;
	b = 1;
	sign = 1;
	result = simd_f32x(0);

	for (i = 0; i < iter_x2 * 2; i += 2) {
		result += a / simd_f32x(b) * simd_f32x(sign);
		a *= x * x;
		b *= (i + 2) * (i + 3);
		sign = -sign;
	}

	return result;
}

static ALWAYS_INLINE F32 naive_fmod_nonneg_f32(F32 x, F32 y)
{
	assert(x == x);
	assert(x < F32_MAX);
	assert(x > -F32_MAX);
	assert(x >= 0);
	assert(y >= 0);
	assert(y != 0);

	x += y;
	do {
		x -= y;
	} while (x >= y);

	if (x < 0) {
		x = 0;
	}

	assert(x == x);
	assert(x < F32_MAX);
	assert(x > -F32_MAX);
	assert(x >= 0);
	return x;
}

static ALWAYS_INLINE F32 naive_sin_f32(F32 x, U32 iter_x2)
{
	S32 sign;

	assert(x == x);
	assert(x < F32_MAX);
	assert(x > -F32_MAX);

	sign = 1;

	if (LESS_LIKELY(x < 0)) {
		x = -x;
		sign = -sign;
	}

	assert(x >= 0);

	x = naive_fmod_nonneg_f32(x, M_PIf * 2);

	assert(x >= 0);
	assert(x < M_PIf * 2);

	if (x >= M_PIf) {
		x -= M_PIf;
		if (x < 0) {
			x = 0;
		}
		if (x > M_PIf) {
			x = M_PIf;
		}
		sign = -sign;
	}

	assert(x >= 0);
	assert(x <= M_PIf);

	if (x >= M_PI_2f) {
		x = M_PIf - x;
		if (x < 0) {
			x = 0;
		}
		if (x > M_PI_2f) {
			x = M_PI_2f;
		}
	}

	assert(x >= 0);
	assert(x <= M_PI_2f);

	return naive_sin_base_iter_f32(x, iter_x2) * sign;
}

static ALWAYS_INLINE F32_VEC naive_sin_iter_f32x(F32_VEC x, U32 iter_x2)
{
	F32_VEC sign = simd_f32x(1);
	F32_VEC tmp;
	F32_VEC tmp1;

	for (U32 i = 0; i < SIMD_N_32; ++i) {
		tmp[i] = x[i] < 0;
	}

	x *= simd_f32x(1) - simd_f32x(2) * tmp;
	sign *= simd_f32x(1) - simd_f32x(2) * tmp;

	for (U32 i = 0; i < SIMD_N_32; ++i) {
		x[i] = naive_fmod_nonneg_f32(x[i], M_PIf * 2);
	}

	tmp = simd_compare_less_eq_01_f32x(simd_f32x(M_PIf), x);

	F32_VEC tmp0 = x;
	tmp0 -= simd_f32x(M_PIf);
	tmp1 = simd_compare_less_01_f32x(tmp0, simd_f32x(0));
	tmp0 *= simd_f32x(1) - tmp1;
	tmp1 = simd_compare_less_01_f32x(simd_f32x(M_PIf), tmp0);
	tmp0 += (simd_f32x(M_PIf) - tmp0) * tmp1;
	x += (tmp0 - x) * tmp;
	sign *= simd_f32x(1) - simd_f32x(2) * tmp;

	tmp = simd_compare_less_eq_01_f32x(simd_f32x(M_PI_2f), x);
	tmp0 = simd_f32x(M_PIf) - x;
	tmp1 = simd_compare_less_01_f32x(tmp0, simd_f32x(0));
	tmp0 *= simd_f32x(1) - tmp1;
	tmp1 = simd_compare_less_01_f32x(simd_f32x(M_PI_2f), tmp0);
	tmp0 += (simd_f32x(M_PI_2f) - tmp0) * tmp1;
	x += (tmp0 - x) * tmp;

	F32_VEC res = naive_sin_base_f32x(x, iter_x2);
	res *= sign;
	return res;
}

static ALWAYS_INLINE void naive_sincos_wrapped_fft_f32(F32 x, F32 *res_sin, F32 *res_cos)
{
	F32 s = naive_sin_f32(x, 7);
	F32 c = naive_sin_f32(x + M_PI_2f, 7);
	*res_sin = s;
	*res_cos = c;
}

static ALWAYS_INLINE F32 naive_log_natural_iter_f32(F32 x, U32 iter_x4)
{
	F32_4 res = simd_f32x4(0);
	if (x <= 1) {
		F32 core = (x - 1) * (x - 1) * (x - 1) * (x - 1);
		F32_4 dividee;
		S32_4 divisor;
		dividee[0] = (x - 1);
		dividee[1] = (x - 1) * (x - 1);
		dividee[2] = (x - 1) * (x - 1) * (x - 1);
		dividee[3] = (x - 1) * (x - 1) * (x - 1) * (x - 1);
		divisor[0] = 1;
		divisor[1] = 2;
		divisor[2] = 3;
		divisor[3] = 4;
		S32_4 sign;
		sign[0] = 1;
		sign[1] = -1;
		sign[2] = 1;
		sign[3] = -1;
		for (U32 i = 1; i <= iter_x4; ++i) {
			res += simd_cast_s32_to_f32_x4(sign) * dividee / simd_cast_s32_to_f32_x4(divisor);
			dividee *= core;
			divisor += simd_s32x4(4);
		}
	} else {
		x = 1 / x;
		F32 core = (x - 1) * (x - 1) * (x - 1) * (x - 1);
		F32_4 dividee;
		S32_4 divisor;
		dividee[0] = (x - 1);
		dividee[1] = (x - 1) * (x - 1);
		dividee[2] = (x - 1) * (x - 1) * (x - 1);
		dividee[3] = (x - 1) * (x - 1) * (x - 1) * (x - 1);
		divisor[0] = 1;
		divisor[1] = 2;
		divisor[2] = 3;
		divisor[3] = 4;
		S32_4 sign;
		sign[0] = -1;
		sign[1] = 1;
		sign[2] = -1;
		sign[3] = 1;
		for (U32 i = 1; i <= iter_x4; ++i) {
			res += simd_cast_s32_to_f32_x4(sign) * dividee / simd_cast_s32_to_f32_x4(divisor);
			dividee *= core;
			divisor += simd_s32x4(4);
		}
	}
	return res[0] + res[1] + res[2] + res[3];
}

static ALWAYS_INLINE F32_4 naive_log_natural_iter_f32x4(F32_4 x, U32 iter)
{
	F32_4 res = simd_f32x4(0);
	F32_4 sign;
	F32_4 core;
	F32_4 dividee;

	core = (x - simd_f32x4(1)) * simd_compare_less_eq_01_f32x4(x, simd_f32x4(1)) +
	       (simd_f32x4(1) / x - simd_f32x4(1)) *
		   (1 - simd_compare_less_eq_01_f32x4(x, simd_f32x4(1)));

	sign = simd_f32x4(1) -
	       simd_f32x4(2) * simd_compare_less_01_f32x4(simd_f32x4(1), x);

	dividee = core;
	for (U32 i = 1; i <= iter; ++i) {
		res += sign * dividee / simd_f32x4(i);
		dividee *= x - simd_f32x4(1);
		sign = -sign;
	}
	return res;
}
