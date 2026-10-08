#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUF 1024

static int send_all(int socket, const char *data, size_t length)
{
    size_t sent = 0;
    while (sent < length) {
        ssize_t n = send(socket, data + sent, length - sent, 0);
        if (n <= 0) return -1;
        sent += (size_t)n;
    }
    return 0;
}

int main(void)
{
    int client = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server = {0};
    char filename[BUF], data[BUF];
    ssize_t n;

    if (client < 0) { perror("socket"); return 1; }
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) != 1) {
        fprintf(stderr, "Invalid server address.\n");
        close(client);
        return 1;
    }
    if (connect(client, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        close(client);
        return 1;
    }
    printf("Enter filename: ");
    if (!fgets(filename, sizeof(filename), stdin)) {
        close(client);
        return 1;
    }
    filename[strcspn(filename, "\n")] = '\0';
    if (send_all(client, filename, strlen(filename)) < 0) {
        perror("send");
        close(client);
        return 1;
    }
    puts("\nServer response:");
    while ((n = recv(client, data, sizeof(data), 0)) > 0)
        fwrite(data, 1, (size_t)n, stdout);
    if (n < 0) perror("recv");
    close(client);
    return n < 0;
}
