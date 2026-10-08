#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000

int main()
{
    int s;
    char msg[1024];
    struct sockaddr_in server;

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);

    sendto(s, msg, strlen(msg), 0,
           (struct sockaddr *)&server, sizeof(server));

    recvfrom(s, msg, sizeof(msg), 0, NULL, NULL);

    printf("Translated: %s", msg);

    close(s);
}