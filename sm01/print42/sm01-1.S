	.global main
main:
	movl $42, %eax
	call writei32
	call finish
