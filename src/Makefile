# release
# -s

# x86-64, AArch64, ..?
#
# No AVX? Add -DNO_SIMD_256 and replace -DSIMD_VEX with -USIMD_VEX

CPU_ARCH = x86-64
CC = clang
COMMON_FLAGS = -fstrict-aliasing -fno-builtin
C_FLAGS = $(COMMON_FLAGS) -pipe -std=c17 -UNDEBUG -mcx16 -march=$(CPU_ARCH) -USIMD_VEX -DNO_SIMD_1024 -DNO_SIMD_512 -DNO_SIMD_256 -UNO_SIMD_128 -UNO_SIMD_64 -Wall -Wextra -Wshadow -Wno-pedantic -Wstrict-aliasing -Wno-logical-op-parentheses -Wno-bitwise-op-parentheses -Wno-shift-op-parentheses -Wno-unused-function -Wno-ignored-attributes -Wno-logical-op-parentheses -Wno-bitwise-op-parentheses -Wno-shift-op-parentheses -Werror=vla -Werror=trigraphs -Werror=unknown-escape-sequence -U_FORTIFY_SOURCE -fvisibility=hidden -Wa,--noexecstack -fno-stack-protector -fno-ident -fno-asynchronous-unwind-tables -fno-unwind-tables -O3 -ffast-math -fno-PIC -fno-pie
ASM_FLAGS = -pipe -Wall -Wextra -Wshadow -Wno-pedantic -fno-PIC -fno-pie -Wa,--noexecstack

amd64/elf_start.o: amd64/elf_start.asm
	$(CC) $(ASM_FLAGS) -c -o $@ $<
amd64/elf_fdlentry.o: amd64/elf_fdlentry.asm
	$(CC) $(ASM_FLAGS) -c -o $@ $<
amd64/elf_trampo.o: amd64/elf_trampo.asm
	$(CC) $(ASM_FLAGS) -c -o $@ $<
launcher.o: launcher.c
	$(CC) $(C_FLAGS) -c -o $@ $<
main.o: main.c
	$(CC) $(C_FLAGS) -URGFW_DEBUG -URGFW_PRINT_ERRORS -UMA_DEBUG_OUTPUT -UMA_NO_SSE -UMA_NO_SSE2 -DMA_NO_AVX -DMA_NO_AVX2 -DMA_NO_NEON -DPRIV_ATOMIC_REQUIRED_SIZE_PREVENT_ERROR=16 -c -o $@ $<
rt_audio_callback_1_1_10.o: rt_audio_callback_1_1_10.c
	$(CC) $(C_FLAGS) -c -o $@ $<
rt_audio_callback_1_2_10.o: rt_audio_callback_1_2_10.c
	$(CC) $(C_FLAGS) -c -o $@ $<
rt_audio_callback_2_2_10.o: rt_audio_callback_2_2_10.c
	$(CC) $(C_FLAGS) -c -o $@ $<
rt_audio_callback_1_1_11.o: rt_audio_callback_1_1_11.c
	$(CC) $(C_FLAGS) -c -o $@ $<
rt_audio_callback_1_2_11.o: rt_audio_callback_1_2_11.c
	$(CC) $(C_FLAGS) -c -o $@ $<
rt_audio_callback_2_2_11.o: rt_audio_callback_2_2_11.c
	$(CC) $(C_FLAGS) -c -o $@ $<
rt_audio_callback_1_1_12.o: rt_audio_callback_1_1_12.c
	$(CC) $(C_FLAGS) -c -o $@ $<
rt_audio_callback_1_2_12.o: rt_audio_callback_1_2_12.c
	$(CC) $(C_FLAGS) -c -o $@ $<
rt_audio_callback_2_2_12.o: rt_audio_callback_2_2_12.c
	$(CC) $(C_FLAGS) -c -o $@ $<
rt_audio_callback_1_1_13.o: rt_audio_callback_1_1_13.c
	$(CC) $(C_FLAGS) -c -o $@ $<
rt_audio_callback_1_2_13.o: rt_audio_callback_1_2_13.c
	$(CC) $(C_FLAGS) -c -o $@ $<
rt_audio_callback_2_2_13.o: rt_audio_callback_2_2_13.c
	$(CC) $(C_FLAGS) -c -o $@ $<
halley: amd64/elf_start.o amd64/elf_fdlentry.o amd64/elf_trampo.o launcher.o main.o rt_audio_callback_1_1_10.o rt_audio_callback_1_2_10.o rt_audio_callback_2_2_10.o rt_audio_callback_1_1_11.o rt_audio_callback_1_2_11.o rt_audio_callback_2_2_11.o rt_audio_callback_1_1_12.o rt_audio_callback_1_2_12.o rt_audio_callback_2_2_12.o rt_audio_callback_1_1_13.o rt_audio_callback_1_2_13.o rt_audio_callback_2_2_13.o
	$(CC) -march=$(CPU_ARCH) $(COMMON_FLAGS) -nostartfiles -nodefaultlibs -nostdlib -e elf_start -Wl,-Bsymbolic,--no-undefined,--build-id=none -static -Wl,-Ttext-segment=0x66000000 -o $@ $^
