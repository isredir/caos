#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <sys/wait.h>
#include <unistd.h>

enum { BASE = 10 };

volatile int mode = 0;

void handler(int s) {
    mode = !mode;
}

void ping_pong(int fd[2], int pids[2], long n, int process_num) {
    pids[process_num] = fork();
    if (pids[0] < 0) {
        close(fd[0]);
        close(fd[1]);
        _exit(1);
    }
    if (!pids[process_num]) {
        if (process_num == 0) {
            if (read(fd[0], &pids[1], sizeof(pids[1])) == -1) {
                close(fd[0]);
                close(fd[1]);
                _exit(1);
            }
        }
        while (1) {
            if (mode == process_num) {
                int x;
                if (read(fd[0], &x, sizeof(x)) < 0) {
                    _exit(1);
                }
                printf("%d %d\n", process_num + 1, x);
                fflush(stdout);
                if (x == n) {
                    kill(pids[1 - process_num], SIGINT);
                    _exit(0);
                }
                ++x;
                if (write(fd[1], &x, sizeof(x)) < 0) {
                    _exit(1);
                }
                kill(pids[1 - process_num], SIGUSR1);
                mode = !mode;
            }
        }
    }
}

void write_data(int fd[2], int x) {
    if (write(fd[1], &x, sizeof(x)) < 0) {
        close(fd[0]);
        close(fd[1]);
        _exit(1);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    long n = strtol(argv[1], NULL, BASE);
    struct sigaction sa = {.sa_flags = SA_RESTART, .sa_handler = handler};
    sigaction(SIGUSR1, &sa, NULL);
    int fd[2];
    if (pipe(fd) < 0) {
        _exit(1);
    }
    int pids[2];
    sigset_t cur;
    sigemptyset(&cur);
    sigaddset(&cur, SIGUSR1);
    signalfd(fd[0], &cur, 0);

    ping_pong(fd, pids, n, 0);
    ping_pong(fd, pids, n, 1);

    write_data(fd, pids[1]);
    int x = 1;
    write_data(fd, x);

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
