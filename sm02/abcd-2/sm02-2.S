	.data
A: .int 0
B: .int 0
R: .int 0
	.global A, B, R

	.text
	.global process
process:
	mov A, %eax
	mov B, %ecx
	mov $0, %edx
loop:
	test $1, %ecx
	jz even
	add %eax, %edx
even:
	shl %eax
	shr %ecx
after:
	cmp $0, %ecx
	jnz loop
	mov %edx, R
	ret
