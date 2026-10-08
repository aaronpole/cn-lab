#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000
#define BUF 1024

int main(void)
{
    int client = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server = {0};
    char message[BUF], result[BUF * 8];
    ssize_t n;

    if (client < 0) {
        perror("socket");
        return 1;
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) != 1) {
        fprintf(stderr, "Invalid server address.\n");
        close(client);
        return 1;
    }

    printf("Enter a message: ");
    if (!fgets(message, sizeof(message), stdin)) {
        close(client);
        return 1;
    }
    message[strcspn(message, "\n")] = '\0';
    if (sendto(client, message, strlen(message), 0,
               (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("sendto");
        close(client);
        return 1;
    }
    n = recvfrom(client, result, sizeof(result) - 1, 0, NULL, NULL);
    if (n < 0) {
        perror("recvfrom");
        close(client);
        return 1;
    }
    result[n] = '\0';
    printf("Translated message: %s\n", result);
    close(client);
    return 0;
}
