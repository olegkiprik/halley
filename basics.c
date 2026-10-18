
#ifndef SENTRY_BASICS_MACROS
#define SENTRY_BASICS_MACROS
#include "basics_macros.c"
#endif

/*
 * bits & arithmetic
 */

static ALWAYS_INLINE U8 bitreverse_8(U8 x)
{
	assert(x == (U8)x);
	return __builtin_bitreverse8(x);
}

static ALWAYS_INLINE U16 bitreverse_16(U16 x)
{
	assert(x == (U16)x);
	return __builtin_bitreverse16(x);
}

static ALWAYS_INLINE U32 bitreverse_32(U32 x)
{
	assert(x == (U32)x);
	return __builtin_bitreverse32(x);
}

static ALWAYS_INLINE U64 bitreverse_64(U64 x)
{
	assert(x == (U64)x);
	return __builtin_bitreverse64(x);
}

static ALWAYS_INLINE U128 bitreverse_128(U128 x)
{
	assert(x == (U128)x);
	U64 m = bitreverse_64(x & U64_MAX);
	U64 l = bitreverse_64(x >> 64);
	U128 result;
	result = 0;
	result |= m;
	result <<= 64;
	result |= l;
	return result;
}

static ALWAYS_INLINE U128 rotate_left_128(U128 x, U8 y)
{
	assert(x == (U128)x);
	assert(y == (U8)y);
	return x << y | x >> (128 - y);
}
static ALWAYS_INLINE U128 rotate_right_128(U128 x, U8 y)
{
	assert(x == (U128)x);
	assert(y == (U8)y);
	return x >> y | x << (128 - y);
}

static ALWAYS_INLINE U8 rotate_left_8(U8 x, U8 y)
{
	assert(x == (U8)x);
	assert(y == (U8)y);
	return __builtin_rotateleft8(x, y);
}

static ALWAYS_INLINE U8 rotate_right_8(U8 x, U8 y)
{
	assert(x == (U8)x);
	assert(y == (U8)y);
	return __builtin_rotateright8(x, y);
}

static ALWAYS_INLINE U16 rotate_left_16(U16 x, U8 y)
{
	assert(x == (U16)x);
	assert(y == (U8)y);
	return __builtin_rotateleft16(x, y);
}

static ALWAYS_INLINE U16 rotate_right_16(U16 x, U8 y)
{
	assert(x == (U16)x);
	assert(y == (U8)y);
	return __builtin_rotateright16(x, y);
}

static ALWAYS_INLINE U32 rotate_left_32(U32 x, U8 y)
{
	assert(x == (U32)x);
	assert(y == (U8)y);
	return __builtin_rotateleft32(x, y);
}

static ALWAYS_INLINE U32 rotate_right_32(U32 x, U8 y)
{
	assert(x == (U32)x);
	assert(y == (U8)y);
	return __builtin_rotateright32(x, y);
}

static ALWAYS_INLINE U64 rotate_left_64(U64 x, U8 y)
{
	assert(x == (U64)x);
	assert(y == (U8)y);
	return __builtin_rotateleft64(x, y);
}

static ALWAYS_INLINE U64 rotate_right_64(U64 x, U8 y)
{
	assert(x == (U64)x);
	assert(y == (U8)y);
	return __builtin_rotateright64(x, y);
}

static ALWAYS_INLINE void multiprecise_add_u32(U32 *restrict result, U32 *restrict carry_out, U32 x, U32 y,
					       U32 carry_in)
{
	U32 res;
	U32 c;

	assert(x == (U32)x);
	assert(y == (U32)y);
	assert(carry_in == (U32)carry_in);

	res = __builtin_addc(x, y, carry_in, &c);
	*result = res;
	*carry_out = c;
}

static ALWAYS_INLINE void multiprecise_sub_u32(U32 *restrict result, U32 *restrict carry_out, U32 x, U32 y,
					       U32 carry_in)
{
	U32 res;
	U32 c;

	assert(x == (U32)x);
	assert(y == (U32)y);
	assert(carry_in == (U32)carry_in);

	res = __builtin_subc(x, y, carry_in, &c);
	*result = res;
	*carry_out = c;
}

static ALWAYS_INLINE void multiprecise_add_u64(U64 *restrict result, U64 *restrict carry_out, U64 x, U64 y,
					       U64 carry_in)
{
	U64 res;
	U64 c;

	assert(x == (U64)x);
	assert(y == (U64)y);
	assert(carry_in == (U64)carry_in);

	res = __builtin_addcll(x, y, carry_in, &c);
	*result = res;
	*carry_out = c;
}

static ALWAYS_INLINE void multiprecise_sub_u64(U64 *restrict result, U64 *restrict carry_out, U64 x, U64 y,
					       U64 carry_in)
{
	U64 res;
	U64 c;

	assert(x == (U64)x);
	assert(y == (U64)y);
	assert(carry_in == (U64)carry_in);

	res = __builtin_subcll(x, y, carry_in, &c);
	*result = res;
	*carry_out = c;
}

static ALWAYS_INLINE BOOL_OUT wrap_add_u32(U32 *result, U32 x, U32 y)
{
	assert(x == (U32)x);
	assert(y == (U32)y);
	return __builtin_uadd_overflow(x, y, result) ? 1 : 0;
}

static ALWAYS_INLINE BOOL_OUT wrap_sub_u32(U32 *result, U32 x, U32 y)
{
	assert(x == (U32)x);
	assert(y == (U32)y);
	return __builtin_usub_overflow(x, y, result) ? 1 : 0;
}

static ALWAYS_INLINE BOOL_OUT wrap_mul_u32(U32 *result, U32 x, U32 y)
{
	assert(x == (U32)x);
	assert(y == (U32)y);
	return __builtin_umul_overflow(x, y, result) ? 1 : 0;
}

static ALWAYS_INLINE BOOL_OUT wrap_add_u64(U64 *result, U64 x, U64 y)
{
	assert(x == (U64)x);
	assert(y == (U64)y);
	return __builtin_uaddll_overflow(x, y, result) ? 1 : 0;
}

static ALWAYS_INLINE BOOL_OUT wrap_sub_u64(U64 *result, U64 x, U64 y)
{
	assert(x == (U64)x);
	assert(y == (U64)y);
	return __builtin_usubll_overflow(x, y, result) ? 1 : 0;
}

static ALWAYS_INLINE BOOL_OUT wrap_mul_u64(U64 *result, U64 x, U64 y)
{
	assert(x == (U64)x);
	assert(y == (U64)y);
	return __builtin_umulll_overflow(x, y, result) ? 1 : 0;
}

static ALWAYS_INLINE BOOL_OUT wrap_add_s32(S32 *result, S32 x, S32 y)
{
	assert(x == (S32)x);
	assert(y == (S32)y);
	return __builtin_sadd_overflow(x, y, result) ? 1 : 0;
}

static ALWAYS_INLINE BOOL_OUT wrap_sub_s32(S32 *result, S32 x, S32 y)
{
	assert(x == (S32)x);
	assert(y == (S32)y);
	return __builtin_ssub_overflow(x, y, result) ? 1 : 0;
}

static ALWAYS_INLINE BOOL_OUT wrap_mul_s32(S32 *result, S32 x, S32 y)
{
	assert(x == (S32)x);
	assert(y == (S32)y);
	return __builtin_smul_overflow(x, y, result) ? 1 : 0;
}

static ALWAYS_INLINE BOOL_OUT wrap_add_s64(S64 *result, S64 x, S64 y)
{
	assert(x == (S64)x);
	assert(y == (S64)y);
	return __builtin_saddll_overflow(x, y, result) ? 1 : 0;
}

static ALWAYS_INLINE BOOL_OUT wrap_sub_s64(S64 *result, S64 x, S64 y)
{
	assert(x == (S64)x);
	assert(y == (S64)y);
	return __builtin_ssubll_overflow(x, y, result) ? 1 : 0;
}

static ALWAYS_INLINE BOOL_OUT wrap_mul_s64(S64 *result, S64 x, S64 y)
{
	assert(x == (S64)x);
	assert(y == (S64)y);
	return __builtin_smulll_overflow(x, y, result) ? 1 : 0;
}

/* slow if x can be 0 */
static ALWAYS_INLINE S32 nr_leading_zeros_8(U8 x)
{
	assert(x == (U8)x);
	return __builtin_clzg(x, 8);
}
static ALWAYS_INLINE S32 nr_leading_zeros_16(U16 x)
{
	assert(x == (U16)x);
	return __builtin_clzg(x, 16);
}
static ALWAYS_INLINE S32 nr_leading_zeros_32(U32 x)
{
	assert(x == (U32)x);
	return __builtin_clzg(x, 32);
}
static ALWAYS_INLINE S32 nr_leading_zeros_64(U64 x)
{
	assert(x == (U64)x);
	return __builtin_clzg(x, 64);
}
static ALWAYS_INLINE S32 nr_leading_zeros_128(U128 x)
{
	assert(x == (U128)x);
	return __builtin_clzg(x, 128);
}
static ALWAYS_INLINE S32 nr_trailing_zeros_8(U8 x)
{
	assert(x == (U8)x);
	return __builtin_ctzg(x, 8);
}
static ALWAYS_INLINE S32 nr_trailing_zeros_16(U16 x)
{
	assert(x == (U16)x);
	return __builtin_ctzg(x, 16);
}
static ALWAYS_INLINE S32 nr_trailing_zeros_32(U32 x)
{
	assert(x == (U32)x);
	return __builtin_ctzg(x, 32);
}
static ALWAYS_INLINE S32 nr_trailing_zeros_64(U64 x)
{
	assert(x == (U64)x);
	return __builtin_ctzg(x, 64);
}
static ALWAYS_INLINE S32 nr_trailing_zeros_128(U128 x)
{
	assert(x == (U128)x);
	return __builtin_ctzg(x, 128);
}
static ALWAYS_INLINE S32 nr_one_bits_u8(U8 x)
{
	assert(x == (U8)x);
	return __builtin_popcount(x);
}
static ALWAYS_INLINE S32 nr_one_bits_u16(U16 x)
{
	assert(x == (U16)x);
	return __builtin_popcount(x);
}
static ALWAYS_INLINE S32 nr_one_bits_u32(U32 x)
{
	assert(x == (U32)x);
	return __builtin_popcount(x);
}
static ALWAYS_INLINE S32 nr_one_bits_u64(U64 x)
{
	assert(x == (U64)x);
	return __builtin_popcountll(x);
}
static ALWAYS_INLINE S32 nr_one_bits_u128(U128 x)
{
	assert(x == (U128)x);
	return __builtin_popcountg(x);
}
static ALWAYS_INLINE BOOL_OUT has_at_most_one_1_bit_u8(U8 x)
{
	assert(x == (U8)x);
	return x == 0 ? 1 : !(x & (x - 1));
}
static ALWAYS_INLINE BOOL_OUT has_at_most_one_1_bit_u16(U16 x)
{
	assert(x == (U16)x);
	return x == 0 ? 1 : !(x & (x - 1));
}
static ALWAYS_INLINE BOOL_OUT has_at_most_one_1_bit_u32(U32 x)
{
	assert(x == (U32)x);
	return x == 0 ? 1 : !(x & (x - 1));
}
static ALWAYS_INLINE BOOL_OUT has_at_most_one_1_bit_u64(U64 x)
{
	assert(x == (U64)x);
	return x == 0 ? 1 : !(x & (x - 1));
}
static ALWAYS_INLINE BOOL_OUT has_at_most_one_1_bit_u128(U128 x)
{
	assert(x == (U128)x);
	return x == 0 ? 1 : !(x & (x - 1));
}

/*
 * performance & synchronization
 */

static ALWAYS_INLINE void prefetch_write_persistence_0_out_of_3(const void *p)
{
	__builtin_prefetch(p, 1, 0);
}
static ALWAYS_INLINE void prefetch_write_persistence_1_out_of_3(const void *p)
{
	__builtin_prefetch(p, 1, 1);
}
static ALWAYS_INLINE void prefetch_write_persistence_2_out_of_3(const void *p)
{
	__builtin_prefetch(p, 1, 2);
}
static ALWAYS_INLINE void prefetch_write_persistence_3_out_of_3(const void *p)
{
	__builtin_prefetch(p, 1, 3);
}

static ALWAYS_INLINE void prefetch_read_persistence_0_out_of_3(const void *p)
{
	__builtin_prefetch(p, 0, 0);
}
static ALWAYS_INLINE void prefetch_read_persistence_1_out_of_3(const void *p)
{
	__builtin_prefetch(p, 0, 1);
}
static ALWAYS_INLINE void prefetch_read_persistence_2_out_of_3(const void *p)
{
	__builtin_prefetch(p, 0, 2);
}
static ALWAYS_INLINE void prefetch_read_persistence_3_out_of_3(const void *p)
{
	__builtin_prefetch(p, 0, 3);
}

static ALWAYS_INLINE void disable_denormals(void)
{
	U32 tmp;
	asm volatile("stmxcsr %0" : "=m"(tmp)::"cc", "memory");
	tmp |= 0x8040;
	asm volatile("ldmxcsr %0" ::"m"(tmp) : "cc", "memory");
}

static ALWAYS_INLINE void full_memory_fence(void)
{
	asm volatile("mfence" ::: "memory");
}

static ALWAYS_INLINE void compiler_memory_fence(void)
{
	asm volatile("" ::: "memory");
}

/*
 * misc
 */

static ALWAYS_INLINE U32 rand_u32(U64 *seed)
{
	/* musl */
	*seed = (U64)*seed * 6364136223846793005uLL + 1;
	return (U32)(*seed & U64_MAX);
}

static ALWAYS_INLINE void read_time_stamp_counter(U64 *restrict result, U32 *restrict processor_id,
						  BOOL_IN prior_to_subsequent_instructions,
						  BOOL_IN after_previous_stores_globally_visible)
{
	assert(prior_to_subsequent_instructions == !!prior_to_subsequent_instructions);
	assert(after_previous_stores_globally_visible == !!after_previous_stores_globally_visible);

	U64 rax;
	U64 rdx;
	U64 rcx;

	/* volatile is required */

	if (processor_id != NULL) {
		if (prior_to_subsequent_instructions & after_previous_stores_globally_visible) {
			asm volatile("mfence\nrdtscp\nlfence" : "=a"(rax), "=d"(rdx), "=c"(rcx)::"memory");
		} else if (prior_to_subsequent_instructions) {
			asm volatile("rdtscp\nlfence" : "=a"(rax), "=d"(rdx), "=c"(rcx)::"memory");
		} else if (after_previous_stores_globally_visible) {
			asm volatile("mfence\nrdtscp" : "=a"(rax), "=d"(rdx), "=c"(rcx)::"memory");
		} else {
			asm volatile("rdtscp" : "=a"(rax), "=d"(rdx), "=c"(rcx)::);
		}

		*processor_id = rcx;
	} else {
		if (prior_to_subsequent_instructions & after_previous_stores_globally_visible) {
			asm volatile("mfence\nrdtsc\nlfence" : "=a"(rax), "=d"(rdx)::"memory");
		} else if (prior_to_subsequent_instructions) {
			asm volatile("rdtsc\nlfence" : "=a"(rax), "=d"(rdx)::"memory");
		} else if (after_previous_stores_globally_visible) {
			asm volatile("mfence\nrdtsc" : "=a"(rax), "=d"(rdx)::"memory");
		} else {
			asm volatile("rdtsc" : "=a"(rax), "=d"(rdx)::);
		}
	}

	if (result != NULL) {
		*result = rdx << 32 | rax;
	}
}

static ALWAYS_INLINE void *get_raw_data_pointer(UPTR ptr_int)
{
	void *res;
	asm volatile("movq %1,%0" : "=r"(res) : "r"(ptr_int) : "memory");
	return res;
}

static ALWAYS_INLINE UPTR tag_data_pointer_u8(void *ptr, U8 data)
{
	return (UPTR)ptr | (UPTR)data << (sizeof(ptr) * CHAR_BIT - 8);
}

static ALWAYS_INLINE void *untag_data_pointer_u8(UPTR ptr)
{
	void *res;
	ptr &= ~((UPTR)0xffu << (sizeof(ptr) * CHAR_BIT - 8));
	asm volatile("movq %1,%0" : "=r"(res) : "r"(ptr) : "memory");
	return res;
}
