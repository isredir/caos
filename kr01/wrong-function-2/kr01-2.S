	.text
#	.global main
#main:
#	jmp call_process
	.global call_process
call_process:
	mov $process, %ecx
	add $3, %ecx
	jmp *%ecx
	

#	call writei32
#	leave
	ret
	
#process:
#	push %ebp
#	mov %esp, %ebp
#	push %ebp
#	mov %esp, %ebp
#	mov $4, %eax
#	leave
#	ret
