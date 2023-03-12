#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *file = argv[1];
    int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
        exit(1);
    }
    size_t rows = atoll(argv[2]);
    size_t cols = atoll(argv[3]);
    int size = sizeof(size) * rows * cols;
    if (ftruncate(fd, size) == -1) {
        exit(1);
    }
    void *ptr = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        exit(1);
    }
    int *arr = ptr;
    int i, j, k = 1, l = 0;
    while (k <= cols * rows) {
        i = l;
        j = l;
        for (j = l; j < cols - l; j++) {
            arr[i * cols + j] = k;
            k++;
            if (k > rows * cols) {
                break;
            }
        }
        if (k > rows * cols) {
            break;
        }
        j = cols - 1 - l;
        for (i = l + 1; i < rows - 1 - l; i++) {
            arr[i * cols + j] = k;
            k++;
            if (k > rows * cols) {
                break;
            }
        }
        if (cols == 1) {
            arr[(rows - 1) * cols + cols - 1] = rows * cols;
            break;
        }
        if (k > rows * cols) {
            break;
        }
        i = rows - 1 - l;
        for (j = cols - 1 - l; j > l; j--) {
            arr[i * cols + j] = k;
            k++;
            if (k > rows * cols) {
                break;
            }
        }
        if (k > rows * cols) {
            break;
        }
        j = l;
        for (i = rows - 1 - l; i > l; i--) {
            arr[i * cols + j] = k;
            k++;
            if (k > rows * cols) {
                break;
            }
        }
        if (k > rows * cols) {
            break;
        }
        l++;
    }
    munmap(ptr, size);
    close(fd);
    return 0;
}