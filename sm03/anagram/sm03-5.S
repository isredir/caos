	.bss
arr: .skip 4 * 130
	.section .rodata
YES: .asciz "YES"
NO: .asciz "NO"
	.text
	.global main
main:
	push %ebp
	mov %esp, %ebp
	push %ebx
	push %ecx
	push %edx
	
loop1:
	call getchar
	cmp $'\n', %eax
	je loop2
	cmp $'A', %eax
	jl not_upper_case1
	cmp $'Z', %eax
	jg not_upper_case1
	add $32, %eax
not_upper_case1:
	mov $arr, %ebx
	incl (%ebx, %eax, 4)
	jmp loop1
loop2:
	call getchar
	cmp $'\n', %eax
	je after
	cmp $'A', %eax
	jl not_upper_case2
	cmp $'Z', %eax
	jg not_upper_case2
	add $32, %eax		#тут 32 как число а не символ
not_upper_case2:
	mov $arr, %ebx
	decl (%ebx, %eax, 4)
	jmp loop2
after:
	mov $' ', %ecx
	xor %edx, %edx
	mov %edx, (%ebx, %ecx, 4)
	xor %ecx, %ecx
loop3:
	mov $arr, %ebx
	mov (%ebx, %ecx, 4), %edx
	cmp $0, %edx
	jne no
	inc %ecx
	cmp $127, %ecx
	jl loop3
	je yes
no:
	push $NO
	call puts
	add $4, %esp
	jmp finale
yes:
	push $YES
	call puts
	add $4, %esp
finale:
	xor %eax, %eax
	pop %edx
	pop %ecx
	pop %ebx
	leave
	ret
