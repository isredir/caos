	.global main
main:
	call readi32
	movl $0, %ebx
loop:
	test $1, %eax
	jz zero
	inc %ebx
zero:
	shr $1, %eax
	jnz loop
finale:
	movl %ebx, %eax
	call writei32
	call finish
