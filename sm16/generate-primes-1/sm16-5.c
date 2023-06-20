#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;

int is_prime(uint64_t n) {
    if (n == 2) {
        return 1;
    }
    if (n < 2 || n % 2 == 0) {
        return 0;
    }
    for (uint64_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int s = 0;
uint64_t cur = 0;
int flag = 0;

void *f(void *x) {
    uint64_t y = *(uint64_t *)x;
    while (1) {
        pthread_mutex_lock(&mut1);
        if (flag) {
            break;
        }
        pthread_mutex_unlock(&mut1);
        if (is_prime(y)) {
            pthread_mutex_lock(&mut2);
            s = 1;
            cur = y;
            ++y;
            pthread_cond_signal(&condvar);
            pthread_mutex_unlock(&mut2);
        } else {
            ++y;
        }
    }
    return NULL;
}

int main() {
    uint64_t base;
    int32_t count;
    if (scanf("%" SCNu64 "%" SCNd32, &base, &count) != 2) {
        return 1;
    }
    pthread_t thread;
    pthread_create(&thread, NULL, f, (void *)&base);
    for (int32_t i = 0; i < count; ++i) {
        uint64_t tmp = 0;
        pthread_mutex_lock(&mut2);
        while (!s) {
            pthread_cond_wait(&condvar, &mut2);
        }
        tmp = cur;
        s = 0;
        pthread_mutex_unlock(&mut2);
        printf("%" PRIu64 "\n", tmp);
    }
    pthread_mutex_lock(&mut1);
    flag = 1;
    pthread_mutex_unlock(&mut1);
    pthread_join(thread, NULL);
    return 0;
}
