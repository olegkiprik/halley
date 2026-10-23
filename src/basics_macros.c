
/*
 * hardware & OS
 */

#ifndef DESTRUCTIVE_INTERFERENCE_NBYTES
#define DESTRUCTIVE_INTERFERENCE_NBYTES 128
#endif

#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif

#ifndef SIMD_VEX
#endif

/*
 * assert
 */

#ifndef STATIC_ASSERT
#define STATIC_ASSERT(x) _Static_assert(x, "")
#endif
#ifndef STATIC_ASSERT_VERBOSE
#define STATIC_ASSERT_VERBOSE(x, msg) _Static_assert(x, msg)
#endif
#ifndef assert
#define assert(x) ((void)(x))
#endif

/*
 * basics
 */

#ifndef NULL
#define NULL ((void *)0)
#endif
#ifndef FNULL
#define FNULL ((void (*)(void))0)
#endif

#define STRINGIZE(x) #x
#define STRINGIZE_VALUE(x) STRINGIZE(x)

#include "basic_types.c"

#ifndef UMAX
#define UMAX U128
#endif
#ifndef SMAX
#define SMAX S128
#endif

/*
 * SIMD
 */

#define U8_8 __attribute__((__vector_size__(8), __aligned__(8))) U8
#define U16_4 __attribute__((__vector_size__(8), __aligned__(8))) U16
#define U32_2 __attribute__((__vector_size__(8), __aligned__(8))) U32
#define U64_1 U64
#define S8_8 __attribute__((__vector_size__(8), __aligned__(8))) S8
#define S16_4 __attribute__((__vector_size__(8), __aligned__(8))) S16
#define S32_2 __attribute__((__vector_size__(8), __aligned__(8))) S32
#define S64_1 S64
#define F5E11S_4 __attribute__((__vector_size__(8), __aligned__(8))) F5E11S
#define F8E8S_4 __attribute__((__vector_size__(8), __aligned__(8))) F8E8S
#define F8E24S_2 __attribute__((__vector_size__(8), __aligned__(8))) F8E24S
#define F11E53S_1 F11E53S
#define F32_2 F8E24S_2
#define F64_1 F11E53S_1

#define U8_8_NO_ALIGNED __attribute__((__vector_size__(8))) U8
#define U16_4_NO_ALIGNED __attribute__((__vector_size__(8))) U16
#define U32_2_NO_ALIGNED __attribute__((__vector_size__(8))) U32
#define U64_1_NO_ALIGNED U64
#define S8_8_NO_ALIGNED __attribute__((__vector_size__(8))) S8
#define S16_4_NO_ALIGNED __attribute__((__vector_size__(8))) S16
#define S32_2_NO_ALIGNED __attribute__((__vector_size__(8))) S32
#define S64_1_NO_ALIGNED S64
#define F5E11S_4_NO_ALIGNED __attribute__((__vector_size__(8))) F5E11S
#define F8E8S_4_NO_ALIGNED __attribute__((__vector_size__(8))) F8E8S
#define F8E24S_2_NO_ALIGNED __attribute__((__vector_size__(8))) F8E24S
#define F11E53S_1_NO_ALIGNED F11E53S
#define F32_2_NO_ALIGNED F8E24S_2_NO_ALIGNED
#define F64_1_NO_ALIGNED F11E53S_1_NO_ALIGNED

#define U8_16 __attribute__((__vector_size__(16), __aligned__(16))) U8
#define U16_8 __attribute__((__vector_size__(16), __aligned__(16))) U16
#define U32_4 __attribute__((__vector_size__(16), __aligned__(16))) U32
#define U64_2 __attribute__((__vector_size__(16), __aligned__(16))) U64
#define S8_16 __attribute__((__vector_size__(16), __aligned__(16))) S8
#define S16_8 __attribute__((__vector_size__(16), __aligned__(16))) S16
#define S32_4 __attribute__((__vector_size__(16), __aligned__(16))) S32
#define S64_2 __attribute__((__vector_size__(16), __aligned__(16))) S64
#define F5E11S_8 __attribute__((__vector_size__(16), __aligned__(16))) F5E11S
#define F8E8S_8 __attribute__((__vector_size__(16), __aligned__(16))) F8E8S
#define F8E24S_4 __attribute__((__vector_size__(16), __aligned__(16))) F8E24S
#define F11E53S_2 __attribute__((__vector_size__(16), __aligned__(16))) F11E53S
#define F32_4 F8E24S_4
#define F64_2 F11E53S_2

#define U8_16_NO_ALIGNED __attribute__((__vector_size__(16))) U8
#define U16_8_NO_ALIGNED __attribute__((__vector_size__(16))) U16
#define U32_4_NO_ALIGNED __attribute__((__vector_size__(16))) U32
#define U64_2_NO_ALIGNED __attribute__((__vector_size__(16))) U64
#define S8_16_NO_ALIGNED __attribute__((__vector_size__(16))) S8
#define S16_8_NO_ALIGNED __attribute__((__vector_size__(16))) S16
#define S32_4_NO_ALIGNED __attribute__((__vector_size__(16))) S32
#define S64_2_NO_ALIGNED __attribute__((__vector_size__(16))) S64
#define F5E11S_8_NO_ALIGNED __attribute__((__vector_size__(16))) F5E11S
#define F8E8S_8_NO_ALIGNED __attribute__((__vector_size__(16))) F8E8S
#define F8E24S_4_NO_ALIGNED __attribute__((__vector_size__(16))) F8E24S
#define F11E53S_2_NO_ALIGNED __attribute__((__vector_size__(16))) F11E53S
#define F32_4_NO_ALIGNED F8E24S_4_NO_ALIGNED
#define F64_2_NO_ALIGNED F11E53S_2_NO_ALIGNED

#define U8_32 __attribute__((__vector_size__(32), __aligned__(32))) U8
#define U16_16 __attribute__((__vector_size__(32), __aligned__(32))) U16
#define U32_8 __attribute__((__vector_size__(32), __aligned__(32))) U32
#define U64_4 __attribute__((__vector_size__(32), __aligned__(32))) U64
#define S8_32 __attribute__((__vector_size__(32), __aligned__(32))) S8
#define S16_16 __attribute__((__vector_size__(32), __aligned__(32))) S16
#define S32_8 __attribute__((__vector_size__(32), __aligned__(32))) S32
#define S64_4 __attribute__((__vector_size__(32), __aligned__(32))) S64
#define F5E11S_16 __attribute__((__vector_size__(32), __aligned__(32))) F5E11S
#define F8E8S_16 __attribute__((__vector_size__(32), __aligned__(32))) F8E8S
#define F8E24S_8 __attribute__((__vector_size__(32), __aligned__(32))) F8E24S
#define F11E53S_4 __attribute__((__vector_size__(32), __aligned__(32))) F11E53S
#define F32_8 F8E24S_8
#define F64_4 F11E53S_4

#define U8_32_NO_ALIGNED __attribute__((__vector_size__(32))) U8
#define U16_16_NO_ALIGNED __attribute__((__vector_size__(32))) U16
#define U32_8_NO_ALIGNED __attribute__((__vector_size__(32))) U32
#define U64_4_NO_ALIGNED __attribute__((__vector_size__(32))) U64
#define S8_32_NO_ALIGNED __attribute__((__vector_size__(32))) S8
#define S16_16_NO_ALIGNED __attribute__((__vector_size__(32))) S16
#define S32_8_NO_ALIGNED __attribute__((__vector_size__(32))) S32
#define S64_4_NO_ALIGNED __attribute__((__vector_size__(32))) S64
#define F5E11S_16_NO_ALIGNED __attribute__((__vector_size__(32))) F5E11S
#define F8E8S_16_NO_ALIGNED __attribute__((__vector_size__(32))) F8E8S
#define F8E24S_8_NO_ALIGNED __attribute__((__vector_size__(32))) F8E24S
#define F11E53S_4_NO_ALIGNED __attribute__((__vector_size__(32))) F11E53S
#define F32_8_NO_ALIGNED F8E24S_8_NO_ALIGNED
#define F64_4_NO_ALIGNED F11E53S_4_NO_ALIGNED

#define U8_64 __attribute__((__vector_size__(64), __aligned__(64))) U8
#define U16_32 __attribute__((__vector_size__(64), __aligned__(64))) U16
#define U32_16 __attribute__((__vector_size__(64), __aligned__(64))) U32
#define U64_8 __attribute__((__vector_size__(64), __aligned__(64))) U64
#define S8_64 __attribute__((__vector_size__(64), __aligned__(64))) S8
#define S16_32 __attribute__((__vector_size__(64), __aligned__(64))) S16
#define S32_16 __attribute__((__vector_size__(64), __aligned__(64))) S32
#define S64_8 __attribute__((__vector_size__(64), __aligned__(64))) S64
#define F5E11S_32 __attribute__((__vector_size__(64), __aligned__(64))) F5E11S
#define F8E8S_32 __attribute__((__vector_size__(64), __aligned__(64))) F8E8S
#define F8E24S_16 __attribute__((__vector_size__(64), __aligned__(64))) F8E24S
#define F11E53S_8 __attribute__((__vector_size__(64), __aligned__(64))) F11E53S
#define F32_16 F8E24S_16
#define F64_8 F11E53S_8

#define U8_64_NO_ALIGNED __attribute__((__vector_size__(64))) U8
#define U16_32_NO_ALIGNED __attribute__((__vector_size__(64))) U16
#define U32_16_NO_ALIGNED __attribute__((__vector_size__(64))) U32
#define U64_8_NO_ALIGNED __attribute__((__vector_size__(64))) U64
#define S8_64_NO_ALIGNED __attribute__((__vector_size__(64))) S8
#define S16_32_NO_ALIGNED __attribute__((__vector_size__(64))) S16
#define S32_16_NO_ALIGNED __attribute__((__vector_size__(64))) S32
#define S64_8_NO_ALIGNED __attribute__((__vector_size__(64))) S64
#define F5E11S_32_NO_ALIGNED __attribute__((__vector_size__(64))) F5E11S
#define F8E8S_32_NO_ALIGNED __attribute__((__vector_size__(64))) F8E8S
#define F8E24S_16_NO_ALIGNED __attribute__((__vector_size__(64))) F8E24S
#define F11E53S_8_NO_ALIGNED __attribute__((__vector_size__(64))) F11E53S
#define F32_16_NO_ALIGNED F8E24S_16_NO_ALIGNED
#define F64_8_NO_ALIGNED F11E53S_8_NO_ALIGNED

#define U8_128 __attribute__((__vector_size__(128), __aligned__(128))) U8
#define U16_64 __attribute__((__vector_size__(128), __aligned__(128))) U16
#define U32_32 __attribute__((__vector_size__(128), __aligned__(128))) U32
#define U64_16 __attribute__((__vector_size__(128), __aligned__(128))) U64
#define S8_128 __attribute__((__vector_size__(128), __aligned__(128))) S8
#define S16_64 __attribute__((__vector_size__(128), __aligned__(128))) S16
#define S32_32 __attribute__((__vector_size__(128), __aligned__(128))) S32
#define S64_16 __attribute__((__vector_size__(128), __aligned__(128))) S64
#define F5E11S_64 __attribute__((__vector_size__(128), __aligned__(128))) F5E11S
#define F8E8S_64 __attribute__((__vector_size__(128), __aligned__(128))) F8E8S
#define F8E24S_32 __attribute__((__vector_size__(128), __aligned__(128))) F8E24S
#define F11E53S_16 __attribute__((__vector_size__(128), __aligned__(128))) F11E53S
#define F32_32 F8E24S_32
#define F64_16 F11E53S_16

#define U8_128_NO_ALIGNED __attribute__((__vector_size__(128))) U8
#define U16_64_NO_ALIGNED __attribute__((__vector_size__(128))) U16
#define U32_32_NO_ALIGNED __attribute__((__vector_size__(128))) U32
#define U64_16_NO_ALIGNED __attribute__((__vector_size__(128))) U64
#define S8_128_NO_ALIGNED __attribute__((__vector_size__(128))) S8
#define S16_64_NO_ALIGNED __attribute__((__vector_size__(128))) S16
#define S32_32_NO_ALIGNED __attribute__((__vector_size__(128))) S32
#define S64_16_NO_ALIGNED __attribute__((__vector_size__(128))) S64
#define F5E11S_64_NO_ALIGNED __attribute__((__vector_size__(128))) F5E11S
#define F8E8S_64_NO_ALIGNED __attribute__((__vector_size__(128))) F8E8S
#define F8E24S_32_NO_ALIGNED __attribute__((__vector_size__(128))) F8E24S
#define F11E53S_16_NO_ALIGNED __attribute__((__vector_size__(128))) F11E53S
#define F32_32_NO_ALIGNED F8E24S_32_NO_ALIGNED
#define F64_16_NO_ALIGNED F11E53S_16_NO_ALIGNED

#if !defined(NO_SIMD_1024)
#define SIMD_N_8 128
#define SIMD_N_16 64
#define SIMD_N_32 32
#define SIMD_N_64 16
#define U8_VEC U8_128
#define U16_VEC U16_64
#define U32_VEC U32_32
#define U64_VEC U64_16
#define S8_VEC S8_128
#define S16_VEC S16_64
#define S32_VEC S32_32
#define S64_VEC S64_16
#define F5E11S_VEC F5E11S_64
#define F8E8S_VEC F8E8S_64
#define F8E24S_VEC F8E24S_32
#define F11E53S_VEC F11E53S_16
#define F32_VEC F32_32
#define F64_VEC F64_16
#define U8_VEC_NO_ALIGNED U8_128_NO_ALIGNED
#define U16_VEC_NO_ALIGNED U16_64_NO_ALIGNED
#define U32_VEC_NO_ALIGNED U32_32_NO_ALIGNED
#define U64_VEC_NO_ALIGNED U64_16_NO_ALIGNED
#define S8_VEC_NO_ALIGNED S8_128_NO_ALIGNED
#define S16_VEC_NO_ALIGNED S16_64_NO_ALIGNED
#define S32_VEC_NO_ALIGNED S32_32_NO_ALIGNED
#define S64_VEC_NO_ALIGNED S64_16_NO_ALIGNED
#define F5E11S_VEC_NO_ALIGNED F5E11S_64_NO_ALIGNED
#define F8E8S_VEC_NO_ALIGNED F8E8S_64_NO_ALIGNED
#define F8E24S_VEC_NO_ALIGNED F8E24S_32_NO_ALIGNED
#define F11E53S_VEC_NO_ALIGNED F11E53S_16_NO_ALIGNED
#define F32_VEC_NO_ALIGNED F32_32_NO_ALIGNED
#define F64_VEC_NO_ALIGNED F64_16_NO_ALIGNED
#elif !defined(NO_SIMD_512)
#define SIMD_N_8 64
#define SIMD_N_16 32
#define SIMD_N_32 16
#define SIMD_N_64 8
#define U8_VEC U8_64
#define U16_VEC U16_32
#define U32_VEC U32_16
#define U64_VEC U64_8
#define S8_VEC S8_64
#define S16_VEC S16_32
#define S32_VEC S32_16
#define S64_VEC S64_8
#define F5E11S_VEC F5E11S_32
#define F8E8S_VEC F8E8S_32
#define F8E24S_VEC F8E24S_16
#define F11E53S_VEC F11E53S_8
#define F32_VEC F32_16
#define F64_VEC F64_8
#define U8_VEC_NO_ALIGNED U8_64_NO_ALIGNED
#define U16_VEC_NO_ALIGNED U16_32_NO_ALIGNED
#define U32_VEC_NO_ALIGNED U32_16_NO_ALIGNED
#define U64_VEC_NO_ALIGNED U64_8_NO_ALIGNED
#define S8_VEC_NO_ALIGNED S8_64_NO_ALIGNED
#define S16_VEC_NO_ALIGNED S16_32_NO_ALIGNED
#define S32_VEC_NO_ALIGNED S32_16_NO_ALIGNED
#define S64_VEC_NO_ALIGNED S64_8_NO_ALIGNED
#define F5E11S_VEC_NO_ALIGNED F5E11S_32_NO_ALIGNED
#define F8E8S_VEC_NO_ALIGNED F8E8S_32_NO_ALIGNED
#define F8E24S_VEC_NO_ALIGNED F8E24S_16_NO_ALIGNED
#define F11E53S_VEC_NO_ALIGNED F11E53S_8_NO_ALIGNED
#define F32_VEC_NO_ALIGNED F32_16_NO_ALIGNED
#define F64_VEC_NO_ALIGNED F64_8_NO_ALIGNED
#elif !defined(NO_SIMD_256)
#define SIMD_N_8 32
#define SIMD_N_16 16
#define SIMD_N_32 8
#define SIMD_N_64 4
#define U8_VEC U8_32
#define U16_VEC U16_16
#define U32_VEC U32_8
#define U64_VEC U64_4
#define S8_VEC S8_32
#define S16_VEC S16_16
#define S32_VEC S32_8
#define S64_VEC S64_4
#define F5E11S_VEC F5E11S_16
#define F8E8S_VEC F8E8S_16
#define F8E24S_VEC F8E24S_8
#define F11E53S_VEC F11E53S_4
#define F32_VEC F32_8
#define F64_VEC F64_4
#define U8_VEC_NO_ALIGNED U8_32_NO_ALIGNED
#define U16_VEC_NO_ALIGNED U16_16_NO_ALIGNED
#define U32_VEC_NO_ALIGNED U32_8_NO_ALIGNED
#define U64_VEC_NO_ALIGNED U64_4_NO_ALIGNED
#define S8_VEC_NO_ALIGNED S8_32_NO_ALIGNED
#define S16_VEC_NO_ALIGNED S16_16_NO_ALIGNED
#define S32_VEC_NO_ALIGNED S32_8_NO_ALIGNED
#define S64_VEC_NO_ALIGNED S64_4_NO_ALIGNED
#define F5E11S_VEC_NO_ALIGNED F5E11S_16_NO_ALIGNED
#define F8E8S_VEC_NO_ALIGNED F8E8S_16_NO_ALIGNED
#define F8E24S_VEC_NO_ALIGNED F8E24S_8_NO_ALIGNED
#define F11E53S_VEC_NO_ALIGNED F11E53S_4_NO_ALIGNED
#define F32_VEC_NO_ALIGNED F32_8_NO_ALIGNED
#define F64_VEC_NO_ALIGNED F64_4_NO_ALIGNED
#elif !defined(NO_SIMD_128)
#define SIMD_N_8 16
#define SIMD_N_16 8
#define SIMD_N_32 4
#define SIMD_N_64 2
#define U8_VEC U8_16
#define U16_VEC U16_8
#define U32_VEC U32_4
#define U64_VEC U64_2
#define S8_VEC S8_16
#define S16_VEC S16_8
#define S32_VEC S32_4
#define S64_VEC S64_2
#define F5E11S_VEC F5E11S_8
#define F8E8S_VEC F8E8S_8
#define F8E24S_VEC F8E24S_4
#define F11E53S_VEC F11E53S_2
#define F32_VEC F32_4
#define F64_VEC F64_2
#define U8_VEC_NO_ALIGNED U8_16_NO_ALIGNED
#define U16_VEC_NO_ALIGNED U16_8_NO_ALIGNED
#define U32_VEC_NO_ALIGNED U32_4_NO_ALIGNED
#define U64_VEC_NO_ALIGNED U64_2_NO_ALIGNED
#define S8_VEC_NO_ALIGNED S8_16_NO_ALIGNED
#define S16_VEC_NO_ALIGNED S16_8_NO_ALIGNED
#define S32_VEC_NO_ALIGNED S32_4_NO_ALIGNED
#define S64_VEC_NO_ALIGNED S64_2_NO_ALIGNED
#define F5E11S_VEC_NO_ALIGNED F5E11S_8_NO_ALIGNED
#define F8E8S_VEC_NO_ALIGNED F8E8S_8_NO_ALIGNED
#define F8E24S_VEC_NO_ALIGNED F8E24S_4_NO_ALIGNED
#define F11E53S_VEC_NO_ALIGNED F11E53S_2_NO_ALIGNED
#define F32_VEC_NO_ALIGNED F32_4_NO_ALIGNED
#define F64_VEC_NO_ALIGNED F64_2_NO_ALIGNED
#elif !defined(NO_SIMD_64)
#define SIMD_N_8 8
#define SIMD_N_16 4
#define SIMD_N_32 2
#define SIMD_N_64 1
#define U8_VEC U8_8
#define U16_VEC U16_4
#define U32_VEC U32_2
#define U64_VEC U64_1
#define S8_VEC S8_8
#define S16_VEC S16_4
#define S32_VEC S32_2
#define S64_VEC S64_1
#define F5E11S_VEC F5E11S_4
#define F8E8S_VEC F8E8S_4
#define F8E24S_VEC F8E24S_2
#define F11E53S_VEC F11E53S_1
#define F32_VEC F32_2
#define F64_VEC F64_1
#define U8_VEC_NO_ALIGNED U8_8_NO_ALIGNED
#define U16_VEC_NO_ALIGNED U16_4_NO_ALIGNED
#define U32_VEC_NO_ALIGNED U32_2_NO_ALIGNED
#define U64_VEC_NO_ALIGNED U64_1_NO_ALIGNED
#define S8_VEC_NO_ALIGNED S8_8_NO_ALIGNED
#define S16_VEC_NO_ALIGNED S16_4_NO_ALIGNED
#define S32_VEC_NO_ALIGNED S32_2_NO_ALIGNED
#define S64_VEC_NO_ALIGNED S64_1_NO_ALIGNED
#define F5E11S_VEC_NO_ALIGNED F5E11S_4_NO_ALIGNED
#define F8E8S_VEC_NO_ALIGNED F8E8S_4_NO_ALIGNED
#define F8E24S_VEC_NO_ALIGNED F8E24S_2_NO_ALIGNED
#define F11E53S_VEC_NO_ALIGNED F11E53S_1_NO_ALIGNED
#define F32_VEC_NO_ALIGNED F32_2_NO_ALIGNED
#define F64_VEC_NO_ALIGNED F64_1_NO_ALIGNED
#endif

#define SIMD_NBYTES (SIMD_N_8 * 8 / CHAR_BIT)

/*
 * advanced features
 */

#ifndef THREAD_LOCAL
#define THREAD_LOCAL __thread
#endif

#ifndef NOINLINE
#define NOINLINE __attribute__((noinline))
#endif
#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE __attribute__((always_inline))
#endif
#ifndef PRAGMA_DO_NOT_UNROLL
#define PRAGMA_DO_NOT_UNROLL _Pragma("clang loop unroll(disable)")
#endif

#ifndef asm
#define asm __asm__
#endif

#ifndef ASM_NOOPT
#define ASM_NOOPT(x)                \
	do {                        \
		asm("" ::"r,i"(x)); \
	} while (0 != 0)
#endif

#define ALIGNAS(n) _Alignas(n)
#ifndef OPTIONAL_ALIGNAS
#define OPTIONAL_ALIGNAS(n) ALIGNAS(n)
#endif

/*
 * atomic
 */

#if 01

#define ATOMIC
#define ATOMIC_LOAD(nbits, p, mo) (__atomic_load_n(p, mo))
#define ATOMIC_STORE(nbits, p, v, mo) (__atomic_store_n(p, v, mo))
#define ATOMIC_EXCHANGE(nbits, p, v, mo) (__atomic_exchange_n(p, v, mo))
#define ATOMIC_COMPARE_EXCHANGE_WEAK(nbits, p, pe, vd, mos, mof) \
	(__atomic_compare_exchange_n(p, pe, vd, 1 == 1, mos, mof) ? 0 : 1)
#define ATOMIC_COMPARE_EXCHANGE_STRONG(nbits, p, pe, vd, mos, mof) \
	(__atomic_compare_exchange_n(p, pe, vd, 0 != 0, mos, mof) ? 0 : 1)
#define ATOMIC_FETCH_ADD(nbits, p, v, mo) (__atomic_fetch_add(p, v, mo))
#define ATOMIC_FETCH_SUB(nbits, p, v, mo) (__atomic_fetch_sub(p, v, mo))
#define ATOMIC_FETCH_AND(nbits, p, v, mo) (__atomic_fetch_and(p, v, mo))
#define ATOMIC_FETCH_XOR(nbits, p, v, mo) (__atomic_fetch_xor(p, v, mo))
#define ATOMIC_FETCH_OR(nbits, p, v, mo) (__atomic_fetch_or(p, v, mo))
#define ATOMIC_ACQUIRE __ATOMIC_ACQUIRE
#define ATOMIC_RELEASE __ATOMIC_RELEASE
#define ATOMIC_SEQ_CST __ATOMIC_SEQ_CST
#define ATOMIC_ACQ_REL __ATOMIC_ACQ_REL
#define ATOMIC_RELAXED __ATOMIC_RELAXED
/* consider volatile! */
#define ATOMIC_LOAD_NON_ATOMIC(nbits, p) (*(p))
/* consider volatile! */
#define ATOMIC_STORE_NON_ATOMIC(nbits, p, v) \
	do {                                 \
		*(p) = (v);                  \
	} while (0 != 0)
#define ATOMIC_THREAD_FENCE_ACQUIRE() (__atomic_thread_fence(ATOMIC_ACQUIRE))
#define ATOMIC_THREAD_FENCE_ACQ_REL() (__atomic_thread_fence(ATOMIC_ACQ_REL))
#define ATOMIC_THREAD_FENCE_RELEASE() (__atomic_thread_fence(ATOMIC_RELEASE))
#define ATOMIC_THREAD_FENCE_SEQ_CST() (__atomic_thread_fence(ATOMIC_SEQ_CST))
#define ATOMIC_SIGNAL_FENCE_ACQUIRE() (__atomic_signal_fence(ATOMIC_ACQUIRE))
#define ATOMIC_SIGNAL_FENCE_ACQ_REL() (__atomic_signal_fence(ATOMIC_ACQ_REL))
#define ATOMIC_SIGNAL_FENCE_RELEASE() (__atomic_signal_fence(ATOMIC_RELEASE))
#define ATOMIC_SIGNAL_FENCE_SEQ_CST() (__atomic_signal_fence(ATOMIC_SEQ_CST))
#define ATOMIC_ALWAYS_LOCK_FREE(nbytes) \
	(__atomic_always_lock_free(nbytes, 0) ? 1 : 0) /* comma hacking, no default parameters, caught */

#else

#define ATOMIC _Atomic
#define ATOMIC_LOAD(nbits, p, mo) (atomic_load_explicit(p, mo))
#define ATOMIC_STORE(nbits, p, v, mo) (atomic_store_explicit(p, v, mo))
#define ATOMIC_EXCHANGE(nbits, p, v, mo) (atomic_exchange_explicit(p, v, mo))
#define ATOMIC_COMPARE_EXCHANGE_WEAK(nbits, p, pe, vd, mos, mof) \
	(atomic_compare_exchange_weak_explicit(p, pe, vd, 1 == 1, mos, mof) ? 0 : 1)
#define ATOMIC_COMPARE_EXCHANGE_STRONG(nbits, p, pe, vd, mos, mof) \
	(atomic_compare_exchange_strong_explicit(p, pe, vd, 0 != 0, mos, mof) ? 0 : 1)
#define ATOMIC_FETCH_ADD(nbits, p, v, mo) (atomic_fetch_add_explicit(p, v, mo))
#define ATOMIC_FETCH_SUB(nbits, p, v, mo) (atomic_fetch_sub_explicit(p, v, mo))
#define ATOMIC_FETCH_AND(nbits, p, v, mo) (atomic_fetch_and_explicit(p, v, mo))
#define ATOMIC_FETCH_XOR(nbits, p, v, mo) (atomic_fetch_xor_explicit(p, v, mo))
#define ATOMIC_FETCH_OR(nbits, p, v, mo) (atomic_fetch_or_explicit(p, v, mo))
#define ATOMIC_ACQUIRE memory_order_acquire
#define ATOMIC_RELEASE memory_order_release
#define ATOMIC_SEQ_CST memory_order_seq_cst
#define ATOMIC_ACQ_REL memory_order_acq_rel
#define ATOMIC_RELAXED memory_order_relaxed
#define ATOMIC_LOAD_NON_ATOMIC(nbits, p) ATOMIC_LOAD(p, ATOMIC_RELAXED)
#define ATOMIC_STORE_NON_ATOMIC(nbits, p, v) ATOMIC_STORE(p, v, ATOMIC_RELAXED)
#define ATOMIC_THREAD_FENCE_ACQUIRE() (atomic_thread_fence(ATOMIC_ACQUIRE))
#define ATOMIC_THREAD_FENCE_ACQ_REL() (atomic_thread_fence(ATOMIC_ACQ_REL))
#define ATOMIC_THREAD_FENCE_RELEASE() (atomic_thread_fence(ATOMIC_RELEASE))
#define ATOMIC_THREAD_FENCE_SEQ_CST() (atomic_thread_fence(ATOMIC_SEQ_CST))
#define ATOMIC_SIGNAL_FENCE_ACQUIRE() (atomic_signal_fence(ATOMIC_ACQUIRE))
#define ATOMIC_SIGNAL_FENCE_ACQ_REL() (atomic_signal_fence(ATOMIC_ACQ_REL))
#define ATOMIC_SIGNAL_FENCE_RELEASE() (atomic_signal_fence(ATOMIC_RELEASE))
#define ATOMIC_SIGNAL_FENCE_SEQ_CST() (atomic_signal_fence(ATOMIC_SEQ_CST))
#define ATOMIC_ALWAYS_LOCK_FREE(nbytes) \
	(__atomic_always_lock_free(nbytes, 0) ? 1 : 0) /* comma hacking, no default parameters, caught */

#endif

/*
 * assumptions
 */

#ifndef OFTEN
#define OFTEN(x) __builtin_expect_with_probability(x, 1, 0.9)
#endif
#ifndef RARELY
#define RARELY(x) __builtin_expect_with_probability(x, 0, 0.9)
#endif
#define MORE_LIKELY(x) __builtin_expect_with_probability((x), 1, 0.6)
#define LESS_LIKELY(x) __builtin_expect_with_probability((x), 0, 0.6)
#ifndef ALWAYS
#define ALWAYS(x)                                \
	do {                                     \
		if (!(x)) {                      \
			__builtin_unreachable(); \
		}                                \
	} while (0 != 0)
#endif
#ifndef NEVER
#define NEVER(x)                                 \
	do {                                     \
		if (x) {                         \
			__builtin_unreachable(); \
		}                                \
	} while (0 != 0)
#endif
#define UNPREDICTABLE(x) (__builtin_unpredictable(x))
#define NONDETERMINISTIC(nbits, p) (__builtin_nondeterministic(*(p)))
#ifndef ASSUME_ALIGNED
#define ASSUME_ALIGNED(pptr, alignment)                                    \
	do {                                                               \
		*(pptr) = __builtin_assume_aligned(*(pptr), alignment, 0); \
	} while (0 != 0)
#endif
#ifndef MAY_ALIAS
#define MAY_ALIAS __attribute__((__may_alias__))
#endif
#ifndef PTR_ALIAS
#define PTR_ALIAS(type, x) ((type)(x))
#endif
/*
 * use newer clang
 *
 * assume_dereferenceable(x);
 * x = __assume_aligned(x);
 * assume_aligned(&x);
 */
#ifndef ASSUME_DEREFERENCEABLE
#define ASSUME_DEREFERENCEABLE(p, nbytes) (__builtin_assume_dereferenceable(p, nbytes))
#endif

/*
 * convenience
 */

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof *(x))

#define SIMD_REFER_1(x) (&(x))
#define SIMD_REFER_2(x) (x)
#define SIMD_REFER_4(x) (x)
#define SIMD_REFER_8(x) (x)
#define SIMD_REFER_16(x) (x)
#define SIMD_REFER_32(x) (x)
#define SIMD_REFER_64(x) (x)

#define BROADCAST_1(x, y)     \
	do {                  \
		(*(x)) = (y); \
	} while (0 != 0)
#define BROADCAST_2(x, y)        \
	do {                     \
		(*(x))[0] = (y); \
		(*(x))[1] = (y); \
	} while (0 != 0)
#define BROADCAST_4(x, y)        \
	do {                     \
		(*(x))[0] = (y); \
		(*(x))[1] = (y); \
		(*(x))[2] = (y); \
		(*(x))[3] = (y); \
	} while (0 != 0)
#define BROADCAST_8(x, y)        \
	do {                     \
		(*(x))[0] = (y); \
		(*(x))[1] = (y); \
		(*(x))[2] = (y); \
		(*(x))[3] = (y); \
		(*(x))[4] = (y); \
		(*(x))[5] = (y); \
		(*(x))[6] = (y); \
		(*(x))[7] = (y); \
	} while (0 != 0)
#define BROADCAST_16(x, y)         \
	do {                       \
		(*(x))[0] = (y);   \
		(*(x))[1] = (y);   \
		(*(x))[2] = (y);   \
		(*(x))[3] = (y);   \
		(*(x))[4] = (y);   \
		(*(x))[5] = (y);   \
		(*(x))[6] = (y);   \
		(*(x))[7] = (y);   \
		(*(x))[8] = (y);   \
		(*(x))[9] = (y);   \
		(*(x))[0xa] = (y); \
		(*(x))[0xb] = (y); \
		(*(x))[0xc] = (y); \
		(*(x))[0xd] = (y); \
		(*(x))[0xe] = (y); \
		(*(x))[0xf] = (y); \
	} while (0 != 0)
#define BROADCAST_32(x, y)          \
	do {                        \
		(*(x))[0] = (y);    \
		(*(x))[1] = (y);    \
		(*(x))[2] = (y);    \
		(*(x))[3] = (y);    \
		(*(x))[4] = (y);    \
		(*(x))[5] = (y);    \
		(*(x))[6] = (y);    \
		(*(x))[7] = (y);    \
		(*(x))[8] = (y);    \
		(*(x))[9] = (y);    \
		(*(x))[0xa] = (y);  \
		(*(x))[0xb] = (y);  \
		(*(x))[0xc] = (y);  \
		(*(x))[0xd] = (y);  \
		(*(x))[0xe] = (y);  \
		(*(x))[0xf] = (y);  \
		(*(x))[0x10] = (y); \
		(*(x))[0x11] = (y); \
		(*(x))[0x12] = (y); \
		(*(x))[0x13] = (y); \
		(*(x))[0x14] = (y); \
		(*(x))[0x15] = (y); \
		(*(x))[0x16] = (y); \
		(*(x))[0x17] = (y); \
		(*(x))[0x18] = (y); \
		(*(x))[0x19] = (y); \
		(*(x))[0x1a] = (y); \
		(*(x))[0x1b] = (y); \
		(*(x))[0x1c] = (y); \
		(*(x))[0x1d] = (y); \
		(*(x))[0x1e] = (y); \
		(*(x))[0x1f] = (y); \
	} while (0 != 0)
#define BROADCAST_64(x, y)          \
	do {                        \
		(*(x))[0] = (y);    \
		(*(x))[1] = (y);    \
		(*(x))[2] = (y);    \
		(*(x))[3] = (y);    \
		(*(x))[4] = (y);    \
		(*(x))[5] = (y);    \
		(*(x))[6] = (y);    \
		(*(x))[7] = (y);    \
		(*(x))[8] = (y);    \
		(*(x))[9] = (y);    \
		(*(x))[0xa] = (y);  \
		(*(x))[0xb] = (y);  \
		(*(x))[0xc] = (y);  \
		(*(x))[0xd] = (y);  \
		(*(x))[0xe] = (y);  \
		(*(x))[0xf] = (y);  \
		(*(x))[0x10] = (y); \
		(*(x))[0x11] = (y); \
		(*(x))[0x12] = (y); \
		(*(x))[0x13] = (y); \
		(*(x))[0x14] = (y); \
		(*(x))[0x15] = (y); \
		(*(x))[0x16] = (y); \
		(*(x))[0x17] = (y); \
		(*(x))[0x18] = (y); \
		(*(x))[0x19] = (y); \
		(*(x))[0x1a] = (y); \
		(*(x))[0x1b] = (y); \
		(*(x))[0x1c] = (y); \
		(*(x))[0x1d] = (y); \
		(*(x))[0x1e] = (y); \
		(*(x))[0x1f] = (y); \
		(*(x))[0x20] = (y); \
		(*(x))[0x21] = (y); \
		(*(x))[0x22] = (y); \
		(*(x))[0x23] = (y); \
		(*(x))[0x24] = (y); \
		(*(x))[0x25] = (y); \
		(*(x))[0x26] = (y); \
		(*(x))[0x27] = (y); \
		(*(x))[0x28] = (y); \
		(*(x))[0x29] = (y); \
		(*(x))[0x2a] = (y); \
		(*(x))[0x2b] = (y); \
		(*(x))[0x2c] = (y); \
		(*(x))[0x2d] = (y); \
		(*(x))[0x2e] = (y); \
		(*(x))[0x2f] = (y); \
		(*(x))[0x30] = (y); \
		(*(x))[0x31] = (y); \
		(*(x))[0x32] = (y); \
		(*(x))[0x33] = (y); \
		(*(x))[0x34] = (y); \
		(*(x))[0x35] = (y); \
		(*(x))[0x36] = (y); \
		(*(x))[0x37] = (y); \
		(*(x))[0x38] = (y); \
		(*(x))[0x39] = (y); \
		(*(x))[0x3a] = (y); \
		(*(x))[0x3b] = (y); \
		(*(x))[0x3c] = (y); \
		(*(x))[0x3d] = (y); \
		(*(x))[0x3e] = (y); \
		(*(x))[0x3f] = (y); \
	} while (0 != 0)
#define BROADCAST_128(x, y)         \
	do {                        \
		(*(x))[0] = (y);    \
		(*(x))[1] = (y);    \
		(*(x))[2] = (y);    \
		(*(x))[3] = (y);    \
		(*(x))[4] = (y);    \
		(*(x))[5] = (y);    \
		(*(x))[6] = (y);    \
		(*(x))[7] = (y);    \
		(*(x))[8] = (y);    \
		(*(x))[9] = (y);    \
		(*(x))[0xa] = (y);  \
		(*(x))[0xb] = (y);  \
		(*(x))[0xc] = (y);  \
		(*(x))[0xd] = (y);  \
		(*(x))[0xe] = (y);  \
		(*(x))[0xf] = (y);  \
		(*(x))[0x10] = (y); \
		(*(x))[0x11] = (y); \
		(*(x))[0x12] = (y); \
		(*(x))[0x13] = (y); \
		(*(x))[0x14] = (y); \
		(*(x))[0x15] = (y); \
		(*(x))[0x16] = (y); \
		(*(x))[0x17] = (y); \
		(*(x))[0x18] = (y); \
		(*(x))[0x19] = (y); \
		(*(x))[0x1a] = (y); \
		(*(x))[0x1b] = (y); \
		(*(x))[0x1c] = (y); \
		(*(x))[0x1d] = (y); \
		(*(x))[0x1e] = (y); \
		(*(x))[0x1f] = (y); \
		(*(x))[0x20] = (y); \
		(*(x))[0x21] = (y); \
		(*(x))[0x22] = (y); \
		(*(x))[0x23] = (y); \
		(*(x))[0x24] = (y); \
		(*(x))[0x25] = (y); \
		(*(x))[0x26] = (y); \
		(*(x))[0x27] = (y); \
		(*(x))[0x28] = (y); \
		(*(x))[0x29] = (y); \
		(*(x))[0x2a] = (y); \
		(*(x))[0x2b] = (y); \
		(*(x))[0x2c] = (y); \
		(*(x))[0x2d] = (y); \
		(*(x))[0x2e] = (y); \
		(*(x))[0x2f] = (y); \
		(*(x))[0x30] = (y); \
		(*(x))[0x31] = (y); \
		(*(x))[0x32] = (y); \
		(*(x))[0x33] = (y); \
		(*(x))[0x34] = (y); \
		(*(x))[0x35] = (y); \
		(*(x))[0x36] = (y); \
		(*(x))[0x37] = (y); \
		(*(x))[0x38] = (y); \
		(*(x))[0x39] = (y); \
		(*(x))[0x3a] = (y); \
		(*(x))[0x3b] = (y); \
		(*(x))[0x3c] = (y); \
		(*(x))[0x3d] = (y); \
		(*(x))[0x3e] = (y); \
		(*(x))[0x3f] = (y); \
		(*(x))[0x40] = (y); \
		(*(x))[0x41] = (y); \
		(*(x))[0x42] = (y); \
		(*(x))[0x43] = (y); \
		(*(x))[0x44] = (y); \
		(*(x))[0x45] = (y); \
		(*(x))[0x46] = (y); \
		(*(x))[0x47] = (y); \
		(*(x))[0x48] = (y); \
		(*(x))[0x49] = (y); \
		(*(x))[0x4a] = (y); \
		(*(x))[0x4b] = (y); \
		(*(x))[0x4c] = (y); \
		(*(x))[0x4d] = (y); \
		(*(x))[0x4e] = (y); \
		(*(x))[0x4f] = (y); \
		(*(x))[0x50] = (y); \
		(*(x))[0x51] = (y); \
		(*(x))[0x52] = (y); \
		(*(x))[0x53] = (y); \
		(*(x))[0x54] = (y); \
		(*(x))[0x55] = (y); \
		(*(x))[0x56] = (y); \
		(*(x))[0x57] = (y); \
		(*(x))[0x58] = (y); \
		(*(x))[0x59] = (y); \
		(*(x))[0x5a] = (y); \
		(*(x))[0x5b] = (y); \
		(*(x))[0x5c] = (y); \
		(*(x))[0x5d] = (y); \
		(*(x))[0x5e] = (y); \
		(*(x))[0x5f] = (y); \
		(*(x))[0x60] = (y); \
		(*(x))[0x61] = (y); \
		(*(x))[0x62] = (y); \
		(*(x))[0x63] = (y); \
		(*(x))[0x64] = (y); \
		(*(x))[0x65] = (y); \
		(*(x))[0x66] = (y); \
		(*(x))[0x67] = (y); \
		(*(x))[0x68] = (y); \
		(*(x))[0x69] = (y); \
		(*(x))[0x6a] = (y); \
		(*(x))[0x6b] = (y); \
		(*(x))[0x6c] = (y); \
		(*(x))[0x6d] = (y); \
		(*(x))[0x6e] = (y); \
		(*(x))[0x6f] = (y); \
		(*(x))[0x70] = (y); \
		(*(x))[0x71] = (y); \
		(*(x))[0x72] = (y); \
		(*(x))[0x73] = (y); \
		(*(x))[0x74] = (y); \
		(*(x))[0x75] = (y); \
		(*(x))[0x76] = (y); \
		(*(x))[0x77] = (y); \
		(*(x))[0x78] = (y); \
		(*(x))[0x79] = (y); \
		(*(x))[0x7a] = (y); \
		(*(x))[0x7b] = (y); \
		(*(x))[0x7c] = (y); \
		(*(x))[0x7d] = (y); \
		(*(x))[0x7e] = (y); \
		(*(x))[0x7f] = (y); \
	} while (0 != 0)

#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

/*
 * min, max
 */

#ifndef F8E24S_MAX
#define F8E24S_MAX __FLT_MAX__
#endif
#ifndef F11E53S_MAX
#define F11E53S_MAX __DBL_MAX__
#endif
#ifndef F8E24S_MIN
#define F8E24S_MIN __FLT_MIN__
#endif
#ifndef F11E53S_MIN
#define F11E53S_MIN __DBL_MIN__
#endif
#ifndef F32_MAX
#define F32_MAX F8E24S_MAX
#endif
#ifndef F64_MAX
#define F64_MAX F11E53S_MAX
#endif
#ifndef F32_MIN
#define F32_MIN F8E24S_MIN
#endif
#ifndef F64_MIN
#define F64_MIN F11E53S_MIN
#endif
#ifndef U128_MAX
#define U128_MAX ((U128) ~(U128)0)
#endif
#ifndef S128_MAX
#define S128_MAX ((S128)(((U128)1 << 127) - 1))
#endif
#ifndef S128_MIN
#define S128_MIN ((S128)(-S128_MAX - 1))
#endif
#ifndef U64_MAX
#define U64_MAX ((U64) ~(U64)0)
#endif
#ifndef S64_MAX
#define S64_MAX ((S64)(((U64)1 << 63) - 1))
#endif
#ifndef S64_MIN
#define S64_MIN ((S64)(-S64_MAX - 1))
#endif
#ifndef U32_MAX
#define U32_MAX ((S64)(U32) ~(U32)0)
#endif
#ifndef S32_MAX
#define S32_MAX ((S32)(((U32)1 << 31) - 1))
#endif
#ifndef S32_MIN
#define S32_MIN ((S64)(-S32_MAX - 1))
#endif
#ifndef U16_MAX
#define U16_MAX ((S32)(U16) ~(U16)0)
#endif
#ifndef S16_MAX
#define S16_MAX ((S32)(((U16)1 << 15) - 1))
#endif
#ifndef S16_MIN
#define S16_MIN ((S32)(-S16_MAX - 1))
#endif
#ifndef U8_MAX
#define U8_MAX ((S32)(U8) ~(U8)0)
#endif
#ifndef S8_MAX
#define S8_MAX ((S32)(((U8)1 << 7) - 1))
#endif
#ifndef S8_MIN
#define S8_MIN ((S32)(-S8_MAX - 1))
#endif

/*
 * types used in functions
 */

#ifndef BOOL_IN
#define BOOL_IN U8
#endif
#ifndef U8_IN
#define U8_IN U8
#endif
#ifndef U16_IN
#define U16_IN U16
#endif
#ifndef U32_IN
#define U32_IN U32
#endif
#ifndef U64_IN
#define U64_IN U64
#endif
#ifndef U128_IN
#define U128_IN U128
#endif
#ifndef S8_IN
#define S8_IN S8
#endif
#ifndef S16_IN
#define S16_IN S16
#endif
#ifndef S32_IN
#define S32_IN S32
#endif
#ifndef S64_IN
#define S64_IN S64
#endif
#ifndef S128_IN
#define S128_IN S128
#endif
#ifndef BOOL_OUT
#define BOOL_OUT U64
#endif
#ifndef U8_OUT
#define U8_OUT U64
#endif
#ifndef U16_OUT
#define U16_OUT U64
#endif
#ifndef U32_OUT
#define U32_OUT U64
#endif
#ifndef U64_OUT
#define U64_OUT U64
#endif
#ifndef U128_OUT
#define U128_OUT U128
#endif
#ifndef S8_OUT
#define S8_OUT S64
#endif
#ifndef S16_OUT
#define S16_OUT S64
#endif
#ifndef S32_OUT
#define S32_OUT S64
#endif
#ifndef S64_OUT
#define S64_OUT S64
#endif
#ifndef S128_OUT
#define S128_OUT S128
#endif

#ifndef TRUE
/* must be non-zero */
#define TRUE 1
#endif

#ifndef FALSE
/* for symmetry, must be zero */
#define FALSE 0
#endif

/*
 * ptr
 */

#ifndef UPTR
#define UPTR U64
#endif
#ifndef SPTR
#define SPTR S64
#endif
#ifndef UFPTR
#define UFPTR U64
#endif
#ifndef SFPTR
#define SFPTR S64
#endif

#ifndef UPTR_IN
#define UPTR_IN U64_IN
#endif
#ifndef SPTR_IN
#define SPTR_IN S64_IN
#endif
#ifndef UFPTR_IN
#define UFPTR_IN U64_IN
#endif
#ifndef SFPTR_IN
#define SFPTR_IN S64_IN
#endif

#ifndef UPTR_OUT
#define UPTR_OUT U64_OUT
#endif
#ifndef SPTR_OUT
#define SPTR_OUT S64_OUT
#endif
#ifndef UFPTR_OUT
#define UFPTR_OUT U64_OUT
#endif
#ifndef SFPTR_OUT
#define SFPTR_OUT S64_OUT
#endif

/*
 * bits & arithmetic
 */

/* prefer compile-time errors */
#ifndef GET_ALIGNED_UP
#define GET_ALIGNED_UP(nbits, p, alignment) (__builtin_align_up(p, alignment))
#endif
#ifndef GET_ALIGNED_DOWN
#define GET_ALIGNED_DOWN(nbits, p, alignment) (__builtin_align_down(p, alignment))
#endif
#ifndef IS_ALIGNED
#define IS_ALIGNED(nbits, p, alignment) (__builtin_is_aligned(p, alignment) ? 1 : 0)
#endif

/*
 * performance
 */

#ifndef NON_TEMPORAL_LOAD
#define NON_TEMPORAL_LOAD(nbits, p) __builtin_nontemporal_load(p)
#endif

#ifndef NON_TEMPORAL_STORE
#define NON_TEMPORAL_STORE(nbits, p, v) __builtin_nontemporal_store(v, p)
#endif

#ifndef ATOMIC_CAS_LOOP_PAUSE
#define ATOMIC_CAS_LOOP_PAUSE() _mm_pause()
#endif

/*
 * misc
 */

/* requires constant */
#ifndef ALIGNED_ALLOCA
#define ALIGNED_ALLOCA(pptr, nbytes, alignment_nbytes)                                       \
	do {                                                                                 \
		*(pptr) = __builtin_alloca_with_align(nbytes, CHAR_BIT * (alignment_nbytes)) \
	} while (0 != 0)
#endif

#ifndef FAILCHECK
#define FAILCHECK(errptr, failfunc, target, report_dev_strliteral, report_user)                               \
	do {                                                                                                  \
		if (OFTEN(!*(errptr))) {                                                                      \
			*(errptr) = (target);                                                                 \
			if (RARELY(*(errptr))) {                                                              \
				if ((failfunc) != FNULL) {                                                    \
					(*(void (*)(void *, void *))(failfunc))(                              \
					    (void *)(report_user), (void *)(__FILE__ " " STRINGIZE_VALUE(     \
								       __LINE__) ":"                          \
										 " " report_dev_strliteral)); \
				}                                                                             \
			}                                                                                     \
		}                                                                                             \
	} while (0 != 0)
#endif
