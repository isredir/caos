    .global  product
product:
    push %ebp
    mov %esp, %ebp
    push %edi
    push %esi
    push %ebx
    push %edx
    
    mov 8(%ebp), %ecx				# size of vectors
    mov 12(%ebp), %esi				# pointer to the start of x
    mov 16(%ebp), %edi				# pointer to the start of y
    mov	20(%ebp), %eax				# pointer to the result
    
    pxor %xmm2, %xmm2				# result will be in xmm2
    xor %ebx, %ebx				# position will be in ebx
while:
	mov %ecx, %edx				# check if there are less than 4 numbers left
	sub %ebx, %edx
    cmp $4, %edx
    jl less_than_4
    
    movups (%esi, %ebx, 4), %xmm0		# xmm0 = (a0, a1, a2, a3) = x[i: i+4]
    movups (%edi, %ebx, 4), %xmm1		# xmm1 = (b0, b1, b2, b3) = y[i: i+4]
    
    mulps %xmm0, %xmm1				# xmm1 = (a0b0, a1b1, a2b2, a3b3)
    
    addps %xmm1, %xmm2				# xmm2 += (a0b0, a1b1, a2b2, a3b3)
    
    add $4, %ebx
    
    jmp while
    
less_than_4:						

    hsubps %xmm2, %xmm2				# xmm2 = (a0b0-a1b1, a2b2-a3b3, *, *)
    
    haddps %xmm2, %xmm2				# xmm2 = (a0b0-a1b1+a2b2-a3b3, *, *, *)	

new_while:
    cmp %ebx, %ecx				# check if there are no numbers left
    je end
    
    movss (%esi, %ebx, 4), %xmm0		# xmm0 = x[i]
    movss (%edi, %ebx, 4), %xmm1		# xmm1 = y[i]
    
    mulss %xmm0, %xmm1				# xmm1 = x[i]y[i]
    
    test $1, %ebx
    jz even
    subss %xmm1, %xmm2				# if position is odd, we subtract x[i]y[i] from result
    jmp next
even:
    addss %xmm1, %xmm2				# else we add x[i]y[i] to result
next:
    inc %ebx
    jmp new_while
end:
    movss %xmm2, (%eax)				# put result into value of pointer *res
    
    pop %edx
    pop %ebx
    pop %esi
    pop %edi
    mov %ebp, %esp
    pop %ebp
    ret
