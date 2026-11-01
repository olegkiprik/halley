
#ifndef SENTRY_NAIVE
#define SENTRY_NAIVE
#include "naive.c"
#endif

#define GENERATE_network_le_read(nbits, nvec)                                                         \
	static ALWAYS_INLINE U##nbits##_##nvec network_le_read_u##nbits##x##nvec(const void *p)       \
	{                                                                                             \
		U##nbits##_##nvec res;                                                                \
		for (U32 i = 0; i < nvec; ++i) {                                                      \
			U##nbits tmp;                                                                 \
			naive_memcpy(&tmp, (const char *)p + nbits / CHAR_BIT * i, nbits / CHAR_BIT); \
			SIMD_REFER_##nvec(res)[i] = LE_NTOH##nbits(tmp);                              \
		}                                                                                     \
		return res;                                                                           \
	}

#define GENERATE_network_le_write(nbits, nvec)                                                     \
	static ALWAYS_INLINE void network_le_write_u##nbits##x##nvec(void *p, U##nbits##_##nvec v) \
	{                                                                                          \
		for (U32 i = 0; i < nvec; ++i) {                                                   \
			U##nbits tmp;                                                              \
			tmp = LE_HTON##nbits(SIMD_REFER_##nvec(v)[i]);                             \
			naive_memcpy((char *)p + nbits / CHAR_BIT * i, &tmp, nbits / CHAR_BIT);    \
		}                                                                                  \
	}

GENERATE_network_le_read(8, 1);
GENERATE_network_le_read(16, 1);
GENERATE_network_le_read(32, 1);
GENERATE_network_le_read(64, 1);

GENERATE_network_le_read(32, 4);

#define network_le_read_u8(p) network_le_read_u8x1(p)
#define network_le_read_u16(p) network_le_read_u16x1(p)
#define network_le_read_u32(p) network_le_read_u32x1(p)
#define network_le_read_u64(p) network_le_read_u64x1(p)

GENERATE_network_le_write(8, 1);
GENERATE_network_le_write(16, 1);
GENERATE_network_le_write(32, 1);
GENERATE_network_le_write(64, 1);

GENERATE_network_le_write(32, 4);

#define network_le_write_u8(p, v) network_le_write_u8x1(p, v)
#define network_le_write_u16(p, v) network_le_write_u16x1(p, v)
#define network_le_write_u32(p, v) network_le_write_u32x1(p, v)
#define network_le_write_u64(p, v) network_le_write_u64x1(p, v)
