        .att_syntax     noprefix
        .text
        .align  16
        .global invoke
// 8(ebp)  - ebx - arr
// 12(ebp) - esi - size
// 16(ebp) - edi - pivot
invoke:
        push    ebp
        mov     esp, ebp
        push    ebx
        push    esi
        push    edi
        sub     $12, esp

        mov     8(ebp), ebx
        mov     12(ebp), esi
        mov     16(ebp), edi
        call    partition
        mov     edx, eax

        cmp     ebx, 8(ebp)
        jnz     fail
        cmp     esi, 12(ebp)
        jnz     fail
        cmp     edi, 16(ebp)
        jnz     fail

        add     $12, esp
        pop     edi
        pop     esi
        pop     ebx
        pop     ebp
        ret

fail:
        push    $stderr
        push    $msg
        call    fputs
        add     $8, esp
        call    abort

        .section        .rodata
msg:    .asciz  "subroutine 'partition' messed up ebx, esi, or edi\n"
