#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int create_connection(char *host, char *service) {
    struct addrinfo hints = {.ai_family = AF_INET, .ai_socktype = SOCK_STREAM};
    struct addrinfo *info = NULL;
    int error = getaddrinfo(host, service, &hints, &info);
    if (getaddrinfo(host, service, &hints, &info)) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(error));
        return -1;
    }
    int sock = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (sock == -1) {
        return -1;
    }
    if (connect(sock, info->ai_addr, info->ai_addrlen) == -1) {
        return -1;
    }
    freeaddrinfo(info);
    return sock;
}

int main(int argc, char **argv) {
    if (argc < 4) {
        return 1;
    }
    int k;
    signal(SIGPIPE, SIG_IGN);
    int sock = create_connection(argv[1], argv[2]);
    if (sock < 0) {
        return 0;
    }
    int sock2 = dup(sock);
    if (sock2 == -1) {
        return 0;
    }
    FILE *read = fdopen(sock, "r");
    if (!read) {
        return 0;
    }
    FILE *write = fdopen(sock2, "w");
    if (!write) {
        return 0;
    }
    int error = fprintf(write, "%s\n", argv[3]);
    fflush(write);
    if (error < 0) {
        return 0;
    }
    error = fscanf(read, "%d", &k);
    if (error < 0) {
        return 0;
    }
    for (int i = 0; i <= k; ++i) {
        error = fprintf(write, "%d\n", i);
        fflush(write);
        if (error < 0) {
            return 0;
        }
    }
    unsigned long long num;
    error = fscanf(read, "%llu", &num);
    if (error < 0) {
        return 0;
    }
    printf("%llu\n", num);
    fflush(stdout);
    fclose(read);
    fclose(write);
    return 0;
}
