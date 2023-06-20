#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void process(int n, int fd[2][2], int process_num, double a, double b) {
    pid_t pid = fork();
    if (!pid) {
        pid_t child = fork();
        if (!child) {
            double count = 0.0;
            for (int i = 0; i < n + 1; ++i) {
                double s = 0.0;
                if (process_num == 0) {
                    s = sin(a);
                } else {
                    s = cos(a);
                }
                a += b;
                if (write(fd[1 - process_num][1], &s, sizeof(s)) < 0) {
                    exit(1);
                }
                if (read(fd[process_num][0], &s, sizeof(s)) < 0) {
                    exit(1);
                }
                if (process_num == 0) {
                    count += s * s;
                } else {
                    count += fabs(s);
                }
            }
            printf("%d %.11g\n", process_num + 1, count);
            fflush(stdout);
            close(fd[0][0]);
            close(fd[0][1]);
            close(fd[1][0]);
            close(fd[1][1]);
            exit(0);
        }
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[1][1]);
        wait(NULL);
        exit(0);
    }
}

int main(int argc, char **argv) {
    if (argc < 4) {
        return 1;
    }
    double a = strtod(argv[1], NULL);
    double b = strtod(argv[3], NULL);
    int fd[2][2];
    int n = atoi(argv[2]);
    if (pipe(fd[0]) == -1 || pipe(fd[1]) == -1) {
        return 1;
    }
    process(n, fd, 0, a, b);
    process(n, fd, 1, a, b);
    close(fd[0][0]);
    close(fd[0][1]);
    close(fd[1][0]);
    close(fd[1][1]);
    while (wait(NULL) > 0) {
        ;
    }
    printf("0 0\n");
    return 0;
}
