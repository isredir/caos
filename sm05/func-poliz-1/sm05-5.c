#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { ITEMS_SIZE = 10, D10 = 10 };

// opaque structure for poliz calculation state
typedef struct PolizState {
    int *top;
    int *start;
    int capacity;
    int err;
} PolizState;

// poliz operation handler
typedef int (*PolizFuncT)(struct PolizState *state, int iextra);

typedef struct PolizItem {
    PolizFuncT handler;
    int iextra;
} PolizItem;

// runtime errors
enum {
    PE_OK,               // no error
    PE_STACK_UNDERFLOW,  // not enough elements on stack
    PE_INVALID_INDEX,    // s or d operations refer to invalid index
    PE_DIVISION_BY_ZERO,
    PE_INT_OVERFLOW,
    PE_READ_FAILED,  // read from stdin failed to convert integer for any reason
    PE_OUT_OF_MEMORY,
};

int push(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    if (state->top - state->start == state->capacity) {
        int new_capacity = 2 * state->capacity;
        int *new_state =
            realloc(state->start, new_capacity * sizeof(*state->start));
        if (new_state == NULL) {
            state->err = PE_OUT_OF_MEMORY;
            return -state->err;
        }
        state->start = new_state;
        state->top = state->start + state->capacity;
        state->capacity = new_capacity;
    }
    ++state->top;
    *(state->top) = iextra;
    return -state->err;
}

int pop(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    if (state->top - state->start == 0) {
        state->err = PE_STACK_UNDERFLOW;
        return -state->err;
    }
    --state->top;
    return -state->err;
}

int add(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    if (state->top - state->start < 2) {
        state->err = PE_STACK_UNDERFLOW;
        return -state->err;
    }
    int64_t res = (int64_t) * (state->top - 1) + (int64_t) * (state->top);
    if (res > INT32_MAX || res < INT32_MIN) {
        state->err = PE_INT_OVERFLOW;
        return -state->err;
    }
    pop(state, iextra);
    pop(state, iextra);
    int err = push(state, (int)res);
    if (err != 0) {
        state->err = err;
        return -state->err;
    }
    return -state->err;
}

int sub(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    if (state->top - state->start < 2) {
        state->err = PE_STACK_UNDERFLOW;
        return -state->err;
    }
    int64_t res = (int64_t) * (state->top - 1) - (int64_t) * (state->top);
    if (res > INT32_MAX || res < INT32_MIN) {
        state->err = PE_INT_OVERFLOW;
        return -state->err;
    }
    pop(state, iextra);
    pop(state, iextra);
    int err = push(state, (int)res);
    if (err != 0) {
        state->err = err;
        return -state->err;
    }
    return -state->err;
}

int mul(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    if (state->top - state->start < 2) {
        state->err = PE_STACK_UNDERFLOW;
        return -state->err;
    }
    int64_t res = (int64_t) * (state->top - 1) * (int64_t) * (state->top);
    if (res > INT32_MAX || res < INT32_MIN) {
        state->err = PE_INT_OVERFLOW;
        return -state->err;
    }
    pop(state, iextra);
    pop(state, iextra);
    int err = push(state, (int)res);
    if (err != 0) {
        state->err = err;
        return -state->err;
    }
    return -state->err;
}

int divide(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    if (state->top - state->start < 2) {
        state->err = PE_STACK_UNDERFLOW;
        return -state->err;
    }
    if (*(state->top) == 0) {
        state->err = PE_DIVISION_BY_ZERO;
        return -state->err;
    }
    int64_t rem = (int64_t) * (state->top - 1) % (int64_t) * (state->top);
    if (rem < 0) {
        rem += labs(*(state->top));
    }
    int64_t res =
        ((int64_t) * (state->top - 1) - rem) / (int64_t) * (state->top);
    if (res > INT32_MAX || res < INT32_MIN) {
        state->err = PE_INT_OVERFLOW;
        return -state->err;
    }
    pop(state, iextra);
    pop(state, iextra);
    int err = push(state, (int)res);
    if (err != 0) {
        state->err = err;
        return -state->err;
    }
    return -state->err;
}

int mod(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    if (state->top - state->start < 2) {
        state->err = PE_STACK_UNDERFLOW;
        return -state->err;
    }
    if (*(state->top) == 0) {
        state->err = PE_DIVISION_BY_ZERO;
        return -state->err;
    }
    int64_t res = (int64_t) * (state->top - 1) % (int64_t) * (state->top);
    if (res < 0) {
        res += labs(*(state->top));
    }
    if (res > INT32_MAX || res < INT32_MIN) {
        state->err = PE_INT_OVERFLOW;
        return -state->err;
    }
    pop(state, iextra);
    pop(state, iextra);
    int err = push(state, (int)res);
    if (err != 0) {
        state->err = err;
        return -state->err;
    }
    return -state->err;
}

int neg(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    if (state->top - state->start == 0) {
        state->err = PE_STACK_UNDERFLOW;
        return -state->err;
    }
    int64_t res = -(int64_t) * (state->top);
    if (res > INT32_MAX || res < INT32_MIN) {
        state->err = PE_INT_OVERFLOW;
        return -state->err;
    }
    pop(state, iextra);
    int err = push(state, (int)res);
    if (err != 0) {
        state->err = err;
        return -state->err;
    }
    return -state->err;
}

int read(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    int res;
    if (scanf("%d", &res) != 1) {
        state->err = PE_READ_FAILED;
        return -state->err;
    }
    if (res > INT32_MAX || res < INT32_MIN) {
        state->err = PE_INT_OVERFLOW;
        return -state->err;
    }
    int err = push(state, res);
    if (err != 0) {
        state->err = err;
        return -state->err;
    }
    return -state->err;
}

int write(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    if (state->top - state->start == 0) {
        state->err = PE_STACK_UNDERFLOW;
        return -state->err;
    }
    int res = *(state->top);
    printf("%d", res);
    pop(state, iextra);
    return -state->err;
}

int endl(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    printf("\n");
    return -state->err;
}

int copy(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    if (state->top - state->start <= iextra || iextra < 0) {
        state->err = PE_INVALID_INDEX;
        return -state->err;
    }
    int copy_num = *(state->top - iextra);
    int err = push(state, copy_num);
    if (err != 0) {
        state->err = err;
        return -state->err;
    }
    return -state->err;
}

int swap(PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    }
    if (iextra == 0) {
        return -state->err;
    }
    if (state->top - state->start <= iextra || iextra < 0) {
        state->err = PE_INVALID_INDEX;
        return -state->err;
    }
    int swap_num = *(state->top - iextra);
    int top_num = *(state->top);
    *(state->top - iextra) = top_num;
    *(state->top) = swap_num;
    return -state->err;
}

int64_t read_number(const char *str, int *start) {
    int64_t num = 0;
    while (isdigit(str[*start])) {
        int c = str[*start] - '0';
        num = num * D10 + c;
        ++*start;
    }
    return num;
}

struct PolizItem *poliz_compile(const char *str) {
    PolizItem *items = calloc(ITEMS_SIZE, sizeof(*items));
    PolizItem *item = items;
    int items_capacity = 1;
    for (int i = 0; i < strlen(str);) {
        if (str[i] == ' ') {
            ++i;
            continue;
        }
        if (isdigit(str[i])) {
            int64_t num = read_number(str, &i);
            item->handler = &push;
            item->iextra = (int)num;
        } else if (str[i] == 'd') {
            ++i;
            item->handler = &copy;
            int64_t num = 0;
            if (isdigit(str[i])) {
                num = read_number(str, &i);
            }
            item->iextra = (int)num;
        } else if (str[i] == 's') {
            ++i;
            int64_t num = 1;
            item->handler = &swap;
            if (isdigit(str[i])) {
                num = read_number(str, &i);
            }
            item->iextra = (int)num;
        } else if (str[i] == '+') {
            ++i;
            if (isdigit(str[i])) {
                int64_t num = read_number(str, &i);
                item->handler = &push;
                item->iextra = (int)num;
            } else {
                item->handler = &add;
            }
        } else if (str[i] == '-') {
            ++i;
            if (isdigit(str[i])) {
                int64_t num = read_number(str, &i);
                item->handler = &push;
                item->iextra = (int)(-num);
            } else {
                item->handler = &sub;
            }
        } else if (str[i] == '*') {
            item->handler = &mul;
            ++i;
        } else if (str[i] == '/') {
            item->handler = &divide;
            ++i;
        } else if (str[i] == '%') {
            item->handler = &mod;
            ++i;
        } else if (str[i] == '#') {
            item->handler = &neg;
            ++i;
        } else if (str[i] == 'r') {
            item->handler = &read;
            ++i;
        } else if (str[i] == 'w') {
            item->handler = &write;
            ++i;
        } else if (str[i] == 'n') {
            item->handler = &endl;
            ++i;
        } else if (str[i] == ';') {
            item->handler = &pop;
            ++i;
        }
        if (item - items == items_capacity) {
            int new_capacity = 2 * items_capacity;
            PolizItem *new_items =
                realloc(items, (new_capacity + 1) * sizeof(*new_items));
            items = new_items;
            item = items + items_capacity;
            items_capacity = new_capacity;
        }
        ++item;
    }
    item->handler = NULL;
    item->iextra = 0;
    return items;
}

struct PolizState *poliz_new_state(void) {
    PolizState *new_state = calloc(1, sizeof(*new_state));
    new_state->start = calloc(ITEMS_SIZE, sizeof(new_state->start));
    new_state->top = new_state->start;
    new_state->capacity = ITEMS_SIZE;
    new_state->err = PE_OK;
    return new_state;
}

void poliz_free_state(struct PolizState *state) {
    free(state->start);
    free(state);
}

int poliz_last_error(struct PolizState *state) {
    return state->err;
}
