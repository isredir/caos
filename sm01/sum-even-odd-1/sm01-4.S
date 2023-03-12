	.global main
main:
	movl $0, %ebx
	movl $0, %ecx
loop:
	call readi32
	jc finale
	test $1, %eax
	jz even
	addl %eax, %ecx //odd
	jmp loop
even:
	addl %eax, %ebx
	jmp loop
finale:
	movl %ebx, %eax
	call writei32
	movl %ecx, %eax
	call writei32
	call finish
