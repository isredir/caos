#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { ARG_SIZE_MAX = 64 };

typedef struct Bytes {
    unsigned char bytes[ARG_SIZE_MAX];
} Bytes;

int main(int argc, char **argv) {
    void *lib = dlopen(argv[1], RTLD_LAZY);
    if (!lib) {
        return 1;
    }
    void *func = dlsym(lib, argv[2]);
    if (!func) {
        return 1;
    }
    char *signature = argv[3];
    Bytes args;
    int size = 0;
    for (int i = 4; i < argc; ++i) {
        if (signature[i - 3] == 'i') {
            int int_buf = atoi(argv[i]);
            memcpy(args.bytes + size, &int_buf, sizeof(int));
            size += sizeof(int);
        } else if (signature[i - 3] == 'd') {
            double double_buf = strtod(argv[i], NULL);
            memcpy(args.bytes + size, &double_buf, sizeof(double));
            size += sizeof(double);
        } else if (signature[i - 3] == 's') {
            memcpy(args.bytes + size, argv + i, sizeof(char *));
            size += sizeof(char *);
        }
    }
    if (signature[0] == 'i') {
        printf("%d\n", ((int (*)(Bytes))func)(args));
    } else if (signature[0] == 'd') {
        printf("%.10g\n", ((double (*)(Bytes))func)(args));
    } else if (signature[0] == 's') {
        printf("%s\n", ((char *(*)(Bytes))func)(args));
    } else {
        ((void (*)(Bytes))func)(args);
    }
    dlclose(lib);
}