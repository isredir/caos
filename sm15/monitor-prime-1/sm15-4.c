#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

enum { MS = 100000, MAX_COUNT = 8 };

volatile uint32_t last_number = 0;
volatile uint32_t counter = 0;

void handler(int s) {
    printf("%" PRIu32 "\n", last_number);
    fflush(stdout);
    ++counter;
    if (counter == MAX_COUNT) {
        exit(0);
    }
}

int is_prime(uint32_t num) {
    for (uint32_t i = 2; i * i < num; ++i) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    signal(SIGVTALRM, handler);
    uint32_t low, high;
    if (scanf("%" SCNu32 "%" SCNu32, &low, &high) != 2) {
        return 1;
    }
    struct itimerval x = {.it_interval.tv_usec = MS, .it_value.tv_usec = MS};
    setitimer(ITIMER_VIRTUAL, &x, NULL);
    for (size_t i = low; i < high; ++i) {
        if (is_prime(i)) {
            last_number = i;
        }
    }
    printf("-1\n");
    fflush(stdout);
    return 0;
}
