#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t cur, prev;
    prev = getpid();
    int x;
    while (scanf("%d", &x) == 1) {
        if ((cur = fork()) < 0) {
            return 1;
        }
        if (cur == 0) {
            continue;
        }
        int status;
        waitpid(cur, &status, 0);
        if (status == 0) {
            printf("%d\n", x);
            return 0;
        }
        if (getpid() == prev) {
            printf("%d\n", -1);
            return 0;
        }
        return 1;
    }
    return 0;
}
