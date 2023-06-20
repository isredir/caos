#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

enum { D1E3 = 1000, D1E9 = 1000000000 };

void handler(int s) {
    _exit(0);
}

int main() {
    int64_t sec, nsec;
    signal(SIGALRM, handler);
    if (scanf("%" SCNd64, &sec) != 1) {
        return 1;
    }
    if (scanf("%" SCNd64, &nsec) != 1) {
        return 1;
    }
    struct timeval x;
    gettimeofday(&x, NULL);
    int64_t d =
        (sec - (int64_t)x.tv_sec) * D1E9 + (nsec - (int64_t)x.tv_usec * D1E3);
    if (d < 0) {
        return 0;
    }
    struct itimerval y;
    y.it_value.tv_sec = d / D1E9;
    y.it_value.tv_usec = (d % D1E9) / D1E3;
    setitimer(ITIMER_REAL, &y, NULL);
    pause();
    return 0;
}
