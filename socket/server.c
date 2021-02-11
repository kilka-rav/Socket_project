#include "my_server.h"


int main() {
    unlink(PATH);
    struct sockaddr_in my_socket = {0};
    int sk = socket(AF_INET, SOCK_STREAM, 0);
    check(sk);
    my_socket.sin_family = AF_INET;
    my_socket.sin_port = htons(23456);
    my_socket.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    //strncpy(my_socket.sun_path, PATH, sizeof(PATH));
    int ret = bind(sk, (struct sockaddr*) &(my_socket), sizeof(my_socket));
    if ( ret < 0 ) {
        close(sk);
    }
    check(ret);
    ret = listen(sk, 10);
    if ( ret < 0 ) {
        close(sk);
    }
    check(ret);
    int i = 0;
    while(1) {
        int client;
        char* buf = (char*) malloc(BUFSZ);
        client = accept(sk, NULL, NULL);
        check(client);
        ret = read(client, buf, BUFSZ);
        check(ret);
        if ( strcmp(buf, "q") != 0 ) {
            printf("%s\n", buf);
        }
        else {
            close(sk);
            free(buf);
            printf("EXIT\n");
            return 1;
        }
        free(buf);
    }
    return 0;
}
