#include <dirent.h>
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

enum { MAX_HEIGHT = 4, BASE = 10 };

void dfs(char *cur_dir, int64_t max_size, char *root, int h) {
    if (h > MAX_HEIGHT) {
        return;
    }
    DIR *d;
    struct dirent *ent;
    d = opendir(cur_dir);
    if (!d) {
        return;
    }
    while ((ent = readdir(d))) {
        if (strlen(ent->d_name) >= 1 && ent->d_name[0] == '.' &&
            ent->d_name[1] == '\0') {
            continue;
        }
        if (strlen(ent->d_name) >= 2 && ent->d_name[0] == '.' &&
            ent->d_name[1] == '.' && ent->d_name[2] == '\0') {
            continue;
        }
        char abs_path[PATH_MAX];
        snprintf(abs_path, PATH_MAX, "%s/%s", cur_dir, ent->d_name);
        struct stat buf;
        errno = 0;
        if (lstat(abs_path, &buf) == 0 && errno == 0) {
            if (S_ISREG(buf.st_mode)) {
                if (access(abs_path, R_OK) == 0 && buf.st_size <= max_size) {
                    char rel_path[PATH_MAX];
                    snprintf(rel_path, PATH_MAX, "%s",
                             abs_path + strlen(root) + 1);
                    printf("%s\n", rel_path);
                }
            } else if (S_ISDIR(buf.st_mode)) {
                dfs(abs_path, max_size, root, h + 1);
            }
        }
    }
    closedir(d);
}

int main(int argc, char **argv) {
    char new_dir[PATH_MAX + 1];
    if (argc >= 2) {
        const char *dir = argv[1];
        int64_t z = strtol(argv[2], NULL, BASE);
        if (strlen(dir) >= 1 && dir[0] == '.' && dir[1] != '.') {
            snprintf(new_dir, PATH_MAX, ".%s", dir);
            dfs(new_dir, z, new_dir, 1);
            return 0;
        }
        if (strlen(dir) >= 2 && dir[0] == '.' && dir[1] == '.') {
            *new_dir = '.';
            *(new_dir + 1) = '.';
            *(new_dir + 2) = '/';
            for (int i = 0; i < strlen(dir); ++i) {
                *(new_dir + i + 3) = *(dir + i);
            }
            dfs(new_dir, z, new_dir, 1);
            return 0;
        }
        snprintf(new_dir, PATH_MAX, "%s", dir);
        dfs(new_dir, z, new_dir, 1);
        return 0;
    } else {
        return 1;
    }
}
