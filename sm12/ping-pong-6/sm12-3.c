#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

enum { BASE = 10 };

void ping_pong(int fd[2][2], long n, int process_num) {
    pid_t pid = fork();
    if (pid == 0) {
        close(fd[process_num][0]);
        close(fd[1 - process_num][1]);
        dup2(fd[1 - process_num][0], 0);
        close(fd[1 - process_num][0]);
        long val;
        while (scanf("%ld", &val) == 1) {
            if (val == n) {
                exit(0);
            }
            printf("%d %ld\n", process_num + 1, val);
            fflush(stdout);
            dprintf(fd[process_num][1], "%ld\n", val + 1);
        }
        close(fd[process_num][1]);
        exit(0);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    long n = strtol(argv[1], NULL, BASE);
    if (n < 2) {
        printf("Done\n");
        return 0;
    }
    int fd[2][2];
    if (pipe(fd[0]) == -1 || pipe(fd[1]) == -1) {
        return 1;
    }
    ping_pong(fd, n, 0);
    close(fd[1][0]);
    close(fd[0][1]);
    ping_pong(fd, n, 1);
    close(fd[0][0]);
    dprintf(fd[1][1], "%ld\n", (long)1);
    close(fd[1][1]);
    wait(NULL);
    wait(NULL);
    printf("Done\n");
    return 0;
}
