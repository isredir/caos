#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *file = argv[1];
    int fd = open(file, O_RDONLY);
    if (fd < 1) {
        exit(1);
    }
    struct stat buf;
    if (fstat(fd, &buf) == -1) {
        exit(1);
    }
    void *ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (ptr == MAP_FAILED) {
        exit(1);
    }
    const double *arr = ptr;
    double sum = 0.0;
    size_t size = buf.st_size / sizeof(*arr);
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    if (size == 0) {
        printf("%a\n", 0.0);
    } else {
        printf("%a\n", sum / ((double)size));
    }
    munmap(ptr, buf.st_size);
    close(fd);
    return 0;
}
