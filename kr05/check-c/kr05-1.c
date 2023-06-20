#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *file = fopen("cjndfjn.c", "w");
    fprintf(file, "void foo() {\n%s;\n}\n", argv[1]);
    fclose(file);
    if (system("gcc -c cjndfjn.c > /dev/null 2>&1") == 0) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }
}
