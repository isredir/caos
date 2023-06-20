#include <stdatomic.h>

typedef struct caos_mutex_t {
    _Atomic unsigned int l;
    _Atomic unsigned int w;
} caos_mutex_t;

void caos_mutex_init(caos_mutex_t *m) {
    m->l = 0;
    m->w = 0;
}

unsigned int cmpxchg(_Atomic unsigned int *x, unsigned int a, unsigned int b) {
    atomic_compare_exchange_strong(x, &a, b);
    return a;
}

void caos_mutex_lock(caos_mutex_t *m) {
    while (1) {
        if (cmpxchg(&m->l, 0, 1) == 0) {
            break;
        }
        ++m->w;
        futex_wait((_Atomic int *)&m->l, 1);
        --m->w;
    }
}

void caos_mutex_unlock(caos_mutex_t *m) {
    m->l = 0;
    if (m->w > 0) {
        futex_wake((_Atomic int *)&m->l, 1);
    }
}
