	.text
	.align  4
	.globl  elf_trampo
	.type   elf_trampo,@function
elf_trampo:
	mov     %rsi, %rsp
	jmp     *%rdi
	hlt     # Should not reach
