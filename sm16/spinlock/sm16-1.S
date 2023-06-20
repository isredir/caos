.global spin_lock, spin_unlock

spin_lock:
    push %ebp
    mov %esp, %ebp
loop:
    pause
    mov 8(%ebp), %ecx
    xor %eax, %eax
    add $1, %eax
    xchg %eax, (%ecx)
    cmp $0, %eax
    jnz loop

    mov %ebp, %esp
    pop %ebp
    ret

spin_unlock:
    push %ebp
    mov %esp, %ebp

    mov 8(%ebp), %ecx
    xor %edx, %edx
    xor %edx, %edx
    lock btr %edx, (%ecx)
    
    mov %ebp, %esp
    pop %ebp
    ret
