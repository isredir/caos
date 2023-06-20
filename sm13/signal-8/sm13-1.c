#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int count = 0;

void handler(int s) {
    if (count >= 4) {
        exit(0);
    }
    printf("%d\n", count);
    ++count;
    fflush(stdout);
}

int main() {
    struct sigaction sa = {.sa_flags = SA_RESTART, .sa_handler = handler};
    sigaction(SIGINT, &sa, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        pause();
    }
}
