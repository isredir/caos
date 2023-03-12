#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>

int main() {
    int64_t sum = 0;
    while (1) {
        int c = getchar();
        if (c == EOF) {
            break;
        }
        if (isdigit(c)) {
            sum += c - '0';
        }
    }
    printf("%lld\n", sum);
}