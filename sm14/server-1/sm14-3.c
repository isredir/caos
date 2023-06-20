#include <inttypes.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

enum { D5 = 5, BASE = 10 };

int create_server(struct sockaddr_in info) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        return -1;
    }
    int num = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &num, sizeof(num));
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &num, sizeof(num));
    if (bind(sock, (struct sockaddr *)&info, sizeof(info)) < 0) {
        return -1;
    }
    if (listen(sock, D5) < 0) {
        return -1;
    }
    return sock;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    unsigned short port = htons(strtol(argv[1], NULL, BASE));
    struct sockaddr_in info = {
        .sin_family = AF_INET, .sin_addr.s_addr = INADDR_ANY, .sin_port = port};
    int sock = create_server(info);
    if (sock < 0) {
        return 0;
    }
    int res = 0;
    while (1) {
        socklen_t size = sizeof(info);
        int sock2 = accept(sock, (struct sockaddr *)&info, &size);
        if (sock2 < 0) {
            return 0;
        }
        int val = 1;
        if (read(sock2, &val, sizeof(val)) < 0) {
            return 0;
        }
        close(sock2);
        res += ntohl(val);
        if (!val) {
            break;
        }
    }
    printf("%" PRId32 "\n", res);
    fflush(stdout);

    close(sock);
    return 0;
}
