#include "my_server.h"
int main() {
    struct sockaddr_in name = {0};
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    check(socket_fd);
    name.sin_family = AF_INET;
    name.sin_port = htons(23456);
    name.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ret = bind(socket_fd, (struct sockaddr*)&name, sizeof(name));
    check(ret);
    while (1) {
        int client_socket_fd;
        char buffer[BUFSZ] = {0};
        socklen_t addrlen = sizeof(name);
        ret = recvfrom(socket_fd, buffer, BUFSZ, 0, (struct sockaddr*)&name, &addrlen);
        check(ret);
        
        if ( strncmp(buffer, "print", sizeof("print") - 1) == 0 ) {
            printf("%s", buffer + sizeof("print"));
        }
        if ( strncmp(buffer, "q", sizeof("q") - 1) == 0 ) {
            break;
        }
        if ( strncmp(buffer, "ls", sizeof("ls") - 1) == 0 ) {
            if (fork() == 0) {
                execlp("ls", "ls", NULL);
                perror("execlp");
            }
        }
        if ( strncmp(buffer, "cd", sizeof("cd") - 1) == 0 ) {
                if ( chdir(buffer+3) == -1 ) {
                    perror("Error in direc");
                }
        }
    }
    close(socket_fd);
} 
