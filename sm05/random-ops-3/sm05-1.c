#include <stdlib.h>

enum { MUL = 1103515245, INC = 12345, MOD = 2147483648 };

typedef struct RandomGenerator {
    unsigned int val;
    struct RandomOperations *ops;
} RandomGenerator;

unsigned int next_num(RandomGenerator *rg) {
    unsigned int new_val = ((MUL * rg->val) + INC) % MOD;
    rg->val = new_val;
    return new_val;
}

void destroy_generator(RandomGenerator *rg) {
    free(rg);
}

typedef struct RandomOperations {
    unsigned int (*next)(RandomGenerator *);
    void (*destroy)(RandomGenerator *);
} RandomOperations;

static RandomOperations ro = {.next = next_num, .destroy = destroy_generator};

RandomGenerator *random_create(int seed) {
    RandomGenerator *rg = calloc(1, sizeof(*rg));
    if (rg == NULL) {
        return NULL;
    }
    rg->val = seed;
    rg->ops = &ro;
    return rg;
}

