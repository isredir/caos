#include <memory.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

enum { D4 = 4 };

struct Task {
    const void *begin;
    size_t end;
    void *init_state, *cur_state;
};

size_t task_size;
void (*op)(void *state, void *el);

void *f(void *arg) {
    struct Task *task = (struct Task *)arg;
    void *start = (void *)task->begin;
    void *state = calloc(1, task_size);
    memcpy(state, task->init_state, task_size);
    task->cur_state = state;
    for (int i = 0; i < task->end; ++i) {
        op(task->cur_state, start);
        start += task_size;
    }
    return NULL;
}

void std_accumulate(void *result, const void *begin, size_t size, size_t n,
                    void *init_state,
                    void (*binary_op)(void *state, void *el)) {
    size_t nthreads = n / (D4 + 1) + 1;
    if (nthreads > D4) {
        nthreads = D4;
    }
    op = binary_op;
    pthread_t *threads = calloc(nthreads - 1, sizeof(*threads));
    struct Task *tasks = calloc(nthreads, sizeof(*tasks));
    size_t sum = 0;
    const void *start = begin;
    task_size = size;
    for (int i = 0; i < nthreads - 1; ++i) {
        tasks[i].begin = start;
        tasks[i].end = n / nthreads;
        tasks[i].init_state = init_state;
        pthread_create(&threads[i], NULL, f, (void *)&tasks[i]);
        sum += n / nthreads;
        start += (n / nthreads) * size;
    }
    tasks[nthreads - 1].begin = start;
    tasks[nthreads - 1].end = n - sum;
    tasks[nthreads - 1].init_state = init_state;
    f((void *)&tasks[nthreads - 1]);
    for (int i = 0; i < nthreads - 1; ++i) {
        pthread_join(threads[i], NULL);
    }
    void *state = calloc(1, size);
    memcpy(state, init_state, size);
    for (int i = 0; i < nthreads; ++i) {
        binary_op(state, tasks[i].cur_state);
    }
    memcpy(result, state, size);
    free(state);
    for (int i = 0; i < nthreads; ++i) {
        free(tasks[i].cur_state);
    }
    free(tasks);
    free(threads);
}
