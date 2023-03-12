	.global partition
partition:
	push %esi
#	addl %esi, %esi
#	addl %ebx, %esi
	
	
#	mov %ebx, %ecx
#	mov %ebx, %eax

	xor %eax, %eax
	xor %ecx, %ecx
	
loop:
	
	
#	call writei32
#	push %eax
#	mov %ecx, %eax
#	call writei32
#	pop %eax
	
#	cmpw (%eax), %di
	
	cmpw (%ebx, %eax, 2), %di

	jge greater
	jmp after
greater:
#	pushw (%ecx)
#	pushw (%eax)
#	popw (%ecx)
#	popw (%eax)
	
	pushw (%ebx, %eax, 2)
	pushw (%ebx, %ecx, 2)
	popw (%ebx, %eax, 2)
	popw (%ebx, %ecx, 2)
	
#	add $2, %ecx
	inc %ecx
after:
#	add $2, %eax
	inc %eax
	cmp %eax, %esi	
	jg loop
	mov %ecx, %edx
	pop %esi
	ret
