#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void kill_bill(int *children, int size) {
    for (int i = 1; i < size; ++i) {
        kill(children[i], SIGKILL);
        wait(NULL);
    }
    free(children);
    _exit(1);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        return 0;
    }
    int fd[2];
    pid_t *children = calloc(argc, sizeof(*children));
    if (children == NULL) {
        return 1;
    }
    int prev_in = -1;
    for (int i = 1; i < argc; ++i) {
        int p = pipe(fd);
        if (p == -1) {
            kill_bill(children, i);
        }
        children[i - 1] = fork();
        if (children[i - 1] < 0) {
            kill_bill(children, i);
        } else if (children[i - 1] == 0) {
            if (i < argc - 1) {
                dup2(fd[1], 1);
                close(fd[1]);
                dup2(prev_in, 0);
                close(prev_in);
                close(fd[0]);
            } else {
                dup2(prev_in, 0);
                close(prev_in);
                close(fd[0]);
                close(fd[1]);
            }
            execlp(argv[i], argv[i], NULL);
            free(children);
            _exit(1);
        }
        close(prev_in);
        if (i == argc - 1) {
            close(fd[0]);
            close(fd[1]);
        } else {
            close(fd[1]);
            prev_in = fd[0];
        }
    }
    while (wait(NULL) != -1) {
    }
    free(children);
    return 0;
}
