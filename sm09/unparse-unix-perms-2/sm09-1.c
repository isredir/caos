#include <stdio.h>
#include <sys/stat.h>

enum { SIZE = 9, D2 = 2, D5 = 5, D8 = 8 };

const char *perms_to_str(char *buf, size_t size, int perms) {
    if (size == 0) {
        return buf;
    }
    size_t new_size = size - 1;
    if (SIZE < new_size) {
        new_size = SIZE;
    }
    int s_perms[SIZE] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP,
                         S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
    char new_perms[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        if (perms & s_perms[i]) {
            if (i % 3 == 0) {
                new_perms[i] = 'r';
            } else if (i % 3 == 1) {
                new_perms[i] = 'w';
            } else {
                new_perms[i] = 'x';
            }
        } else {
            new_perms[i] = '-';
        }
    }
    if ((perms & S_ISUID) && ((perms & S_IXGRP) || (perms & S_IXOTH))) {
        new_perms[D2] = 's';
    }
    if ((perms & S_ISGID) && (perms & S_IXOTH)) {
        new_perms[D5] = 's';
    }
    if ((perms & S_ISVTX) && (perms & S_IWOTH) && (perms & S_IXOTH)) {
        new_perms[D8] = 't';
    }
    for (int i = 0; i < new_size; ++i) {
        *(buf + i) = new_perms[i];
    }
    *(buf + new_size) = '\0';
    return buf;
}

int main() {
    char buf[12];
    for (int i = 0; i < 07777; ++i) {
        printf("%s\n", perms_to_str(buf, 12, i));
    }
    return 0;
}