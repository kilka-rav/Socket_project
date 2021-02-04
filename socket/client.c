#include "my_server.h"


int main() {
    struct sockaddr_un name = {0};
    int sk = socket(AF_UNIX, SOCK_STREAM, 0);
    check(sk);
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, PATH, sizeof(PATH));
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
