#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

enum { SIGNAL_CONST = 1024 };

void free_argv(int argc, char **argv) {
    for (int i = 0; i < argc; ++i) {
        free(argv[i]);
    }
    free(argv);
}

int mysystem(const char *cmd) {
    if (*cmd == '\0') {
        return -1;
    }
    int pos = 0, size = 1;
    int argc = 0;
    char **argv = calloc(size, sizeof(*argv));
    while (cmd[pos] != '\0') {
        while (isspace(cmd[pos])) {
            ++pos;
        }
        int i = 0;
        while (cmd[pos + i] != '\0' && !isspace(cmd[pos + i])) {
            ++i;
        }
        if (i == 0) {
            break;
        }
        if (argc == size) {
            argv = realloc(argv, sizeof(*argv) * 2 * size);
            size *= 2;
        }
        argv[argc] = strndup(cmd + pos, i);
        pos += i;
        ++argc;
    }
    if (argc == 0) {
        free_argv(1, argv);
        return -1;
    }
    if (argc == size) {
        argv = realloc(argv, sizeof(*argv) * 2 * size);
    }
    argv[argc] = NULL;
    pid_t pid = fork();
    if (pid == 0) {
        execvp(argv[0], argv);
        free_argv(argc, argv);
        _exit(1);
    } else if (pid < 0) {
        free_argv(argc, argv);
        return -1;
    }
    free_argv(argc, argv);
    int status;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status)) {
        return WTERMSIG(status) + SIGNAL_CONST;
    }
    return WEXITSTATUS(status);
}
