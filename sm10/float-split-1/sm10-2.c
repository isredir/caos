#include <stdio.h>

typedef union FloatNumber {
    float f;

    struct {
        unsigned mnt : 23;
        unsigned exp : 8;
        unsigned sgn : 1;
    };
} FloatNumber;

int main() {
    FloatNumber num;
    while (scanf("%f", &num.f) == 1) {
        printf("%u %u %x\n", num.sgn, num.exp, num.mnt);
    }
    return 0;
}
