#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 12345

int main(){
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    sock = socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock,(struct sockaddr *)&server_addr,sizeof(server_addr));
    send(sock,"Hello from client",18,0);

    int n = recv(sock,buffer,sizeof(buffer)-1,0);

    if (n>0){
        buffer[n] = '\0';
        printf("Server says : %s\n",buffer);
    }
    close(sock);
    return 0;
}