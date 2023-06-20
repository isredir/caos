#include <pthread.h>
#include <stdio.h>

enum { THREADS_NUM = 10 };

pthread_t threads[THREADS_NUM];

void *f(void *num) {
    if (*(int *)num > 0) {
        pthread_join(threads[*(int *)num - 1], NULL);
    }
    printf("%d\n", (*(int *)num));
    return NULL;
}

int main() {
    int arr[THREADS_NUM];
    for (int i = 0; i < THREADS_NUM; ++i) {
        arr[i] = i;
    }
    for (int i = 0; i < THREADS_NUM; ++i) {
        pthread_create(&threads[i], NULL, f, (void *)&arr[i]);
    }
    pthread_join(threads[THREADS_NUM - 1], NULL);
    return 0;
}
