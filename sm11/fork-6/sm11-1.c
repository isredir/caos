#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t son, grandson;
    if ((son = fork()) < 0) {
        return 1;
    }
    if (son == 0) {
        if ((grandson = fork()) < 0) {
            return 1;
        }
        if (grandson == 0) {
            printf("3 ");
            return 0;
        }
        wait(NULL);
        printf("2 ");
        return 0;
    }
    wait(NULL);
    printf("1\n");
    return 0;
}
