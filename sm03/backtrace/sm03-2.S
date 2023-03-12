	.section .rodata
Foo: .asciz "foo"
Bar: .asciz "bar"
Main: .asciz "main"
Print_tb: .asciz "print_tb"
	.text
	.global print_tb
print_tb:
	push %ebp
	mov %esp, %ebp
	push %edx
	push %edi
		
	push $Print_tb
	call puts
	add $4, %esp
loop:
	xor %edi, %edi
	mov 4(%ebp), %edx
	cmp $foo, %edx
	jl after_foo
	cmp $foo, %edi
	jg after_foo
	mov $foo, %edi
after_foo:
	cmp $bar, %edx
	jl after_foo_bar
	cmp $bar, %edi
	jg after_foo_bar
	mov $bar, %edi
after_foo_bar:
	cmp $main, %edx
	jl after_foo_bar_main
	cmp $main, %edi
	jg after_foo_bar_main
	mov $main, %edi
after_foo_bar_main:
	cmp $foo, %edi
	jne before_foo
	push $Foo
	call puts
	add $4, %esp
before_foo:
	cmp $bar, %edi
	jne before_foo_bar
	push $Bar
	call puts
	add $4, %esp
before_foo_bar:
	cmp $main, %edi
	jne before_foo_bar_main
	push $Main
	call puts
	add $4, %esp
before_foo_bar_main:
	cmp $main, %edi
	je finale
	mov (%ebp), %ebp
	jmp loop
finale:
	xor %eax, %eax
	pop %edi
	pop %edx
	leave
	ret
