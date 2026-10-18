
#ifndef SENTRY_BASICS
#define SENTRY_BASICS
#include "basics.c"
#endif

#define STR_FAIL_MATH "math error"

static ALWAYS_INLINE BOOL_OUT cplx_mul_impl(void *resr, void *resi, void *r1, void *i1, void *r2, void *i2, void *buf1,
					    void *buf2, BOOL_OUT (*add)(void *res, void *x, void *y, void (*fl)(void)),
					    BOOL_OUT (*neg)(void *res, void *x, void (*fl)(void)),
					    BOOL_OUT (*mul)(void *res, void *x, void *y, void (*fl)(void)), void (*fl)(void))
{
	U32 err;
	err = 0;

	/*
	 * buf1 = i1 * i2
	 * buf2 = -buf1 = -i1 * i2
	 * buf1 = r1 * r2
	 * rres = buf1 + buf2 = r1 * r2 - i1 * i2
	 *
	 * buf1 = r1 * i2
	 * buf2 = i1 * r2
	 * ires = buf1 + buf2 = r1 * i2 + i1 * r2
	 */
	FAILCHECK(&err, fl, (*mul)(buf1, i1, i2, fl), STR_FAIL_MATH, NULL);
	FAILCHECK(&err, fl, (*neg)(buf2, buf1, fl), STR_FAIL_MATH, NULL);
	FAILCHECK(&err, fl, (*mul)(buf1, r1, r2, fl), STR_FAIL_MATH, NULL);
	FAILCHECK(&err, fl, (*add)(resr, buf1, buf2, fl), STR_FAIL_MATH, NULL);
	FAILCHECK(&err, fl, (*mul)(buf1, r1, i2, fl), STR_FAIL_MATH, NULL);
	FAILCHECK(&err, fl, (*mul)(buf2, i1, r2, fl), STR_FAIL_MATH, NULL);
	FAILCHECK(&err, fl, (*add)(resi, buf1, buf2, fl), STR_FAIL_MATH, NULL);
	return err;
}

#define GENERATE_add_impl(type, nvec)                                                                           \
	static ALWAYS_INLINE BOOL_OUT add_##type##x##nvec##_impl(void *res, void *a, void *b, void (*fl)(void)) \
	{                                                                                                       \
		(void)fl;                                                                                       \
		*(type##x##nvec *)res = *(type##x##nvec *)a + *(type##x##nvec *)b;                              \
		return 0;                                                                                       \
	}

#define GENERATE_sub_impl(type, nvec)                                                                           \
	static ALWAYS_INLINE BOOL_OUT sub_##type##x##nvec##_impl(void *res, void *a, void *b, void (*fl)(void)) \
	{                                                                                                       \
		(void)fl;                                                                                       \
		*(type##x##nvec *)res = *(type##x##nvec *)a - *(type##x##nvec *)b;                              \
		return 0;                                                                                       \
	}

#define GENERATE_mul_impl(type, nvec)                                                                           \
	static ALWAYS_INLINE BOOL_OUT mul_##type##x##nvec##_impl(void *res, void *a, void *b, void (*fl)(void)) \
	{                                                                                                       \
		(void)fl;                                                                                       \
		*(type##x##nvec *)res = *(type##x##nvec *)a * *(type##x##nvec *)b;                              \
		return 0;                                                                                       \
	}

#define GENERATE_div_impl(type, nvec)                                                                           \
	static ALWAYS_INLINE BOOL_OUT div_##type##x##nvec##_impl(void *res, void *a, void *b, void (*fl)(void)) \
	{                                                                                                       \
		(void)fl;                                                                                       \
		*(type##x##nvec *)res = *(type##x##nvec *)a / *(type##x##nvec *)b;                              \
		return 0;                                                                                       \
	}

#define GENERATE_bitxor_impl(type, nvec)                                                                           \
	static ALWAYS_INLINE BOOL_OUT bitxor_##type##x##nvec##_impl(void *res, void *a, void *b, void (*fl)(void)) \
	{                                                                                                          \
		(void)fl;                                                                                          \
		*(type##x##nvec *)res = *(type##x##nvec *)a ^ *(type##x##nvec *)b;                                 \
		return 0;                                                                                          \
	}

#define GENERATE_bitor_impl(type, nvec)                                                                           \
	static ALWAYS_INLINE BOOL_OUT bitor_##type##x##nvec##_impl(void *res, void *a, void *b, void (*fl)(void)) \
	{                                                                                                         \
		(void)fl;                                                                                         \
		*(type##x##nvec *)res = *(type##x##nvec *)a | *(type##x##nvec *)b;                                \
		return 0;                                                                                         \
	}

#define GENERATE_bitand_impl(type, nvec)                                                                           \
	static ALWAYS_INLINE BOOL_OUT bitand_##type##x##nvec##_impl(void *res, void *a, void *b, void (*fl)(void)) \
	{                                                                                                          \
		(void)fl;                                                                                          \
		*(type##x##nvec *)res = *(type##x##nvec *)a & *(type##x##nvec *)b;                                 \
		return 0;                                                                                          \
	}

#define GENERATE_mod_impl(type, nvec)                                                                           \
	static ALWAYS_INLINE BOOL_OUT mod_##type##x##nvec##_impl(void *res, void *a, void *b, void (*fl)(void)) \
	{                                                                                                       \
		(void)fl;                                                                                       \
		*(type##x##nvec *)res = *(type##x##nvec *)a % *(type##x##nvec *)b;                              \
		return 0;                                                                                       \
	}

#define GENERATE_bitnot_impl(type, nvec)                                                                  \
	static ALWAYS_INLINE BOOL_OUT bitnot_##type##x##nvec##_impl(void *res, void *a, void (*fl)(void)) \
	{                                                                                                 \
		(void)fl;                                                                                 \
		*(type##x##nvec *)res = ~*(type##x##nvec *)a;                                             \
		return 0;                                                                                 \
	}

#define GENERATE_neg_impl(type, nvec)                                                                  \
	static ALWAYS_INLINE BOOL_OUT neg_##type##x##nvec##_impl(void *res, void *a, void (*fl)(void)) \
	{                                                                                              \
		(void)fl;                                                                              \
		*(type##x##nvec *)res = -*(type##x##nvec *)a;                                          \
		return 0;                                                                              \
	}

#define GENERATE_nop_impl(type, nvec)                                                                  \
	static ALWAYS_INLINE BOOL_OUT nop_##type##x##nvec##_impl(void *res, void *a, void (*fl)(void)) \
	{                                                                                              \
		(void)fl;                                                                              \
		*(type##x##nvec *)res = *(type##x##nvec *)a;                                           \
		return 0;                                                                              \
	}

#define GENERATE_cplx_mul(type, nvec)                                                                                                                                            \
	static ALWAYS_INLINE BOOL_OUT cplx_mul_##type##x##nvec(type##x##nvec *restrict resr, type##x##nvec *restrict resi, type##x##nvec r1, type##x##nvec i1, type##x##nvec r2, \
							       type##x##nvec i2)                                                                                                 \
	{                                                                                                                                                                        \
		type##x##nvec buf1;                                                                                                                                              \
		type##x##nvec buf2;                                                                                                                                              \
		type##x##nvec tmprres;                                                                                                                                           \
		type##x##nvec tmpires;                                                                                                                                           \
                                                                                                                                                                                 \
		cplx_mul_impl(&tmprres, &tmpires, &r1, &i1, &r2, &i2, &buf1, &buf2, add_##type##x##nvec##_impl,                                                                  \
			      neg_##type##x##nvec##_impl, mul_##type##x##nvec##_impl, FNULL);                                                                                    \
		*resr = tmprres;                                                                                                                                                 \
		*resi = tmpires;                                                                                                                                                 \
		return 0;                                                                                                                                                        \
	}

#define GENERATE_cplx_div(type, nvec)                                                                                                                                            \
	static ALWAYS_INLINE BOOL_OUT cplx_div_##type##x##nvec(type##x##nvec *restrict resr, type##x##nvec *restrict resi, type##x##nvec r1, type##x##nvec i1, type##x##nvec r2, \
							       type##x##nvec i2)                                                                                                 \
	{                                                                                                                                                                        \
		type##x##nvec a;                                                                                                                                                 \
		type##x##nvec b;                                                                                                                                                 \
		type##x##nvec c;                                                                                                                                                 \
		type##x##nvec d;                                                                                                                                                 \
                                                                                                                                                                                 \
		a = r1;                                                                                                                                                          \
		b = i1;                                                                                                                                                          \
		c = r2;                                                                                                                                                          \
		d = i2;                                                                                                                                                          \
                                                                                                                                                                                 \
		type##x##nvec ac;                                                                                                                                                \
		type##x##nvec bc;                                                                                                                                                \
		type##x##nvec ad;                                                                                                                                                \
		type##x##nvec bd;                                                                                                                                                \
		type##x##nvec cc;                                                                                                                                                \
		type##x##nvec dd;                                                                                                                                                \
                                                                                                                                                                                 \
		ac = a * c;                                                                                                                                                      \
		bc = b * c;                                                                                                                                                      \
		bd = b * d;                                                                                                                                                      \
		ad = a * d;                                                                                                                                                      \
		cc = c * d;                                                                                                                                                      \
		dd = d * d;                                                                                                                                                      \
                                                                                                                                                                                 \
		type##x##nvec ac_bd;                                                                                                                                             \
		type##x##nvec bc_ad;                                                                                                                                             \
		type##x##nvec cc_dd;                                                                                                                                             \
                                                                                                                                                                                 \
		ac_bd = ac + bd;                                                                                                                                                 \
		bc_ad = bc - ad;                                                                                                                                                 \
		cc_dd = cc + dd;                                                                                                                                                 \
                                                                                                                                                                                 \
		type##x##nvec one;                                                                                                                                               \
		type##x##nvec rec;                                                                                                                                               \
                                                                                                                                                                                 \
		BROADCAST_##nvec(&one, 1);                                                                                                                                       \
		rec = one / cc_dd;                                                                                                                                               \
                                                                                                                                                                                 \
		*resr = ac_bd * rec;                                                                                                                                             \
		*resi = bc_ad * rec;                                                                                                                                             \
		return 0;                                                                                                                                                        \
	}

#define GENERATE_cplx_sqrt(type, nvec)                                                                                                                       \
	static ALWAYS_INLINE BOOL_OUT cplx_sqrt_##type##x##nvec(type##x##nvec *restrict resr1, type##x##nvec *restrict resi1, type##x##nvec *restrict resr2, \
								type##x##nvec *restrict resi2, type##x##nvec re, type##x##nvec im)                           \
	{                                                                                                                                                    \
		type##x##nvec aa_bb;                                                                                                                         \
		aa_bb = re * re + im * im;                                                                                                                   \
		type##x##nvec sqrt_aa_bb;                                                                                                                    \
		type##x##nvec pl;                                                                                                                            \
		type##x##nvec mi;                                                                                                                            \
                                                                                                                                                             \
		sqrt_aa_bb = sqrt_##type##x##nvec(aa_bb);                                                                                                    \
		pl = re + sqrt_aa_bb;                                                                                                                        \
		mi = sqrt_aa_bb - re;                                                                                                                        \
		type##x##nvec two;                                                                                                                           \
		BROADCAST_##nvec(&two, 2);                                                                                                                   \
		pl /= two;                                                                                                                                   \
		mi /= two;                                                                                                                                   \
                                                                                                                                                             \
		type##x##nvec sqrt_all_pl;                                                                                                                   \
		type##x##nvec sqrt_all_mi;                                                                                                                   \
                                                                                                                                                             \
		sqrt_all_pl = sqrt_##type##x##nvec(pl);                                                                                                      \
		sqrt_all_mi = sqrt_##type##x##nvec(mi);                                                                                                      \
                                                                                                                                                             \
		for (U32 i = 0; i < nvec; ++i) {                                                                                                             \
			SIMD_REFER_##nvec(sqrt_all_mi)[i] *= SIMD_REFER_##nvec(im)[i] < 0 ? -1 : 1;                                                          \
		}                                                                                                                                            \
                                                                                                                                                             \
		type##x##nvec neg_pl;                                                                                                                        \
		type##x##nvec neg_mi;                                                                                                                        \
                                                                                                                                                             \
		neg_pl = -sqrt_all_pl;                                                                                                                       \
		neg_mi = -sqrt_all_mi;                                                                                                                       \
                                                                                                                                                             \
		*resr1 = sqrt_all_pl;                                                                                                                        \
		*resr2 = neg_pl;                                                                                                                             \
		*resi1 = sqrt_all_mi;                                                                                                                        \
		*resi2 = neg_mi;                                                                                                                             \
                                                                                                                                                             \
		return 0;                                                                                                                                    \
	}

#define GENERATE_cplx_rsqrt(type, nvec)                                                                                                                       \
	static ALWAYS_INLINE BOOL_OUT cplx_rsqrt_##type##x##nvec(type##x##nvec *restrict resr1, type##x##nvec *restrict resi1, type##x##nvec *restrict resr2, \
								 type##x##nvec *restrict resi2, type##x##nvec re, type##x##nvec im)                           \
	{                                                                                                                                                     \
		type##x##nvec aa_bb;                                                                                                                          \
		aa_bb = re * re + im * im;                                                                                                                    \
		type##x##nvec rsqrt_aa_bb;                                                                                                                    \
		type##x##nvec pl;                                                                                                                             \
		type##x##nvec mi;                                                                                                                             \
                                                                                                                                                              \
		rsqrt_aa_bb = rsqrt_##type##x##nvec(aa_bb);                                                                                                   \
		pl = re / aa_bb;                                                                                                                              \
		mi = -pl;                                                                                                                                     \
                                                                                                                                                              \
		pl += rsqrt_aa_bb;                                                                                                                            \
		mi += rsqrt_aa_bb;                                                                                                                            \
                                                                                                                                                              \
		type##x##nvec two;                                                                                                                            \
		BROADCAST_##nvec(&two, 2);                                                                                                                    \
		pl /= two;                                                                                                                                    \
		mi /= two;                                                                                                                                    \
                                                                                                                                                              \
		type##x##nvec sqrt_all_pl;                                                                                                                    \
		type##x##nvec sqrt_all_mi;                                                                                                                    \
                                                                                                                                                              \
		sqrt_all_pl = sqrt_##type##x##nvec(pl);                                                                                                       \
		sqrt_all_mi = sqrt_##type##x##nvec(mi);                                                                                                       \
                                                                                                                                                              \
		for (U32 i = 0; i < nvec; ++i) {                                                                                                              \
			SIMD_REFER_##nvec(sqrt_all_mi)[i] *= SIMD_REFER_##nvec(im)[i] < 0 ? -1 : 1;                                                           \
		}                                                                                                                                             \
                                                                                                                                                              \
		type##x##nvec neg_pl;                                                                                                                         \
		type##x##nvec neg_mi;                                                                                                                         \
                                                                                                                                                              \
		neg_pl = -sqrt_all_pl;                                                                                                                        \
		neg_mi = -sqrt_all_mi;                                                                                                                        \
                                                                                                                                                              \
		*resr1 = sqrt_all_pl;                                                                                                                         \
		*resr2 = neg_pl;                                                                                                                              \
		*resi1 = neg_mi;                                                                                                                              \
		*resi2 = sqrt_all_mi;                                                                                                                         \
                                                                                                                                                              \
		return 0;                                                                                                                                     \
	}

#define s8 S8
#define u8 U8
#define s8x1 s8
#define u8x1 u8

#define s16 S16
#define u16 U16
#define f5e11s F5E11S
#define f8e8s F8E8S
#define s16x1 s16
#define u16x1 u16
#define f5e11sx1 f5e11s
#define f8e8sx1 f8e8s

#define s32 S32
#define u32 U32
#define f32 F32
#define s32x1 s32
#define u32x1 u32
#define f32x1 f32

#define s64 S64
#define u64 U64
#define f64 F64
#define s64x1 s64
#define u64x1 u64
#define f64x1 f64
#define s8x8 S8_8
#define u8x8 U8_8
#define s16x4 S16_4
#define u16x4 U16_4
#define f5e11sx4 F5E11S_4
#define f8e8sx4 F8E8S_4
#define s32x2 S32_2
#define u32x2 U32_2
#define f32x2 F32_2

#define s128 S128
#define u128 U128
#define s8x16 S8_16
#define u8x16 U8_16
#define s16x8 S16_8
#define u16x8 U16_8
#define f5e11sx8 F5E11S_8
#define f8e8sx8 F8E8S_8
#define s32x4 S32_4
#define u32x4 U32_4
#define f32x4 F32_4
#define s64x2 S64_2
#define u64x2 U64_2
#define f64x2 F64_2

#define s8x32 S8_32
#define u8x32 U8_32
#define s16x16 S16_16
#define u16x16 U16_16
#define f5e11sx16 F5E11S_16
#define f8e8sx16 F8E8S_16
#define s32x8 S32_8
#define u32x8 U32_8
#define f32x8 F32_8
#define s64x4 S64_4
#define u64x4 U64_4
#define f64x4 F64_4

#define s8x64 S8_64
#define u8x64 U8_64
#define s16x32 S16_32
#define u16x32 U16_32
#define f5e11sx32 F5E11S_32
#define f8e8sx32 F8E8S_32
#define s32x16 S32_16
#define u32x16 U32_16
#define f32x16 F32_16
#define s64x8 S64_8
#define u64x8 U64_8
#define f64x8 F64_8

#define s8x128 S8_128
#define u8x128 U8_128
#define s16x64 S16_64
#define u16x64 U16_64
#define f5e11sx64 F5E11S_64
#define f8e8sx64 F8E8S_64
#define s32x32 S32_32
#define u32x32 U32_32
#define f32x32 F32_32
#define s64x16 S64_16
#define u64x16 U64_16
#define f64x16 F64_16

#ifndef NO_SIMD_128
static ALWAYS_INLINE f32 sqrt_f32(f32 x)
{
	f32x4 xx;
	f32x4 yy;
	xx[0] = x;
	xx[1] = 0;
	xx[2] = 0;
	xx[3] = 0;

#if defined(SIMD_VEX)
	f32x4 zz;
	BROADCAST_4(&zz, 0);
	asm("vsqrtss %1, %2, %0" : "=x"(yy) : "x"(xx), "x"(zz) :);
#else
	asm("sqrtss %1, %0" : "=x"(yy) : "x"(xx) :);
#endif
	return yy[0];
}

static ALWAYS_INLINE f64 sqrt_f64(f64 x)
{

	f64x2 xx;
	f64x2 yy;
	xx[0] = x;
	xx[1] = 0;

#if defined(SIMD_VEX)
	f64x2 zz;
	BROADCAST_2(&zz, 0);
	asm("vsqrtsd %1, %2, %0" : "=x"(yy) : "x"(xx), "x"(zz) :);
#else
	asm("sqrtsd %1, %0" : "=x"(yy) : "x"(xx) :);
#endif
	return yy[0];
}
#endif

#ifndef NO_SIMD_128
static ALWAYS_INLINE f32x4 sqrt_f32x4(f32x4 x)
{
	f32x4 yy;

#if defined(SIMD_VEX)
	asm("vsqrtps %1, %0" : "=x"(yy) : "x"(x) :);
#else
	asm("sqrtps %1, %0" : "=x"(yy) : "x"(x) :);
#endif
	return yy;
}

static ALWAYS_INLINE f64x2 sqrt_f64x2(f64x2 x)
{
	f64x2 yy;

#if defined(SIMD_VEX)
	asm("vsqrtpd %1, %0" : "=x"(yy) : "x"(x) :);
#else
	asm("sqrtpd %1, %0" : "=x"(yy) : "x"(x) :);
#endif
	return yy;
}
#endif

#ifndef NO_SIMD_256
static ALWAYS_INLINE f32x8 sqrt_f32x8(f32x8 x)
{

#if 1
	f32x4 xx;
	f32x4 y0;
	f32x4 y1;
	f32x8 y;
	xx[0] = x[0];
	xx[1] = x[1];
	xx[2] = x[2];
	xx[3] = x[3];
	asm("vsqrtps %1, %0" : "=x"(y0) : "x"(xx) :);
	xx[0] = x[4];
	xx[1] = x[5];
	xx[2] = x[6];
	xx[3] = x[7];
	asm("vsqrtps %1, %0" : "=x"(y1) : "x"(xx) :);
	y[0] = y0[0];
	y[1] = y0[1];
	y[2] = y0[2];
	y[3] = y0[3];
	y[4] = y1[0];
	y[5] = y1[1];
	y[6] = y1[2];
	y[7] = y1[3];
	return y;
#else
	f32x8 yy;
	asm("vsqrtps %1, %0" : "=X"(yy) : "X"(x) :);
	return yy;
#endif
}

static ALWAYS_INLINE f64x4 sqrt_f64x4(f64x4 x)
{
#if 1
	f64x2 xx;
	f64x2 y0;
	f64x2 y1;
	f64x4 y;
	xx[0] = x[0];
	xx[1] = x[1];
	asm("vsqrtpd %1, %0" : "=x"(y0) : "x"(xx) :);
	xx[0] = x[2];
	xx[1] = x[3];
	asm("vsqrtpd %1, %0" : "=x"(y1) : "x"(xx) :);
	y[0] = y0[0];
	y[1] = y0[1];
	y[2] = y1[0];
	y[3] = y1[1];
	return y;
#else
	f64x4 yy;
	asm("vsqrtpd %1, %0" : "=X"(yy) : "X"(x) :);
	return yy;
#endif
}
#endif

#ifndef NO_SIMD_512
static ALWAYS_INLINE f32x16 sqrt_f32x16(f32x16 x)
{
	f32x4 xx;
	f32x4 y0;
	f32x4 y1;
	f32x4 y2;
	f32x4 y3;
	f32x16 y;
	xx[0] = x[0];
	xx[1] = x[1];
	xx[2] = x[2];
	xx[3] = x[3];
	asm("vsqrtps %1, %0" : "=x"(y0) : "x"(xx) :);
	xx[0] = x[4];
	xx[1] = x[5];
	xx[2] = x[6];
	xx[3] = x[7];
	asm("vsqrtps %1, %0" : "=x"(y1) : "x"(xx) :);
	xx[0] = x[8];
	xx[1] = x[9];
	xx[2] = x[10];
	xx[3] = x[11];
	asm("vsqrtps %1, %0" : "=x"(y2) : "x"(xx) :);
	xx[0] = x[12];
	xx[1] = x[13];
	xx[2] = x[14];
	xx[3] = x[15];
	asm("vsqrtps %1, %0" : "=x"(y3) : "x"(xx) :);
	y[0x0] = y0[0];
	y[0x1] = y0[1];
	y[0x2] = y0[2];
	y[0x3] = y0[3];
	y[0x4] = y1[0];
	y[0x5] = y1[1];
	y[0x6] = y1[2];
	y[0x7] = y1[3];
	y[0x8] = y2[0];
	y[0x9] = y2[1];
	y[0xa] = y2[2];
	y[0xb] = y2[3];
	y[0xc] = y3[0];
	y[0xd] = y3[1];
	y[0xe] = y3[2];
	y[0xf] = y3[3];
	return y;
}

static ALWAYS_INLINE f64x8 sqrt_f64x8(f64x8 x)
{

#if 1
	f64x2 xx;
	f64x2 y0;
	f64x2 y1;
	f64x2 y2;
	f64x2 y3;
	f64x8 y;

	xx[0] = x[0];
	xx[1] = x[1];
	asm("vsqrtpd %1, %0" : "=x"(y0) : "x"(xx) :);
	xx[0] = x[2];
	xx[1] = x[3];
	asm("vsqrtpd %1, %0" : "=x"(y1) : "x"(xx) :);
	xx[0] = x[4];
	xx[1] = x[5];
	asm("vsqrtpd %1, %0" : "=x"(y2) : "x"(xx) :);
	xx[0] = x[6];
	xx[1] = x[7];
	asm("vsqrtpd %1, %0" : "=x"(y3) : "x"(xx) :);

	y[0] = y0[0];
	y[1] = y0[1];
	y[2] = y1[0];
	y[3] = y1[1];
	y[4] = y2[0];
	y[5] = y2[1];
	y[6] = y3[0];
	y[7] = y3[1];
	return y;
#else
	f64x8 yy;
	asm("vsqrtpd %1, %0" : "=X"(yy) : "X"(x) :);
	return yy;
#endif
}

#endif

#ifndef NO_SIMD_1024
static ALWAYS_INLINE f32x32 sqrt_f32x32(f32x32 x)
{
	f32x4 xx;
	f32x4 y0;
	f32x4 y1;
	f32x4 y2;
	f32x4 y3;
	f32x4 y4;
	f32x4 y5;
	f32x4 y6;
	f32x4 y7;
	f32x32 y;

	xx[0] = x[0];
	xx[1] = x[1];
	xx[2] = x[2];
	xx[3] = x[3];
	asm("vsqrtps %1, %0" : "=x"(y0) : "x"(xx) :);
	xx[0] = x[4];
	xx[1] = x[5];
	xx[2] = x[6];
	xx[3] = x[7];
	asm("vsqrtps %1, %0" : "=x"(y1) : "x"(xx) :);
	xx[0] = x[8];
	xx[1] = x[9];
	xx[2] = x[10];
	xx[3] = x[11];
	asm("vsqrtps %1, %0" : "=x"(y2) : "x"(xx) :);
	xx[0] = x[12];
	xx[1] = x[13];
	xx[2] = x[14];
	xx[3] = x[15];
	asm("vsqrtps %1, %0" : "=x"(y3) : "x"(xx) :);
	xx[0] = x[16];
	xx[1] = x[17];
	xx[2] = x[18];
	xx[3] = x[19];
	asm("vsqrtps %1, %0" : "=x"(y4) : "x"(xx) :);
	xx[0] = x[20];
	xx[1] = x[21];
	xx[2] = x[22];
	xx[3] = x[23];
	asm("vsqrtps %1, %0" : "=x"(y5) : "x"(xx) :);
	xx[0] = x[24];
	xx[1] = x[25];
	xx[2] = x[26];
	xx[3] = x[27];
	asm("vsqrtps %1, %0" : "=x"(y6) : "x"(xx) :);
	xx[0] = x[28];
	xx[1] = x[29];
	xx[2] = x[30];
	xx[3] = x[31];
	asm("vsqrtps %1, %0" : "=x"(y7) : "x"(xx) :);

	y[0x0] = y0[0];
	y[0x1] = y0[1];
	y[0x2] = y0[2];
	y[0x3] = y0[3];
	y[0x4] = y1[0];
	y[0x5] = y1[1];
	y[0x6] = y1[2];
	y[0x7] = y1[3];
	y[0x8] = y2[0];
	y[0x9] = y2[1];
	y[0xa] = y2[2];
	y[0xb] = y2[3];
	y[0xc] = y3[0];
	y[0xd] = y3[1];
	y[0xe] = y3[2];
	y[0xf] = y3[3];

	y[0x10] = y4[0];
	y[0x11] = y4[1];
	y[0x12] = y4[2];
	y[0x13] = y4[3];
	y[0x14] = y5[0];
	y[0x15] = y5[1];
	y[0x16] = y5[2];
	y[0x17] = y5[3];
	y[0x18] = y6[0];
	y[0x19] = y6[1];
	y[0x1a] = y6[2];
	y[0x1b] = y6[3];
	y[0x1c] = y7[0];
	y[0x1d] = y7[1];
	y[0x1e] = y7[2];
	y[0x1f] = y7[3];
	return y;
}

static ALWAYS_INLINE f64x16 sqrt_f64x16(f64x16 x)
{
	f64x2 xx;
	f64x2 y0;
	f64x2 y1;
	f64x2 y2;
	f64x2 y3;
	f64x2 y4;
	f64x2 y5;
	f64x2 y6;
	f64x2 y7;
	f64x16 y;

	xx[0] = x[0];
	xx[1] = x[1];
	asm("vsqrtpd %1, %0" : "=x"(y0) : "x"(xx) :);
	xx[0] = x[2];
	xx[1] = x[3];
	asm("vsqrtpd %1, %0" : "=x"(y1) : "x"(xx) :);
	xx[0] = x[4];
	xx[1] = x[5];
	asm("vsqrtpd %1, %0" : "=x"(y2) : "x"(xx) :);
	xx[0] = x[6];
	xx[1] = x[7];
	asm("vsqrtpd %1, %0" : "=x"(y3) : "x"(xx) :);

	xx[0] = x[8];
	xx[1] = x[9];
	asm("vsqrtpd %1, %0" : "=x"(y4) : "x"(xx) :);
	xx[0] = x[10];
	xx[1] = x[11];
	asm("vsqrtpd %1, %0" : "=x"(y5) : "x"(xx) :);
	xx[0] = x[12];
	xx[1] = x[13];
	asm("vsqrtpd %1, %0" : "=x"(y6) : "x"(xx) :);
	xx[0] = x[14];
	xx[1] = x[15];
	asm("vsqrtpd %1, %0" : "=x"(y7) : "x"(xx) :);

	y[0] = y0[0];
	y[1] = y0[1];
	y[2] = y1[0];
	y[3] = y1[1];
	y[4] = y2[0];
	y[5] = y2[1];
	y[6] = y3[0];
	y[7] = y3[1];
	y[8] = y4[0];
	y[9] = y4[1];
	y[10] = y5[0];
	y[11] = y5[1];
	y[12] = y6[0];
	y[13] = y6[1];
	y[14] = y7[0];
	y[15] = y7[1];
	return y;
}

#endif

#if !defined(NO_SIMD_1024)
static ALWAYS_INLINE f32x32 rsqrt_f32x32(f32x32 x)
{
	f32x4 xx;
	f32x4 y0;
	f32x4 y1;
	f32x4 y2;
	f32x4 y3;
	f32x4 y4;
	f32x4 y5;
	f32x4 y6;
	f32x4 y7;
	f32x32 y;
	xx[0] = x[0];
	xx[1] = x[1];
	xx[2] = x[2];
	xx[3] = x[3];
	asm("vrsqrtps %1, %0" : "=x"(y0) : "x"(xx) :);
	xx[0] = x[4];
	xx[1] = x[5];
	xx[2] = x[6];
	xx[3] = x[7];
	asm("vrsqrtps %1, %0" : "=x"(y1) : "x"(xx) :);
	xx[0] = x[8];
	xx[1] = x[9];
	xx[2] = x[10];
	xx[3] = x[11];
	asm("vrsqrtps %1, %0" : "=x"(y2) : "x"(xx) :);
	xx[0] = x[12];
	xx[1] = x[13];
	xx[2] = x[14];
	xx[3] = x[15];
	asm("vrsqrtps %1, %0" : "=x"(y3) : "x"(xx) :);
	xx[0] = x[16];
	xx[1] = x[17];
	xx[2] = x[18];
	xx[3] = x[19];
	asm("vrsqrtps %1, %0" : "=x"(y4) : "x"(xx) :);
	xx[0] = x[20];
	xx[1] = x[21];
	xx[2] = x[22];
	xx[3] = x[23];
	asm("vrsqrtps %1, %0" : "=x"(y5) : "x"(xx) :);
	xx[0] = x[24];
	xx[1] = x[25];
	xx[2] = x[26];
	xx[3] = x[27];
	asm("vrsqrtps %1, %0" : "=x"(y6) : "x"(xx) :);
	xx[0] = x[28];
	xx[1] = x[29];
	xx[2] = x[30];
	xx[3] = x[31];
	asm("vrsqrtps %1, %0" : "=x"(y7) : "x"(xx) :);
	y[0x0] = y0[0];
	y[0x1] = y0[1];
	y[0x2] = y0[2];
	y[0x3] = y0[3];
	y[0x4] = y1[0];
	y[0x5] = y1[1];
	y[0x6] = y1[2];
	y[0x7] = y1[3];
	y[0x8] = y2[0];
	y[0x9] = y2[1];
	y[0xa] = y2[2];
	y[0xb] = y2[3];
	y[0xc] = y3[0];
	y[0xd] = y3[1];
	y[0xe] = y3[2];
	y[0xf] = y3[3];
	y[0x10] = y4[0];
	y[0x11] = y4[1];
	y[0x12] = y4[2];
	y[0x13] = y4[3];
	y[0x14] = y5[0];
	y[0x15] = y5[1];
	y[0x16] = y5[2];
	y[0x17] = y5[3];
	y[0x18] = y6[0];
	y[0x19] = y6[1];
	y[0x1a] = y6[2];
	y[0x1b] = y6[3];
	y[0x1c] = y7[0];
	y[0x1d] = y7[1];
	y[0x1e] = y7[2];
	y[0x1f] = y7[3];
	return y;
}
#endif
#if !defined(NO_SIMD_512)
static ALWAYS_INLINE f32x16 rsqrt_f32x16(f32x16 x)
{
#if 1
	f32x4 xx;
	f32x4 y0;
	f32x4 y1;
	f32x4 y2;
	f32x4 y3;
	f32x16 y;
	xx[0] = x[0];
	xx[1] = x[1];
	xx[2] = x[2];
	xx[3] = x[3];
	asm("vrsqrtps %1, %0" : "=x"(y0) : "x"(xx) :);
	xx[0] = x[4];
	xx[1] = x[5];
	xx[2] = x[6];
	xx[3] = x[7];
	asm("vrsqrtps %1, %0" : "=x"(y1) : "x"(xx) :);
	xx[0] = x[8];
	xx[1] = x[9];
	xx[2] = x[10];
	xx[3] = x[11];
	asm("vrsqrtps %1, %0" : "=x"(y2) : "x"(xx) :);
	xx[0] = x[12];
	xx[1] = x[13];
	xx[2] = x[14];
	xx[3] = x[15];
	asm("vrsqrtps %1, %0" : "=x"(y3) : "x"(xx) :);
	y[0x0] = y0[0];
	y[0x1] = y0[1];
	y[0x2] = y0[2];
	y[0x3] = y0[3];
	y[0x4] = y1[0];
	y[0x5] = y1[1];
	y[0x6] = y1[2];
	y[0x7] = y1[3];
	y[0x8] = y2[0];
	y[0x9] = y2[1];
	y[0xa] = y2[2];
	y[0xb] = y2[3];
	y[0xc] = y3[0];
	y[0xd] = y3[1];
	y[0xe] = y3[2];
	y[0xf] = y3[3];
	return y;
#else
	f32x16 yy;
	asm("vrsqrtps %1, %0" : "=X"(yy) : "X"(x) :);
	return yy;
#endif
}

#endif
#if !defined(NO_SIMD_256)
static ALWAYS_INLINE f32x8 rsqrt_f32x8(f32x8 x)
{
#if 1
	f32x4 xx;
	f32x4 y0;
	f32x4 y1;
	f32x8 y;
	xx[0] = x[0];
	xx[1] = x[1];
	xx[2] = x[2];
	xx[3] = x[3];
	asm("vrsqrtps %1, %0" : "=x"(y0) : "x"(xx) :);
	xx[0] = x[4];
	xx[1] = x[5];
	xx[2] = x[6];
	xx[3] = x[7];
	asm("vrsqrtps %1, %0" : "=x"(y1) : "x"(xx) :);
	y[0] = y0[0];
	y[1] = y0[1];
	y[2] = y0[2];
	y[3] = y0[3];
	y[4] = y1[0];
	y[5] = y1[1];
	y[6] = y1[2];
	y[7] = y1[3];
	return y;
#else
	f32x8 yy;
	asm("vrsqrtps %1, %0" : "=X"(yy) : "X"(x) :);
	return yy;
#endif
}

#endif
#if !defined(NO_SIMD_128)
static ALWAYS_INLINE f32x4 rsqrt_f32x4(f32x4 x)
{
	f32x4 yy;

#if defined(SIMD_VEX)
	asm("vrsqrtps %1, %0" : "=x"(yy) : "x"(x) :);
#else
	asm("rsqrtps %1, %0" : "=x"(yy) : "x"(x) :);
#endif
	return yy;
}

#endif

static ALWAYS_INLINE f32 rsqrt_f32(f32 x)
{
	f32x4 xx;
	f32x4 yy;
	xx[0] = x;
	xx[1] = 0;
	xx[2] = 0;
	xx[3] = 0;

#if defined(SIMD_VEX)
	f32x4 zz;
	BROADCAST_4(&zz, 0);
	asm("vrsqrtss %1, %2, %0" : "=x"(yy) : "x"(xx), "x"(zz) :);
#else
	asm("rsqrtss %1, %0" : "=x"(yy) : "x"(xx) :);
#endif
	return yy[0];
}

#define GENERATE_simd_load(type, nvec)                                          \
	static ALWAYS_INLINE type##x##nvec simd_load_##type##x##nvec(type *mem) \
	{                                                                       \
		ASSUME_ALIGNED(&mem, sizeof(type) * 4);                         \
		type##x##nvec result;                                           \
		for (U32 i = 0; i < nvec; ++i) {                                \
			result[i] = mem[i];                                     \
		}                                                               \
		return result;                                                  \
	}

#define GENERATE_simd_store(type, nvec)                                                    \
	static ALWAYS_INLINE void simd_store_##type##x##nvec(type *mem, type##x##nvec vec) \
	{                                                                                  \
		ASSUME_ALIGNED(&mem, sizeof(type) * nvec);                                 \
		for (U32 i = 0; i < nvec; ++i) {                                           \
			mem[i] = vec[i];                                                   \
		}                                                                          \
	}

#define GENERATE_simd_load_unaligned(type, nvec)                                          \
	static ALWAYS_INLINE type##x##nvec simd_load_unaligned_##type##x##nvec(type *mem) \
	{                                                                                 \
		type##x##nvec result;                                                     \
		for (U32 i = 0; i < nvec; ++i) {                                          \
			result[i] = mem[i];                                               \
		}                                                                         \
		return result;                                                            \
	}

#define GENERATE_simd_store_unaligned(type, nvec)                                                    \
	static ALWAYS_INLINE void simd_store_unaligned_##type##x##nvec(type *mem, type##x##nvec vec) \
	{                                                                                            \
		for (U32 i = 0; i < nvec; ++i) {                                                     \
			mem[i] = vec[i];                                                             \
		}                                                                                    \
	}

#define GENERATE_simd(type, nvec)                                         \
	static ALWAYS_INLINE type##x##nvec simd_##type##x##nvec(type val) \
	{                                                                 \
		type##x##nvec result;                                     \
		BROADCAST_##nvec(&result, val);                           \
		return result;                                            \
	}

/* returns bit mask */
#define GENERATE_simd_compare_less(type, masktype, nvec)                                                           \
	static ALWAYS_INLINE masktype##x##nvec simd_compare_less_##type##x##nvec(type##x##nvec x, type##x##nvec y) \
	{                                                                                                          \
		masktype##x##nvec res;                                                                             \
		for (U32 i = 0; i < nvec; ++i) {                                                                   \
			res[i] = x[i] < y[i] ? (masktype)~0uLL : 0;                                                \
		}                                                                                                  \
		return res;                                                                                        \
	}

/* returns bit mask */
#define GENERATE_simd_compare_less_eq(type, masktype, nvec)                                                           \
	static ALWAYS_INLINE masktype##x##nvec simd_compare_less_eq_##type##x##nvec(type##x##nvec x, type##x##nvec y) \
	{                                                                                                             \
		masktype##x##nvec res;                                                                                \
		for (U32 i = 0; i < nvec; ++i) {                                                                      \
			res[i] = x[i] <= y[i] ? (masktype)~0uLL : 0;                                                  \
		}                                                                                                     \
		return res;                                                                                           \
	}

/* returns bit mask */
#define GENERATE_simd_compare_eq(type, masktype, nvec)                                                           \
	static ALWAYS_INLINE masktype##x##nvec simd_compare_eq_##type##x##nvec(type##x##nvec x, type##x##nvec y) \
	{                                                                                                        \
		masktype##x##nvec res;                                                                           \
		for (U32 i = 0; i < nvec; ++i) {                                                                 \
			res[i] = x[i] == y[i] ? (masktype)~0uLL : 0;                                             \
		}                                                                                                \
		return res;                                                                                      \
	}

#define GENERATE_simd_compare_less_01(type, nvec)                                                                 \
	static ALWAYS_INLINE type##x##nvec simd_compare_less_01_##type##x##nvec(type##x##nvec x, type##x##nvec y) \
	{                                                                                                         \
		type##x##nvec res;                                                                                \
		for (U32 i = 0; i < nvec; ++i) {                                                                  \
			res[i] = x[i] < y[i];                                                                     \
		}                                                                                                 \
		return res;                                                                                       \
	}

#define GENERATE_simd_compare_less_eq_01(type, nvec)                                                                 \
	static ALWAYS_INLINE type##x##nvec simd_compare_less_eq_01_##type##x##nvec(type##x##nvec x, type##x##nvec y) \
	{                                                                                                            \
		type##x##nvec res;                                                                                   \
		for (U32 i = 0; i < nvec; ++i) {                                                                     \
			res[i] = x[i] <= y[i];                                                                       \
		}                                                                                                    \
		return res;                                                                                          \
	}

#define GENERATE_simd_compare_eq_01(type, nvec)                                                                 \
	static ALWAYS_INLINE type##x##nvec simd_compare_eq_01_##type##x##nvec(type##x##nvec x, type##x##nvec y) \
	{                                                                                                       \
		type##x##nvec res;                                                                              \
		for (U32 i = 0; i < nvec; ++i) {                                                                \
			res[i] = x[i] == y[i];                                                                  \
		}                                                                                               \
		return res;                                                                                     \
	}

#define GENERATE_simd_cast(from, to, nvec)                                                     \
	static ALWAYS_INLINE to##x##nvec simd_cast_##from##_to_##to##_x##nvec(from##x##nvec x) \
	{                                                                                      \
		to##x##nvec res;                                                               \
		for (U32 i = 0; i < nvec; ++i) {                                               \
			res[i] = x[i];                                                         \
		}                                                                              \
		return res;                                                                    \
	}

#define GENERATE_min(type)                                  \
	static ALWAYS_INLINE F32 min_##type(type x, type y) \
	{                                                   \
		return MIN(x, y);                           \
	}

#define GENERATE_max(type)                                  \
	static ALWAYS_INLINE F32 max_##type(type x, type y) \
	{                                                   \
		return MAX(x, y);                           \
	}

GENERATE_min(f32);
GENERATE_max(f32);

#ifndef NO_SIMD_128
GENERATE_cplx_sqrt(f32, 4);
GENERATE_cplx_sqrt(f64, 2);
#endif

#ifndef NO_SIMD_256
GENERATE_cplx_sqrt(f32, 8);
GENERATE_cplx_sqrt(f64, 4);
#endif

#ifndef NO_SIMD_512
GENERATE_cplx_sqrt(f32, 16);
GENERATE_cplx_sqrt(f64, 8);
#endif

GENERATE_simd_cast(s32, f32, 4);

GENERATE_simd_compare_less(f32, u32, 32);
GENERATE_simd_compare_less_eq(f32, u32, 32);
GENERATE_simd_compare_eq(f32, u32, 32);
GENERATE_simd_compare_less_eq_01(f32, 32);
GENERATE_simd_compare_eq_01(f32, 32);
GENERATE_simd_compare_less_01(f32, 32);

GENERATE_simd_compare_less(f32, u32, 16);
GENERATE_simd_compare_less_eq(f32, u32, 16);
GENERATE_simd_compare_eq(f32, u32, 16);
GENERATE_simd_compare_less_eq_01(f32, 16);
GENERATE_simd_compare_eq_01(f32, 16);
GENERATE_simd_compare_less_01(f32, 16);

GENERATE_simd_compare_less(f32, u32, 8);
GENERATE_simd_compare_less_eq(f32, u32, 8);
GENERATE_simd_compare_eq(f32, u32, 8);
GENERATE_simd_compare_less_eq_01(f32, 8);
GENERATE_simd_compare_eq_01(f32, 8);
GENERATE_simd_compare_less_01(f32, 8);

GENERATE_simd_compare_less(f32, u32, 4);
GENERATE_simd_compare_less_eq(f32, u32, 4);
GENERATE_simd_compare_eq(f32, u32, 4);
GENERATE_simd_compare_less_eq_01(f32, 4);
GENERATE_simd_compare_eq_01(f32, 4);
GENERATE_simd_compare_less_01(f32, 4);

GENERATE_simd_compare_less(f32, u32, 2);
GENERATE_simd_compare_less_eq(f32, u32, 2);
GENERATE_simd_compare_eq(f32, u32, 2);
GENERATE_simd_compare_less_eq_01(f32, 2);
GENERATE_simd_compare_eq_01(f32, 2);
GENERATE_simd_compare_less_01(f32, 2);

GENERATE_simd_load(f32, 4);
GENERATE_simd_load(f32, 8);
GENERATE_simd_load(f32, 16);
GENERATE_simd_load(f32, 32);
GENERATE_simd_load(f64, 2);
GENERATE_simd_load(f64, 4);
GENERATE_simd_load(f64, 8);

GENERATE_simd_store(f32, 4);
GENERATE_simd_store(f32, 8);
GENERATE_simd_store(f32, 16);
GENERATE_simd_store(f32, 32);
GENERATE_simd_store(f64, 2);
GENERATE_simd_store(f64, 4);
GENERATE_simd_store(f64, 8);

GENERATE_simd(f32, 4);
GENERATE_simd(f32, 32);
GENERATE_simd(f32, 16);
GENERATE_simd(f32, 8);
GENERATE_simd(u32, 4);
GENERATE_simd(s32, 4);

GENERATE_add_impl(f32, 1);
GENERATE_mul_impl(f32, 1);
GENERATE_neg_impl(f32, 1);

GENERATE_cplx_mul(f32, 1);

#define cplx_mul_f32 cplx_mul_f32x1

#if !defined(NO_SIMD_1024)
#define simd_f32x simd_f32x32
#define simd_store_f32x simd_store_f32x32
#define simd_load_f32x simd_load_f32x32
#define simd_cast_s32_to_f32_x simd_cast_s32_to_f32_x32
#define simd_compare_less_eq_01_f32x simd_compare_less_eq_01_f32x32
#define simd_compare_less_01_f32x simd_compare_less_01_f32x32
#define sqrt_f32x sqrt_f32x32
#elif !defined(NO_SIMD_512)
#define simd_f32x simd_f32x16
#define simd_store_f32x simd_store_f32x16
#define simd_load_f32x simd_load_f32x16
#define simd_cast_s32_to_f32_x simd_cast_s32_to_f32_x16
#define simd_compare_less_eq_01_f32x simd_compare_less_eq_01_f32x16
#define simd_compare_less_01_f32x simd_compare_less_01_f32x16
#define sqrt_f32x sqrt_f32x16
#elif !defined(NO_SIMD_256)
#define simd_f32x simd_f32x8
#define simd_store_f32x simd_store_f32x8
#define simd_load_f32x simd_load_f32x8
#define simd_cast_s32_to_f32_x simd_cast_s32_to_f32_x8
#define simd_compare_less_eq_01_f32x simd_compare_less_eq_01_f32x8
#define simd_compare_less_01_f32x simd_compare_less_01_f32x8
#define sqrt_f32x sqrt_f32x8
#elif !defined(NO_SIMD_128)
#define simd_f32x simd_f32x4
#define simd_store_f32x simd_store_f32x4
#define simd_load_f32x simd_load_f32x4
#define simd_cast_s32_to_f32_x simd_cast_s32_to_f32_x4
#define simd_compare_less_eq_01_f32x simd_compare_less_eq_01_f32x4
#define simd_compare_less_01_f32x simd_compare_less_01_f32x4
#define sqrt_f32x sqrt_f32x4
#elif !defined(NO_SIMD_64)
#define simd_f32x simd_f32x2
#define simd_store_f32x simd_store_f32x2
#define simd_load_f32x simd_load_f32x2
#define simd_cast_s32_to_f32_x simd_cast_s32_to_f32_x2
#define simd_compare_less_eq_01_f32x simd_compare_less_eq_01_f32x2
#define simd_compare_less_01_f32x simd_compare_less_01_f32x2
#define sqrt_f32x sqrt_f32x2
#endif

#undef s8
#undef s16
#undef s32
#undef s64
#undef s128
#undef u8
#undef u16
#undef u32
#undef u64
#undef u128
#undef f32
#undef f64
#undef f8e8s
#undef f5e11s
#undef s8x8
#undef s16x4
#undef s32x2
#undef u8x8
#undef u16x4
#undef u32x2
#undef f32x2
#undef f8e8sx4
#undef f5e11sx4
#undef s8x16
#undef s16x8
#undef s32x4
#undef s64x2
#undef u8x16
#undef u16x8
#undef u32x4
#undef u64x2
#undef f32x4
#undef f64x2
#undef f8e8sx8
#undef f5e11sx8
#undef s8x32
#undef s16x16
#undef s32x8
#undef s64x4
#undef s128x2
#undef u8x32
#undef u16x16
#undef u32x8
#undef u64x4
#undef u128x2
#undef f32x8
#undef f64x4
#undef f8e8sx16
#undef f5e11sx16
#undef s8x64
#undef s16x32
#undef s32x16
#undef s64x8
#undef s128x4
#undef u8x64
#undef u16x32
#undef u32x16
#undef u64x8
#undef u128x4
#undef f32x16
#undef f64x8
#undef f8e8sx32
#undef f5e11sx32
#undef s8x128
#undef s16x64
#undef s32x32
#undef s64x16
#undef u8x128
#undef u16x64
#undef u32x32
#undef u64x16
#undef f32x32
#undef f64x16
#undef f8e8sx64
#undef f5e11sx64

#if !defined(M_PIf)
#define M_PIf 3.14159265358979323846f
#endif

#if !defined(M_PI_2f)
#define M_PI_2f 1.57079632679489661923f
#endif

#if !defined(M_PI_4f)
#define M_PI_4f 0.78539816339744830962f
#endif

#if !defined(M_Ef)
#define M_Ef 2.7182818284590452354f
#endif
