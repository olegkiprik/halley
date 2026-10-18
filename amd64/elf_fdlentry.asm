	.text
	.globl  elf_fdl_entry
	.type   elf_fdl_entry,@function
elf_fdl_entry:
	andq    $-16, %rsp        # align RSP to 16-byte boundary
	call    fdl_entry_impl    # tail-jump into C body
