	.text
	.align  4
	.globl  elf_start
	.hidden elf_start
	.type   elf_start,@function
elf_start:
	mov     %rsp, %rdi
	mov     %rdx, %rsi
	call    elf_entry
	hlt
