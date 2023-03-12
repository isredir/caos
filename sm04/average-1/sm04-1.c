#include <stdio.h>

int main() {
    unsigned a;
    unsigned b;
    if (scanf("%u%u", &a, &b) == 2) {
        unsigned c = (a >> 1) + (b >> 1);
        if (a % 2 == 1 && b % 2 == 1) {
            ++c;
        }
        printf("%u\n", c);
    } else {
        return 1;
    }
}
