    .text
    .global f1
f1:
    pushl   %eax
    call    printf
    popl    %eax
    ret

    .global str1
    .global str2
str1:
    .asciz  "Hello, "
str2:
    .asciz  "world!\n"
        
