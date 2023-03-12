	.global computation
computation:
    movl 4(%esp), %ecx
    movl 8(%esp), %eax

    xorps %xmm0, %xmm0
    test %eax, %eax
    jz end

    movups (%ecx), %xmm0
    subl $4, %eax
    addl $16, %ecx
    test %eax, %eax
    jz end

loop:
    test %eax, %eax
    jz end
    movups (%ecx), %xmm1
    mulps %xmm1, %xmm0
    subl $4, %eax
    addl $16, %ecx
    jmp loop

end:
    movl 12(%esp), %eax
    haddps %xmm0, %xmm0
    haddps %xmm0, %xmm0
    movss %xmm0, (%eax)
    ret
