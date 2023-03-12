	.global main
main:
	movl $1, %ebx
loop1:
	call readi32
	jc loop2
	pushl %eax
	incl %ebx
	jmp loop1
loop2:
	decl %ebx
	jz finale
	popl %eax
	call writei32
	jmp loop2
finale:
	call finish
