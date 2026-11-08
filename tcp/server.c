#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int main(){
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    // Make Socket.
    server_fd = socket(AF_INET,SOCK_STREAM,0);

    // Configure server address.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind Address
    bind(server_fd,(struct sockaddr *)&address,sizeof(address));

    // Listen
    listen(server_fd,3);
    printf("Server Waiting...\n");

    // Accept Client
    new_socket = accept(server_fd,(struct sockaddr *)&address,(socklen_t *)&addrlen);

    // Receive Message
    int n = recv(new_socket,buffer,sizeof(buffer)-1,0);

    if (n > 0){
        buffer[n] = '\0';
        printf("Client says : %s\n",buffer);

        // send response.
        send(new_socket,"Hello from server",18,0);
    }
    close(new_socket);
    close(server_fd);
    return 0;
}