#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>

void login(int sock);

void *connection_handler(void *);

int main(int argc , char *argv[])
{

    int server_socket, client_socket, client_len, *new_socket;
    struct sockaddr_in server_address, client_address;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(server_socket==1){
        perror("[-] Could not create socket\n");
    }
    puts("Socket created");
    // address of socket defined
    server_address.sin_family = AF_INET;    
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    int bind_status = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (bind_status < 0)
    {
        perror("[-] Binding failed: \n");
        return 1;
    }

    printf("[+] Binding established\n");

    // enabled listening for 5 clients
    listen(server_socket, 5);

    puts("Waiting for connection...");
    
    
    client_len = sizeof(client_address);
    while((client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t *)&client_len))){
        puts("Connection accepted\n");

        pthread_t sniffer_thread;
        new_socket = malloc(1);
        *new_socket = client_socket;

        if(pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_socket)<0){
            perror("[-] Could not create thread\n");
            return 1;
        }

        puts("Handler assigned");
    }

    if(client_socket<0){
        perror("[-] Accept failed\n");
        return 1;
    }

    // login(client_socket);
    // close(client_socket);
    // close(server_socket);

    return 0;
}

void login(int sock)
{
    
}

void *connection_handler(void *server_socket){
    int socket = *(int*)server_socket;
    int read_size;
    char *message, client_message[2000];

    message = "You are connected to the server\n";
    write(socket, message, strlen(message));


    while((read_size = recv(socket, client_message, 2000, 0))>0){
        write(socket, client_message, strlen(client_message));
    }
    if(read_size==0){
        puts("[+] Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1){
        perror("[-] Receive failed\n");
    }
    free(server_socket);
    return 0;
}