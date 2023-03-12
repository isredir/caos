void normalize_path(char *buf) {
    char *buf_copy = buf;
    int slash = 0;
    while (*buf) {
        if (slash == 1 && *buf == '/') {
            ++buf;
        } else {
            if (*buf == '/') {
                slash = 1;
            } else {
                slash = 0;
            }
            *buf_copy = *buf;
            ++buf_copy;
            ++buf;
        }
    }
    *buf_copy = '\0';
}
