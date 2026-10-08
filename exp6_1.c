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
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server = {0};
    char message[BUF], result[BUF * 8];
    ssize_t n;

    if (s < 0) { perror("socket"); return 1; }
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    printf("Enter a message: ");
    if (!fgets(message, sizeof(message), stdin)) { close(s); return 1; }
    message[strcspn(message, "\n")] = '\0';
    if (sendto(s, message, strlen(message), 0,
               (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("sendto"); close(s); return 1;
    }
    n = recvfrom(s, result, sizeof(result) - 1, 0, NULL, NULL);
    if (n < 0) { perror("recvfrom"); close(s); return 1; }
    result[n] = '\0';
    printf("Translated message: %s\n", result);
    close(s);
    return 0;
}
