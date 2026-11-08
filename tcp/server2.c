#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 12345

int main(){
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    server_fd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd,(struct sockaddr *)&address,sizeof(address));

    listen(server_fd,3);
    printf("Server Waiting");
    new_socket = accept(server_fd,(struct sockaddr *)&address,(socklen_t *)&addrlen);
    int n = recv(new_socket,buffer,sizeof(buffer)-1,0);

    if (n>0){
        buffer[n] = '\0';
        printf("Server receives : %s\n",buffer);
        send(new_socket,"hello from server",18,0);
    }
    close(new_socket);
    close(server_fd);
    return 0;

}