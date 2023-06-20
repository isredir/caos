#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile int mode = 0;

void handler(int s) {
    if (s == SIGUSR1) {
        mode = 0;
    } else if (s == SIGUSR2) {
        mode = 1;
    }
}

int main() {
    struct sigaction sa = {.sa_flags = SA_RESTART, .sa_handler = handler};
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    long long x;
    while (scanf("%lld", &x) == 1) {
        if (!mode) {
            printf("%lld\n", -x);
            fflush(stdout);
        } else {
            printf("%lld\n", x * x);
            fflush(stdout);
        }
    }
}
