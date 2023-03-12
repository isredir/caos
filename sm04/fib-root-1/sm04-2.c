#include <inttypes.h>
#include <stdio.h>

int main() {
    int64_t a;
    if (scanf("%llX", &a) > 0) {
        while (1) {
            if (a == 0) {
                printf("%X", -1);
                continue;
            }
            int64_t b = 0, c = 1, d;
            int i = 0;
            while (a - c >= b) {
                d = c;
                c += b;
                b = d;
                ++i;
            }
            printf("%X ", i);
            if (scanf("%llX", &a) < 0) {
                break;
            }
        }
    }
    printf("\n");
}