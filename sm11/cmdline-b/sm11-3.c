#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 4) {
        return 1;
    }
    pid_t pid = fork();
    if (pid == 0) {
        int fd_in = open(argv[2], O_RDONLY);
        int fd_out = open(argv[3], O_TRUNC | O_CREAT | O_RDWR, 0666);
        dup2(fd_in, STDIN_FILENO);
        dup2(fd_out, STDOUT_FILENO);
        close(fd_in);
        close(fd_out);
        execlp(argv[1], argv[1], NULL);
    }
    wait(NULL);
    return 0;
}
