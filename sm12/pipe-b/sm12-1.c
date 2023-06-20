#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }
    int fd[2];
    int p = pipe(fd);
    if (p == -1) {
        return 1;
    }
    pid_t pid1 = fork();
    if (pid1 == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }
    pid_t pid2 = fork();
    if (pid2 == 0) {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[2], argv[2], NULL);
        _exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
