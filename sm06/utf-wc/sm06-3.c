#include <stdio.h>

enum { D14 = 14, D30 = 30, D31 = 31, D63 = 63, LOWER = 1024, UPPER = 1279 };

int main() {
    int count = 0, cyrillic_count = 0;
    while (1) {
        int c = fgetc(stdin);
        if (c == EOF) {
            break;
        }
        ++count;
        int next = 0;
        if (c >> 5 == 6) {
            int c1 = fgetc(stdin);
            int num = ((c & D31) << 6) + (c1 & D63);
            if (num >= LOWER && num <= UPPER) {
                ++cyrillic_count;
            }
        } else if (c >> 4 == D14) {
            next = 2;
        } else if (c >> 3 == D30) {
            next = 3;
        }
        for (int i = 0; i < next; ++i) {
            int c1 = fgetc(stdin);
            ++c1;
        }
    }
    printf("%d %d\n", count, cyrillic_count);
    return 0;
}
