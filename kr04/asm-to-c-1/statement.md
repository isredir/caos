|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem ku04-5: kr04-5 (дореш)

На языке Си напишите функцию `computation` вычисляющую то же что приведенный ниже код на asm.

Функция ничего не возвращает. Аргументы функции неизвестны - вы должны выяснить их количество и типы
из приведенного кода.

    
    
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
    

Считайте, что операции с вещественными числами ассоциативны. Ассемблерные вставки использовать
нельзя.

