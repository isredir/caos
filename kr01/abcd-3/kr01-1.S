	.data
A: .int 0
B: .int 0
R: .int 0
	.global A, B, R

	.text
	.global process
process:
	mov B, %eax
	sar $4, %eax
	neg %eax
	add A, %eax
	jo after
	add A, %eax
	jo after
	add A, %eax
	jo after
	mov %eax, R
after:
	xor %eax, %eax
	ret

#	.global main
#main:
#	call process
#	mov R, %eax
#	call writei32

#3 * a + b / 16
