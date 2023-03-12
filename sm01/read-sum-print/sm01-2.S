	.global main
main:
	call readi32
	movl %eax, %ebx
	call readi32
	addl %eax, %eax
	subl %eax, %ebx
	call readi32
	movl %eax, %ecx
	sal $4, %ecx
	addl %eax, %ecx
	addl %ecx, %ebx
	call readi32
	call writei32
	movl %ebx, %eax
	call writei32
	call finish
