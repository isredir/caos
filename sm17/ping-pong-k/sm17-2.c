#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *fds;
int n;

void *pingpong(void *arg) {
    int t = 0;
    int next = 0;
    while (1) {
        if (read(fds[(*(int *)arg) * 2], &t, sizeof(t)) < 0) {
            _exit(1);
        }
        if (scanf("%d", &next) == 1) {
            printf("%d %d\n", *(int *)arg, next);
            fflush(stdout);
            next %= n;
            if (next < 0) {
                next += n;
            }
            if (write(fds[next * 2 + 1], &next, sizeof(next)) < 0) {
                _exit(1);
            }
            fflush(stdout);
        } else {
            next = ((*(int *)arg) + 1) % n;
            if (write(fds[next * 2 + 1], &next, sizeof(next)) < 0) {
                _exit(1);
            }
            fflush(stdout);
            break;
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    n = atoi(argv[1]);
    pthread_t *threads = calloc(n, sizeof(*threads));
    int *arr = calloc(n, sizeof(*arr));
    fds = calloc(n * 2, sizeof(*fds));
    for (int i = 0; i < n; ++i) {
        arr[i] = i;
        if (pipe(&(fds[i * 2])) < 0) {
            return 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        pthread_create(&threads[i], NULL, pingpong, (void *)&arr[i]);
    }
    int t = 0;
    if (write(fds[1], &t, sizeof(t)) < 0) {
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < n; ++i) {
        close(fds[i * 2]);
        close(fds[i * 2 + 1]);
    }
    free(fds);
    free(threads);
    free(arr);
    return 0;
}
