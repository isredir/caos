    .global supercall
supercall:
    push %ebx
    push %ecx
    push %esi
    push %edi

    movl 20(%esp), %eax
    movl 24(%esp), %esi
    movl 28(%esp), %ebx
    movl 32(%esp), %edi
    movl 36(%esp), %ecx
    call supersum

    pop %edi
    pop %esi
    pop %ecx
    pop %ebx

    ret
