#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        exit(1);
    }
    struct servent *service_info = getservbyname(argv[1], "tcp");
    if (service_info == NULL) {
        printf("Non serviam.\n");
        exit(0);
    }
    printf("%d\n", ntohs(service_info->s_port));
    return 0;
}
