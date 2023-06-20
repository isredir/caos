#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

enum { MAX_LEN = 1000 };

int main() {
    char host[MAX_LEN];
    char service[MAX_LEN];
    while (1) {
        if (scanf("%s %s", host, service) == EOF) {
            break;
        }
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        struct addrinfo *info = NULL;
        int error = getaddrinfo(host, service, &hints, &info);
        if (error != 0) {
            printf("%s\n", gai_strerror(error));
            fflush(stdout);
        } else {
            struct sockaddr_in *min_addr = NULL;
            unsigned int min_port = 0;
            int first = 0;
            for (struct addrinfo *cur_addr = info; cur_addr != NULL;
                 cur_addr = cur_addr->ai_next) {
                struct sockaddr_in *tmp_addr =
                    (struct sockaddr_in *)cur_addr->ai_addr;
                if (!first || ntohl(tmp_addr->sin_addr.s_addr) < min_port) {
                    first = 1;
                    min_port = ntohl(tmp_addr->sin_addr.s_addr);
                    min_addr = tmp_addr;
                }
            }
            printf("%s:%hu\n", inet_ntoa(min_addr->sin_addr),
                   ntohs(min_addr->sin_port));
            fflush(stdout);
            freeaddrinfo(info);
        }
    }
    return 0;
}
