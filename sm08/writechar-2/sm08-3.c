enum { BUF_SIZE = 4096 };

struct FileWriteState {
    int fd;
    unsigned char *buf;
    int bufsize;
    int cur_bufsize;
};

static unsigned char buf[BUF_SIZE];

static struct FileWriteState x = {
    1,
    buf,
    BUF_SIZE,
    0,
};

struct FileWriteState *stout = &x;

void flush(struct FileWriteState *out) {
    asm volatile("mov $4, %%eax \n\t"
                 "int $0x80 \n\t"
                 :
                 : "b"(out->fd), "c"(out->buf), "d"(out->cur_bufsize)
                 : "eax");
}

void writechar(int c, struct FileWriteState *out) {
    out->buf[out->cur_bufsize] = c;
    ++out->cur_bufsize;
    if (out->cur_bufsize == out->bufsize) {
        flush(out);
        out->cur_bufsize = 0;
    }
}
