#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>

enum { D13 = 13, D10 = 10 };

void please_compute_and_print_some_strange_values_from_some_other_strange_values(
    const char *val1, const char *val2) {
    int64_t res1 = 0, res2 = 0, sgn1 = 1, sgn2 = 1;
    if (*val1 == '-') {
        sgn1 = -1;
        ++val1;
    }
    if (*val2 == '-') {
        sgn2 = -1;
        ++val2;
    }
    while (*val1 != '\0') {
        if (isdigit(*val1)) {
            res1 = D13 * res1 + (int64_t)(*val1 - '0');
        } else {
            res1 = D13 * res1 + (int64_t)(D10 + *val1 - 'a');
        }
        ++val1;
    }
    while (*val2 != '\0') {
        if (isdigit(*val2)) {
            res2 = D13 * res2 + (int64_t)(*val2 - '0');
        } else {
            res2 = D13 * res2 + (int64_t)(D10 + *val2 - 'a');
        }
        ++val2;
    }
    res1 *= sgn1;
    res2 *= sgn2;
    if (res1 + res2 == (int32_t)(res1 + res2)) {
        printf("%d\n", 0);
    } else {
        printf("%d\n", 1);
    }
    if (res2 != 0 && res1 / res2 == (int32_t)(res1 / res2)) {
        printf("%d\n", 0);
    } else {
        printf("%d\n", 1);
    }
}
