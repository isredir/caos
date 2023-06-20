#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

enum { BUF_SIZE = 65535 };

int main(int argc, char **argv) {
    struct addrinfo hints = {.ai_family = AF_UNSPEC, .ai_socktype = SOCK_DGRAM};
    struct addrinfo *info;
    if (getaddrinfo(argv[1], NULL, &hints, &info) != 0) {
        exit(1);
    }
    int sock;
    if ((sock = socket(info->ai_family, info->ai_socktype, info->ai_protocol)) <
        0) {
        exit(1);
    }
    char buf[BUF_SIZE];
    int port = atoi(argv[2]);
    while (1) {
        ((struct sockaddr_in *)info->ai_addr)->sin_port = htons(port);
        char *line = ".";
        if (sendto(sock, line, 1, 0, info->ai_addr, info->ai_addrlen) < 0) {
            exit(1);
        }
        socklen_t len = info->ai_addrlen;
        ssize_t x = recvfrom(sock, buf, BUF_SIZE, 0, info->ai_addr, &len);
        if (x < 0) {
            exit(0);
        };
        buf[x] = '\0';
        fprintf(stdout, "%s\n", buf);
        if ('0' > buf[0] || buf[0] > '9') {
            freeaddrinfo(info);
            break;
        }
        port = atoi(buf);
    }
}
