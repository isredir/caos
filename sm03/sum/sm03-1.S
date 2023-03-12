	.data
var: .int 0
	.section .rodata
scan_d: .asciz "%d"
print_d: .asciz "%d\n"
print_s: .asciz "%s\n"
print_overflow: .asciz "Overflow"
	.text
	.global main
main:
	push %ebp
	mov %esp, %ebp

	xor %ebx, %ebx
loop:
	push $var
	push $scan_d
	call scanf
	add $8, %esp
	cmp $0, %eax
	jle after
	add var, %ebx
	jo error
	jmp loop
error:
	push $print_overflow
	push $print_s
	call printf
	add $8, %esp
	xor %eax, %eax
	leave
	ret
after:
	push %ebx
	push $print_d
	call printf
	add $8, %esp
	xor %eax, %eax
	leave
	ret
