#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <limits.h>                                                             
#include <stdlib.h>

void *f(void *num) {
    int x;
    while (scanf("%d", &x) != 1) {
        return NULL;
    }
    pthread_t thread;
    pthread_create(&thread, NULL, f, NULL);
    pthread_join(thread, NULL);
    printf("%d\n", x);
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, f, NULL);
    pthread_join(thread, NULL);
    return 0;
}
