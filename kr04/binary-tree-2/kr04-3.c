#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

typedef struct Node {
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
} Node;

void dfs(int fd, size_t v) {
    Node node = {0, 0, 0};
    if (lseek(fd, v * sizeof(node), 0) < 0) {
        exit(1);
    }
    int p = 1;
    unsigned char buf[3 * sizeof(p)];
    if (read(fd, buf, sizeof(buf)) == 0) {
        exit(1);
    }
    for (int i = 0; i < sizeof(p); ++i) {
        node.key += p * buf[i];
        node.left_idx += p * buf[i + sizeof(p)];
        node.right_idx += p * buf[i + 2 * sizeof(p)];
        p *= (1 << (2 * sizeof(p)));
    }
    if (node.right_idx != 0) {
        dfs(fd, node.right_idx);
    }
    printf("%d ", node.key);
    if (node.left_idx != 0) {
        dfs(fd, node.left_idx);
    }
}

int main(int argc, char **argv) {
    char *file = argv[1];
    int fd = open(file, O_RDONLY);
    struct stat st;
    if (fstat(fd, &st) != 0) {
        return -1;
    }
    mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
    dfs(fd, 0);
    printf("\n");
    return 0;
}