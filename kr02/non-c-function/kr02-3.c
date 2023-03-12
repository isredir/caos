#include <stdio.h>

int call_func(int eax, int ebx, int ecx, int edx) {
    int esi;
    asm volatile ("call func\n\t"
                  : "=S"(esi)
                  : "a"(eax), "b"(ebx), "c"(ecx), "d"(edx)
                  : "ebp");
    return esi;
}