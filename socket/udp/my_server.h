#ifndef _myserver_h
#define _myserver_h

#include <stdio.h>
#include <sys/un.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define PATH "/tmp/mysock"
#define BUFSZ 256
#define print_error(string) fprintf(stderr, "%s\n", string)

void check(int arg) {
    if (arg < 0 ) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }
}


#endif 

