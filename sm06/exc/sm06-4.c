#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

enum { SIZE = 10, ERR = 13 };

int exc_stack[SIZE];
int pos = 0;
jmp_buf jmp_points_stack[SIZE];

jmp_buf *try(int exception) {
    exc_stack[pos] = exception;
    if (!setjmp(jmp_points_stack[pos])) {
        jmp_buf *jmp_point = &jmp_points_stack[pos];
        ++pos;
        return jmp_point;
    }
    return NULL;
}

void endtry() {
    exc_stack[pos] = 0;
    --pos;
}

void throw(int exception) {
    while (pos >= 0) {
        --pos;
        if (exc_stack[pos] == exception) {
            longjmp(jmp_points_stack[pos], 1);
        }
    }
    exit(ERR);
}