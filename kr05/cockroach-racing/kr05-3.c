#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }
    int pos = 1;
    while (argv[pos][0] != ';') {
        ++pos;
    }
    char *cmd1 = argv[1];
    char **args1 = calloc(pos, sizeof(*args1));
    for (int i = 1; i < pos; ++i) {
        args1[i - 1] = argv[i];
    }
    char *cmd2 = argv[pos + 1];
    char **args2 = calloc(argc - pos, sizeof(*args2));
    for (int i = pos + 1; i < argc; ++i) {
        args2[i - pos - 1] = argv[i];
    }
    args1[pos - 1] = NULL;
    args2[argc - pos - 1] = NULL;
    int pid1 = fork();
    if (pid1 == 0) {
        execvp(cmd1, args1);
        free(args1);
        _exit(1);
    }
    int pid2 = fork();
    if (pid2 == 0) {
        execvp(cmd2, args2);
        free(args2);
        _exit(1);
    }
    wait(NULL);
    kill(pid1, SIGKILL);
    kill(pid2, SIGKILL);
    free(args1);
    free(args2);
    return 0;
}
