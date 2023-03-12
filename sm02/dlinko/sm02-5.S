	.data
carry: .int 0
res: .int 0

	.text
	.global supersum
supersum:

	push %ebp
	push %edx
	
	mov %esi, %edx
	add %edi, %edx
	cmp $0, %edx
	je finale

	xor %ebp, %ebp
	cmp %esi, %edi
	jle loop
	xchg %esi, %edi
	xchg %eax, %ebx
loop:

	xor %edx, %edx
	movb (%eax, %ebp, 1), %dl
	mov %edx, res
	mov carry, %edx
	add %edx, res
	cmp %ebp, %edi
	
	jle end_of_b
	movb (%ebx, %ebp, 1), %dl
	jmp continue

end_of_b:
	mov $0, %edx

continue:
	add %edx, res
	mov res, %edx
	
	shr $8, %edx
	mov %edx, carry
	
	mov res, %edx
	movb %dl, (%ecx, %ebp, 1)
	inc %ebp
	cmp %ebp, %esi
	jg loop
	mov carry, %edx
	cmp $0, %edx
	je after
	movb %dl, (%ecx, %ebp, 1)
	inc %ebp
after:
	dec %ebp
	movb (%ecx, %ebp, 1), %dl
	cmp $0, %dl
	je after
	inc %ebp
	
	cmp $0, %ebp
	jl zero
	mov %ebp, %eax
	jmp finale

zero:
	movl $1, %eax
	movb $0, (%ecx)

finale:
	pop %edx
	pop %ebp
	ret
