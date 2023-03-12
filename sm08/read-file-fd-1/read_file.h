#include <sys/types.h>

struct FileContent
{
    ssize_t size;
    char *data;
};

struct FileContent read_file(int fd);
