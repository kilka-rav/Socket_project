#ifndef _my_server_h_
#define _my_server_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>



#define PATH "/tmp/mysock"
#define BUFSZ 256

void check(int arg) {
    if ( arg < 0 ) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }
}


#endif
