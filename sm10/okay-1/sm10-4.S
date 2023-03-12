	.global okay
okay:
    push %ebp
    mov %esp, %ebp

    movsd 8(%ebp), %xmm1	# x
    movsd 16(%ebp), %xmm2	# y
    mov 24(%ebp), %eax		# *r

    mulsd %xmm1, %xmm1
    mulsd %xmm1, %xmm1
    
    mulsd %xmm2, %xmm2
    mulsd %xmm2, %xmm2

    addsd %xmm2, %xmm1

    sqrtsd %xmm1, %xmm1

    movsd %xmm1, (%eax)

	mov %ebp, %esp
    pop %ebp
    ret
