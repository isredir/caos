#include <stdio.h>
#include <time.h>

enum { SECONDS_IN_DAY = 86400, BUF_SIZE = 30 };

int main() {
    int x;
    time_t y;
    while (scanf("%d", &x) != EOF) {
        time_t now = time(NULL);
        if (__builtin_mul_overflow(x, SECONDS_IN_DAY, &y) ||
            __builtin_add_overflow(now, y, &now)) {
            printf("OVERFLOW\n");
            continue;
        }
        struct tm *local_time = localtime(&now);
        char buf[BUF_SIZE];
        strftime(buf, BUF_SIZE, "%Y-%m-%d\n", local_time);
        printf("%s", buf);
    }
    return 0;
}
