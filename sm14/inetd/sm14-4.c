#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

enum { D5 = 5, BASE = 10 };

int create_server(struct sockaddr_in6 info) {
    int sock = socket(PF_INET6, SOCK_STREAM, 0);
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

void handler(int s) {
    _exit(0);
}

void child_handler(int s) {
}

int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }
    unsigned short port = htons(strtol(argv[1], NULL, BASE));
    struct sockaddr_in6 info = {
        .sin6_family = AF_INET6, .sin6_addr = in6addr_any, .sin6_port = port};
    int sock = create_server(info);
    if (sock < 0) {
        return 0;
    }
    struct sigaction sa = {.sa_handler = handler, .sa_flags = SA_RESTART};
    sigaction(SIGTERM, &sa, NULL);
    struct sigaction sa_children = {.sa_handler = child_handler,
                                    .sa_flags = SA_RESTART | SA_NOCLDWAIT};
    sigaction(SIGCHLD, &sa_children, NULL);
    while (1) {
        socklen_t size = sizeof(info);
        int conn = accept(sock, (struct sockaddr *)&info, &size);
        if (conn < 0) {
            close(sock);
            return 1;
        }
        int pid = fork();
        if (!pid) {
            dup2(conn, STDIN_FILENO);
            dup2(conn, STDOUT_FILENO);
            close(conn);
            close(sock);
            execvp(argv[2], argv + 2);
            _exit(1);
        }
        close(conn);
    }
    close(sock);
}
