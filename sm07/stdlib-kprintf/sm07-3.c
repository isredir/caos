#include "drivers/uart.h"
#include <stdarg.h>

void kprintf(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int i = 0;
    while (fmt[i] != '\0') {
        if (fmt[i] == '%' && fmt[i + 1] == 'u') {
            unsigned arg = va_arg(ap, unsigned);
            unsigned pow = 1;
            while (pow <= arg / 10) {
                pow *= 10;
            }
            while (pow > 0) {
                uartputc((char)('0' + arg / pow));
                arg %= pow;
                pow /= 10;
            }
            i += 2;
        } else if (fmt[i] == '%' && fmt[i + 1] == 'x') {
            unsigned arg = va_arg(ap, unsigned);
            unsigned pow = 1;
            while (pow <= arg / 16) {
                pow *= 16;
            }
            while (pow > 0) {
                if (arg / pow < 10) {
                    uartputc((char) ('0' + arg / pow));
                } else {
                    uartputc((char) ('a' + arg / pow - 10));
                }
                arg %= pow;
                pow /= 16;
            }
            i += 2;
        } else {
            uartputc(fmt[i]);
            ++i;
        }
    }
    va_end(ap);
}
