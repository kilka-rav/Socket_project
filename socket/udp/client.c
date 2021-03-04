#include "my_server.h"

void checking(int arg) {
    printf("%d\n", arg);
    if ( arg != 2 ) {
        print_error("ERROR IN ENTER\n");
        exit(2);
    }
}


int main(int argc, char** argv) {
    checking(argc);
    struct sockaddr_in name = {0};
    char buffer[BUFSZ] = {0};
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    char path[256];
    check(socket_fd);
    name.sin_family = AF_INET;
    name.sin_port = htons(23456);
    name.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(socket_fd, (struct sockaddr*)&name, sizeof(name));
    check(ret);
    while(1) {
        ret = read(1, buffer, BUFSZ);
        check(ret);
        if ( strncmp(buffer, "cd", sizeof("cd") - 1) == 0 ) {
            buffer[strlen(buffer) - 1] = 0;
            strcpy(path, buffer);
            continue;
        }
        ret = sendto(socket_fd, buffer, BUFSZ, 0, (struct sockaddr*)&name, sizeof(name));
        check(ret);
        if ( strncmp(buffer, "q", 1) == 0 ) {
            break;
        }
    }
    return 0;
} 
