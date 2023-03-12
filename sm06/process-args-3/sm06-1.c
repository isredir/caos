#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i != argc; ++i) {
        if (*argv[i] == '\0') {
            printf("%d\n", -1);
            continue;
        }
        char *r = NULL;
        long val = strtol(argv[i], &r, 10);
        if (errno == ERANGE || *r != '\0') {
            printf("%d\n", -1);
            errno = 0;
            continue;
        }
        if (val == (int8_t)val) {
            printf("%d\n", 1);
        } else if (val == (int16_t)val) {
            printf("%d\n", 2);
        } else if (val == (int32_t)val) {
            printf("%d\n", 4);
        } else {
            printf("%d\n", -1);
        }
        errno = 0;
    }
    return 0;
}
