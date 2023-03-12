#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum { LEN_MAX = 63, D32 = 32, D127 = 127 };

int main(int argc, char **argv) {
    if (argc > 2) {
        fprintf(stderr, "%s\n", "Error! To many args!");
        return 1;
    }
    FILE *file;
    if (argc == 1) {
        file = stdin;
    } else if (argc == 2) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            fprintf(stderr, "%s\n", "Error! Cannot open the file!");
            return 1;
        }
    } else {
        fprintf(stderr, "%s\n", "Error! Wrong number of args!");
        return 1;
    }
    char word[LEN_MAX + 1];
    int pos = 0;
    int first_int = 0;
    int max_int = 0;
    int first_double = 0;
    double min_double = 0;
    int end_of_while = 0;
    while (1) {
        if (end_of_while) {
            break;
        }
        int c = getc_unlocked(file);
        if (c == EOF) {
            c = ' ';
            end_of_while = 1;
        }
        if (ferror(file)) {
            fclose(file);
            fprintf(stderr, "%s\n", "Error! Reading from file failed!");
            return 1;
        }
        if (c == ' ' || c == '\r' || c == '\t' || c == '\n') {
            word[pos] = '\0';
            // printf("word %s\n", word);
            int ipos = pos;
            pos = 0;
            int is_number = 1;
            if (word[0] == '\0') {
                continue;
            }
            if (word[0] == '+' || word[0] == '-') {
                for (int i = 1; i < ipos; ++i) {
                    if (!isdigit(word[i])) {
                        is_number = 0;
                        break;
                    }
                }
            }
            if (word[0] != '+' && word[0] != '-') {
                for (int i = 0; i < ipos; ++i) {
                    if (!isdigit(word[i])) {
                        is_number = 0;
                        break;
                    }
                }
            }
            if (is_number) {
                errno = 0;
                long x = strtol(word, NULL, 10);
                if (errno != 0 || x != (int)x) {
                    continue;
                }
                if (first_int == 0) {
                    max_int = (int)x;
                    first_int = 1;
                } else if (x > max_int) {
                    max_int = (int)x;
                }
            } else {
                errno = 0;
                char *start_ptr = &word[0];
                char **end_ptr = &start_ptr;
                double x = strtod(word, end_ptr);
                if (errno != 0 || **end_ptr != '\0') {
                    continue;
                }
                if (first_double == 0) {
                    min_double = x;
                    first_double = 1;
                } else if (isnan(x) || (!isnan(x) && x < min_double)) {
                    min_double = x;
                }
            }
        } else if (c < D32 || c == D127) {
            fclose(file);
            fprintf(stderr, "%s\n", "Error! Forbidden symbol!");
            return 1;
        } else {
            word[pos] = (char)c;
            ++pos;
            if (pos == LEN_MAX) {
                fclose(file);
                fprintf(stderr, "%s\n", "Error! Too long word!");
                return 1;
            }
        }
    }
    if (first_int == 0 || first_double == 0) {
        fclose(file);
        fprintf(stderr, "%s\n", "Error! Int or double not found!");
        return 1;
    }
    printf("%d %.10g\n", max_int, min_double);
    fclose(file);
    return 0;
}
