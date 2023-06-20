#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    char *dir = getenv("XDG_RUNTIME_DIR");
    if (!dir) {
        dir = getenv("TMPDIR");
    }
    if (!dir) {
        dir = "/tmp";
    }
    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "%s/%d.py", dir, getpid());
    int fd = open(path, O_WRONLY | O_CREAT, 0700);
    dprintf(fd, "#!/usr/bin/python3\n");
    dprintf(fd, "print(%s", argv[1]);
    for (int i = 2; i < argc; ++i) {
        dprintf(fd, " * %s", argv[i]);
    }
    dprintf(fd, ")\n");
    dprintf(fd, "import os\n");
    dprintf(fd, "import sys\n");
    dprintf(fd, "os.remove('%s')", path);
    close(fd);
    execlp(path, path, NULL);
    return 0;
}
