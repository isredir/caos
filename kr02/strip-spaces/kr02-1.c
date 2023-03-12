#include <ctype.h>
#include <stdio.h>
#include <string.h>


void strip_spaces(char *buf) {
    char *buf_copy = buf;
    while (isspace(*buf)) {
        ++buf;
    }
    while (*buf) {
        if (!isspace(*buf)) {
            *buf_copy = *buf;
            ++buf;
            ++buf_copy;
        } else {
            while (isspace(*buf)) {
                ++buf;
            }
            if (*buf) {
                *buf_copy = ' ';
                ++buf_copy;
            }
        }
    }
    *buf_copy = '\0';
}
