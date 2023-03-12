#include <inttypes.h>
#include <stdio.h>

int main() {
    int a, b;
    unsigned int n;
    if (scanf("%d%d%d", &a, &b, &n) == 3) {
        printf("%*s", n + 1, "");
        for (int i = a; i < b; ++i) {
            if (i + 1 < b) {
                printf("%*d ", n, i);
            } else {
                printf("%*d", n, i);
            }
        }
        printf("\n");
        for (int i = a; i < b; ++i) {
            printf("%*d ", n, i);
            for (int j = a; j < b; ++j) {
                if (j + 1 < b) {
                    printf("%*lld ", n, (int64_t)i * j);
                } else {
                    printf("%*lld", n, (int64_t)i * j);
                }
            }
            printf("\n");
        }
    } else {
        return 1;
    }
}
