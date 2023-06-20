#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum { MAX_FILES_NUM = 20, BYTES_AMOUNT = 16, BASE = 10 };

volatile sig_atomic_t mode = 0;

void handler(int s) {
    if (s == SIGTERM) {
        mode = -1;
    } else if (s >= SIGRTMIN && s <= SIGRTMAX) {
        mode = s - SIGRTMIN + 1;
    }
}

int main(int argc, char **argv) {
    long long sums[MAX_FILES_NUM];
    int fds[MAX_FILES_NUM];
    int flags[MAX_FILES_NUM];
    for (int i = 1; i < argc; ++i) {
        flags[i - 1] = 0;
        sums[i - 1] = 0;
        fds[i - 1] = open(argv[i], O_RDONLY, 0400);
    }
    struct sigaction sa = {.sa_flags = 0, .sa_handler = handler};
    sigaction(SIGTERM, &sa, NULL);
    sigset_t prev, cur;
    sigemptyset(&cur);
    sigemptyset(&prev);
    sigaddset(&cur, SIGTERM);
    for (int i = 1; i < argc; ++i) {
        sigaction(SIGRTMIN + i - 1, &sa, NULL);
        sigaddset(&cur, SIGRTMIN + i - 1);
    }
    sigprocmask(SIG_BLOCK, &cur, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        while (!mode) {
            sigsuspend(&prev);
        }
        if (mode == -1) {
            for (int i = 1; i < argc; ++i) {
                printf("%lld\n", sums[i - 1]);
                fflush(stdout);
                if (!flags[i - 1]) {
                    close(fds[i - 1]);
                }
            }
            _exit(0);
        }
        if (flags[mode - 1]) {
            mode = 0;
            continue;
        }
        char buf[BYTES_AMOUNT];
        errno = 0;
        sigprocmask(SIG_UNBLOCK, &cur, NULL);
        int x = read(fds[mode - 1], buf, BYTES_AMOUNT);
        sigprocmask(SIG_BLOCK, &cur, NULL);
        if (errno != EINTR) {
            if (x == BYTES_AMOUNT) {
                sums[mode - 1] += strtoll(buf, NULL, BASE);
            } else {
                close(fds[mode - 1]);
                flags[mode - 1] = 1;
                mode = 0;
            }
        }
    }
    return 0;
}
