#include <stdint.h>
#include <stdio.h>

enum { MNT = 24, EXP = 9 };

int is_float(uint32_t x) {
    int exp = 1;
    while (x % 2 == 0 && exp < EXP) {
        x >>= 1;
        ++exp;
    }
    return ((x >> MNT) == 0);
}

int main() {
    uint32_t x;
    while (scanf("%u", &x) == 1) {
        printf("%d\n", is_float(x));
    }
    return 0;
}
