#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

enum { THREADS_NUM = 3, ITERATIONS = 1000000, HUNDRED = 100 };

double array[THREADS_NUM];
pthread_mutex_t mut;

void *f(void *x) {
    pthread_mutex_lock(&mut);
    for (int i = 0; i < ITERATIONS; i++) {
        array[*(int *)x] += (*(int *)x + 1) * HUNDRED;
        array[(*(int *)x + 1) % THREADS_NUM] -= ((*(int *)x + 1) * HUNDRED + 1);
    }
    pthread_mutex_unlock(&mut);
    return NULL;
}

int main() {
    pthread_t threads[THREADS_NUM];
    int v[THREADS_NUM];
    for (int i = 0; i < THREADS_NUM; i++) {
        v[i] = i;
        pthread_create(&threads[i], NULL, f, (void *)&v[i]);
    }
    for (int i = 0; i < THREADS_NUM; i++) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < THREADS_NUM; i++) {
        printf("%.10g\n", array[i]);
    }
    return 0;
}
