#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <termios.h>
#include <poll.h>
#include <dlfcn.h>

#define PATH "/tmp/mysock"
#define BUFSZ 256
#define port 23456
#define MAX_CLIENTS_COUNT 10
#define TIMEOUT 100
#define PRINT "print"
#define EXIT "exit"
#define CD "cd"
#define LS "ls"
#define FINDALL "findall"
#define SHELL "shell"
#define UDP "udp"
#define TCP "tcp"

struct client_info {
    int pid;
    int client_id;
    int pipes_from_main[2];
    int pipes_to_main[2];
    int shell; //flag if shell activated
    int client_sk; //client sk for tcp
}; typedef struct client_info client_info;

void clear_buf(char* buffer, int size);

void create_sock_name(struct sockaddr_in* name, struct in_addr addr);

int convert_address(const char* ip, struct in_addr* addr);

void bind_socket (int sk, struct sockaddr_in name);

void send_data(int sk, struct sockaddr_in* name, 
               char* data, int fd, int client_sk,
               void (*send_buf)(int sk, struct sockaddr_in* name, char* data, int client_sk));

void receive_data(int sk, struct sockaddr_in* name, 
                  char* buffer, int client_sk,
                  int (*receive_buf)(int sk, struct sockaddr_in* name, char* buffer, int client_sk));

int starts_with(char* str, char* substr);

FILE* open_log_file();

void start_daemon();

void* choose_protocol(char* type, FILE* logfile);
