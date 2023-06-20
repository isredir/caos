#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <limits.h>                                                             
#include <stdlib.h>

struct Item {
    struct Item *next;
    long long value;
};

enum { THREADS_NUM = 100, N = 1000 };

struct Item* _Atomic head;

void *f(void *num) {
    for (int i = 0; i < N; ++i) {
        struct Item* node = calloc(1, sizeof(*node));
        node->value = N * (*(int *)num) + i;
        node->next = atomic_exchange_explicit(&head, node, memory_order_relaxed);
        sched_yield();
    }
    return NULL;
}


int main() {
    
pthread_t threads[THREADS_NUM];
    pthread_attr_t a;
    pthread_attr_init(&a);
    pthread_attr_setstacksize(&a, PTHREAD_STACK_MIN);
    int *arr = calloc(THREADS_NUM, sizeof(*arr));
    for (int i = 0; i < THREADS_NUM; ++i) {
        arr[i] = i;
    }
    for (int i = 0; i < THREADS_NUM; ++i) {
        pthread_create(&threads[i], &a, f, (void *) &arr[i]);
    }
    pthread_attr_destroy(&a);
    for (int i = 0; i < THREADS_NUM; ++i) {
        pthread_join(threads[i], NULL);
    }
    while (head) {
        printf("%lld\n", head->value);
        struct Item *node = head;
        head = head->next;
        free(node);
    }
    free(arr);
    return 0;
}
