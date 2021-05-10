#include "lib.h"

//get exclusive id for recognizing in server
int get_id()
{
    return getpid(); //for local
    //return get_my_ip() - for internet 
}

int get_str(char* buffer, struct sockaddr_in* name)
{
    char tmp_buf[BUFSZ] = {0};
    char* ret_s = fgets(tmp_buf, BUFSZ, stdin);
    if (ret_s == NULL)
        perror("fgets in get_str");
    tmp_buf[strlen(tmp_buf) - 1] = '\0';
    int ret = sprintf(buffer, "%d %s", get_id(), tmp_buf);
    if (ret < 0)
        perror("sprintf in get_str");
    
    if (starts_with(tmp_buf, FINDALL)) //if command findall
        return -1;
    else if (starts_with(tmp_buf, EXIT))
        return 0;
    else if (starts_with(tmp_buf, SHELL))
        return 2;
    else
        return 1;
    
}

int main(int argc, char** argv) {

    assert(argc > 2);
    struct sockaddr_in name = {0};
    struct in_addr addr = {0};
    int sk, ret, flag = 1, shell = 0;
    char buffer[BUFSZ] = {0};
    FILE* logfile = stdout;

    void* sl = choose_protocol(argv[1], NULL);
    int (*create_socket)();
    int (*receive_buf)(int sk, struct sockaddr_in* name, char* buffer, int client_sk);
    void (*send_buf)(int sk, struct sockaddr_in* name, char* data, int client_sk);
    void (*connect_socket) (int sk, struct sockaddr_in name);
    *(void **) (&create_socket) = dlsym(sl, "create_socket");
    *(void **) (&receive_buf) = dlsym(sl, "receive_buf");
    *(void **) (&send_buf) = dlsym(sl, "send_buf");
    *(void **) (&connect_socket) = dlsym(sl, "connect_socket");
    
    convert_address(argv[2], &addr);
    create_sock_name(&name, addr);
    sk = create_socket();
    connect_socket(sk, name); 

    ret = setsockopt(sk, SOL_SOCKET, SO_BROADCAST | SO_REUSEADDR | SO_REUSEPORT, &(int){1}, sizeof(int));
    if (ret < 0)
        perror("setsockipt can't change mode\n");

    while (flag)
    {
        create_sock_name(&name, addr);
        printf("Enter command: ");
        flag = get_str(buffer, &name);
        
        if (flag >= 0) //usual command
        {
            send_buf(sk, &name, buffer, sk);

            if ((shell == 1) && (flag == 0)) //if exit in shell
            {
                flag = 1;
                shell = 0;
            }
            else if (flag == 2)  //if command shell
                shell = 1; 

            if ((flag == 1) || ((flag == 0) && (shell == 1)) || (flag == 2)) //if classic command or exit in shell or "shell" command
            {
                name.sin_addr.s_addr = htonl(INADDR_ANY);
                name.sin_port = 0;
                bind_socket(sk, name);  //bind to rec message back
                printf("Enter command:\n");
                receive_data(sk, &name, buffer, sk, receive_buf);
            }
        }
        else if (flag == -1) //findall command
        {
            name.sin_addr.s_addr = htonl(INADDR_BROADCAST);   //make broadcast
            send_buf(sk, &name, buffer, sk);

            name.sin_addr.s_addr = htonl(INADDR_ANY);
            name.sin_port = 0;
            bind_socket(sk, name);  //bind to rec message back

            receive_buf(sk, &name, buffer, sk);
            printf("find server, buf: (%s), ip: %s\n", buffer, inet_ntoa(name.sin_addr));
        }
    }

    close(sk);
}
