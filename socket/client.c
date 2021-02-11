#include "my_server.h"


int main(int argc, char** argv) {
    if ( argc != 2 ) {
        fprintf(stderr, "ERROR IN INPUT\n");
        exit(1);
    }
    //char* ip = argv[1];
    //check(ip);
    printf("%d\n", htonl(INADDR_LOOPBACK));
    /*
    if ( ip != htonl(INADDR_LOOPBACK) ) {
        printf("bad addres\n");
        exit(1);
    }
    */
    struct sockaddr_in name = {0};
    int sk = socket(AF_INET, SOCK_STREAM, 0);
    check(sk);
    name.sin_family = AF_INET;
    name.sin_port = htons(23456);
    int ipy = inet_aton(argv[1], &(name.sin_addr));
    //name.sin_addr.s_addr = ipy;
    //strncpy(name.sin_family, PATH, sizeof(PATH));
    int ret = connect(sk, (struct sockaddr*) &name, sizeof(name));
    check(ret);
    char* flag = (char*) malloc(BUFSZ);
    printf("ENTER q, if you want to exit\n");
    scanf("%s", flag);
    if ( strcmp(flag, "q") == 0 ) {
        ret = write(sk, "q", 1);
        check(ret);
        close(sk);
        free(flag);
        return 1;
    }
    else {
        ret = write(sk, flag, strlen(flag));
        check(ret);
        free(flag);
        close(sk);
    }
    return 0;
}
