	.section .rodata
print_d: .asciz "%d"
	.text
	.global main
main:
	push %ebp
	mov %esp, %ebp
	push $to_print
	push %ebp
	mov %esp, %ebp
	jmp process
to_print:
	push %eax
	push $print_d
	call printf
	xor %eax, %eax
	leave
	ret
	
#process:
#	mov $4, %eax
#	leave
#	ret
