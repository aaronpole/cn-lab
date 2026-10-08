#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

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
    int server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = {0};
    char filename[BUF], data[BUF];

    if (server < 0) { perror("socket"); return 1; }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    if (bind(server, (struct sockaddr *)&address, sizeof(address)) < 0 ||
        listen(server, 5) < 0) {
        perror("server setup");
        close(server);
        return 1;
    }
    puts("File server running...");

    for (;;) {
        int client = accept(server, NULL, NULL);
        ssize_t n;
        FILE *file;

        if (client < 0) { perror("accept"); continue; }
        n = recv(client, filename, sizeof(filename) - 1, 0);
        if (n <= 0) { close(client); continue; }
        filename[n] = '\0';
        filename[strcspn(filename, "\r\n")] = '\0';

        file = fopen(filename, "r");
        if (!file) {
            const char *error = "Error: File does not exist.";
            send_all(client, error, strlen(error));
        } else {
            int length = snprintf(data, sizeof(data), "Server PID: %ld\n\n",
                                  (long)getpid());
            send_all(client, data, (size_t)length);
            while ((n = (ssize_t)fread(data, 1, sizeof(data), file)) > 0)
                if (send_all(client, data, (size_t)n) < 0) break;
            fclose(file);
        }
        close(client);
    }
}
