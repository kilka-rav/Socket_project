#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main() {
    uint32_t ip = htonl(INADDR_LOOPBACK);
    printf("%d\n", ip);
    return 0;
}
