#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char **argv) {
    void *lib = dlopen("libm.so.6", RTLD_LAZY);
    if (!lib) {
        return 1;
    }
    double (*func)(double) = dlsym(lib, argv[1]);
    if (!func) {
        return 1;
    }
    double val;
    while (scanf("%lf", &val) == 1) {
        printf("%.10g\n", (*func)(val));
    }
    dlclose(lib);
}