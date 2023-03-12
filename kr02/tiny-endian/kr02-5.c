#include <inttypes.h>
#include <stdio.h>

void tinyconv(uint8_t bytes[], size_t size) {
    for (int i = 0; i < size; ++i) {
        char str[8];
        int c = 0;
        while (bytes[i] > 0 || c < 8) {
            if (bytes[i] % 2 == 0) {
                str[c] = '0';
            } else {
                str[c] = '1';
            }
            bytes[i] /= 2;
            ++c;
        }
        bytes[i] = 0;
        for (c = 0; c < 8; ++c) {
            bytes[i] = 2 * bytes[i] + (str[c] - '0');
        }
    }
}
