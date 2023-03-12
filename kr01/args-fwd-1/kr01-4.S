	.global my.args.forward
my.args.forward:
	push %ebp
	mov %esp, %ebp
	
	pushl 16(%ebp)
	pushl 12(%ebp)
	pushl 8(%ebp)
	pushl 20(%ebp)
	call process
	neg %eax
	
	leave
	ret
