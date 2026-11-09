
#ifndef S8
#define S8 signed char
#endif
#ifndef S16
#define S16 short
#endif
#ifndef S32
#define S32 int
#endif
#ifndef S64
#define S64 long long
#endif
#ifndef S128
#define S128 __int128
#endif
#ifndef U8
#define U8 unsigned char
#endif
#ifndef U16
#define U16 unsigned short
#endif
#ifndef U32
#define U32 unsigned int
#endif
#ifndef U64
#define U64 unsigned long long
#endif
#ifndef U128
#define U128 unsigned __int128
#endif
#ifndef F5E11S
#define F5E11S _Float16
#endif
#ifndef F8E8S
#define F8E8S __bf16
#endif
#ifndef F8E24S
#define F8E24S float
#endif
#ifndef F11E53S
#define F11E53S double
#endif

#ifndef F32
#define F32 F8E24S
#endif
#ifndef F64
#define F64 F11E53S
#endif

#ifndef S8_RAW
#define S8_RAW priv_signed_char_may_alias_t
#endif
#ifndef S16_RAW
#define S16_RAW priv_short_may_alias_t
#endif
#ifndef S32_RAW
#define S32_RAW priv_int_may_alias_t
#endif
#ifndef S64_RAW
#define S64_RAW priv_long_long_may_alias_t
#endif
#ifndef S128_RAW
#define S128_RAW priv___int128_may_alias_t
#endif
#ifndef U8_RAW
#define U8_RAW priv_unsigned_char_may_alias_t
#endif
#ifndef U16_RAW
#define U16_RAW priv_unsigned_short_may_alias_t
#endif
#ifndef U32_RAW
#define U32_RAW priv_unsigned_int_may_alias_t
#endif
#ifndef U64_RAW
#define U64_RAW priv_unsigned_long_long_may_alias_t
#endif
#ifndef U128_RAW
#define U128_RAW priv_unsigned___int128_may_alias_t
#endif
#ifndef F5E11S_RAW
#define F5E11S_RAW priv__Float16_may_alias_t
#endif
#ifndef F8E8S_RAW
#define F8E8S_RAW priv___bf16_may_alias_t
#endif
#ifndef F8E24S_RAW
#define F8E24S_RAW priv_float_may_alias_t
#endif
#ifndef F11E53S_RAW
#define F11E53S_RAW priv_double_may_alias_t
#endif

#ifndef F32_RAW
#define F32_RAW F8E24S_RAW
#endif
#ifndef F64_RAW
#define F64_RAW F11E53S_RAW
#endif
