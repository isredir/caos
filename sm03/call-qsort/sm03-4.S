	.section .rodata
int16_t_min: .word -32768
	.text
	.global sort_by_abs
sort_by_abs:
	push %ebp
	mov %esp, %ebp
	push %ebx
	push %ecx
	push %edx
	
	mov 8(%ebp), %eax
	mov 12(%ebp), %ebx
	sub $16, %esp
	mov %eax, (%esp)
	mov %ebx, 4(%esp)
	movl $2, 8(%esp)
	mov $cmp, %ebx
	mov %ebx, 12(%esp)
	call qsort
	add $16, %esp
	
	pop %edx
	pop %ecx
	pop %ebx
	leave
	ret
cmp:
	push %ebp
	mov %esp, %ebp
	push %ebx
	push %ecx
	push %edx
	
	xor %eax, %eax
	xor %ebx, %ebx
	mov 8(%ebp), %ecx
	mov 12(%ebp), %edx
	movw (%ecx), %ax
	movw (%edx), %bx
	mov %eax, %ecx
	mov %ebx, %edx
	cmpw int16_t_min, %cx
	je first_min
	cmpw int16_t_min, %dx
	je second_min
	cmpw $0, %cx
	jge first_pos
	negw %cx
first_pos:
	cmpw $0, %dx
	jge both_pos
	negw %dx
both_pos:
	cmpw %cx, %dx
	jg less
	cmpw %cx, %dx
	jl greater
	mov $0, %eax
	jmp after
greater:
	mov $1, %eax
	jmp after
less:
	mov $-1, %eax
	jmp after
first_min:
	mov $1, %eax
	cmpw int16_t_min, %dx
	jne after
	mov $0, %eax
	jmp after
second_min:
	mov $-1, %eax
after:
	pop %edx
	pop %ecx
	pop %ebx
	leave
	ret
