#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int s) {
    char str[28] = "We communicate on my terms.\n";
    if (write(STDOUT_FILENO, &str, sizeof(str)) < 0) {
        _exit(1);
    }
    fflush(stdout);
}

int main() {
    struct sigaction sa = {.sa_flags = SA_RESTART, .sa_handler = handler};
    sigaction(SIGTERM, &sa, NULL);
    char x;
    while (1) {
        if (read(STDIN_FILENO, &x, sizeof(x)) <= 0) {
            break;
        }
        if (write(STDOUT_FILENO, &x, sizeof(x)) < 0) {
            _exit(1);
        }
        fflush(stdout);
    }
    return 0;
}
