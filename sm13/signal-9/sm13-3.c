#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int mode = 0;

void handler(int s) {
    if (s == SIGUSR1) {
        mode = 0;
    } else if (s == SIGUSR2) {
        mode = 1;
    } else if (s == SIGTERM) {
        mode = 2;
    }
}

int main() {
    struct sigaction sa = {.sa_flags = SA_RESTART, .sa_handler = handler};
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigset_t prev, cur;
    sigemptyset(&prev);
    sigemptyset(&cur);
    sigaddset(&cur, SIGUSR1);
    sigaddset(&cur, SIGUSR2);
    sigaddset(&cur, SIGTERM);
    sigprocmask(SIG_BLOCK, &cur, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    long long x = 0, y = 0;
    while (1) {
        sigsuspend(&prev);
        if (mode == 0) {
            printf("%lld %lld\n", x, y);
            ++x;
            fflush(stdout);
        } else if (mode == 1) {
            ++y;
        } else {
            exit(0);
        }
    }
}
