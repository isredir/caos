#include "read_file.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum { BUF_SIZE = 4096 };

struct FileContent error_result(struct FileContent res) {
    free(res.data);
    res.data = NULL;
    res.size = -1;
    return res;
}

struct FileContent read_file(int fd) {
    struct FileContent res;
    res.size = 0;
    ssize_t size = 1;
    res.data = calloc(size, sizeof(*res.data));
    if (!res.data) {
        return error_result(res);
    }
    while (1) {
        char buf[BUF_SIZE];
        ssize_t x = read(fd, buf, BUF_SIZE);
        if (x < 0) {
            return error_result(res);
        } else if (x > 0) {
            if (res.size + x >= size) {
                char *new_data =
                    realloc(res.data, (size + BUF_SIZE) * sizeof(*new_data));
                if (!new_data) {
                    return error_result(res);
                }
                size += BUF_SIZE;
                res.data = new_data;
            }
            for (ssize_t i = res.size; i < res.size + x; ++i) {
                res.data[i] = buf[i - res.size];
            }
            res.size += x;
        }
        if (x == 0) {
            break;
        }
    }
    res.data[res.size] = '\0';
    return res;
}
