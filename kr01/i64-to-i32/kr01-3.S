	.section .rodata
max_32: .int 2147483647
min_32: .int -2147483648
	.text
	.global main
main:
	call readi64
#	call writei32
	
#	push %eax
#	mov %edx, %eax
#	call writei32
#	pop %eax
	
	cmp $-1, %edx
	je minus_one
	cmp $0, %edx
	jl less
	cmp $0, %edx
	jg greater
	cmp $0, %eax
	jl problem_pos
	call writei32
	jmp after
problem_pos:
	mov max_32, %eax
	call writei32
	jmp after
problem_neg:
	mov min_32, %eax
	call writei32
	jmp after
minus_one:
	cmp $0, %eax
	jg problem_neg
	call writei32
	jmp after
less:
	mov min_32, %eax
	call writei32
	jmp after
greater:
	mov max_32, %eax
	call writei32
	jmp after
after:	
	xor %eax, %eax
	call finish

