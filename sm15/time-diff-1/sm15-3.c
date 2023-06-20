#define _XOPEN_SOURCE

#include <stdio.h>
#include <time.h>

enum { BUF_SIZE = 1000 };

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    time_t time_sum;
    int first_line = 0;
    char datetime[BUF_SIZE];
    while (fgets(datetime, BUF_SIZE, file)) {
        struct tm tm;
        strptime(datetime, "%Y/%m/%d %H:%M:%S", &tm);
        tm.tm_isdst = -1;
        time_t time_diff = mktime(&tm);
        if (!first_line) {
            first_line = 1;
            time_sum = time_diff;
            continue;
        }
        time_diff -= time_sum;
        printf("%ld\n", time_diff);
        time_sum += time_diff;
    }
}
