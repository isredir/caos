#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    struct stat st;
    for (int i = 1; i < argc; ++i) {
        if (lstat(argv[i], &st) == -1) {
            printf("%s (missing)\n", argv[i]);
        } else if (S_ISLNK(st.st_mode)) {
            if (stat(argv[i], &st) == -1) {
                printf("%s (broken symlink)\n", argv[i]);
            } else {
                printf("%s\n", argv[i]);
            }
        } else {
            if (access(argv[i], F_OK) == 0) {
                printf("%s\n", argv[i]);
            } else {
                printf("%s (missing)\n", argv[i]);
            }
        }
    }
    return 0;
}