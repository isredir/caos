#include <stdio.h>

int main() {
    unsigned int eax, ecx, edx;
    asm volatile("cpuid\n\t"
            : "=a"(eax), "=c"(ecx), "=d"(edx)
            : "a"(1)
            : "%ebx");
    unsigned int model_id = (eax >> 4) & 15;
    unsigned int family_id = (eax >> 8) & 15;
    if (family_id == 6 || family_id == 15) {
        unsigned int extended_model_id = (eax >> 16) & 127;
        model_id += (extended_model_id << 4);
    }
    if (family_id == 15) {
        unsigned int extended_family_id = (eax >> 20) & 15;
        family_id += extended_family_id;
    }
    printf("family=%d model=%d ecx=0x%x edx=0x%x\n", family_id, model_id, ecx, edx);
}