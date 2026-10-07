#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUF 128

int main() {
    int s;                    // client socket
    struct sockaddr_in a;     // server address
    char msg[] = "TIME";     // request to send
    char r[BUF];              // received time

    s = socket(AF_INET, SOCK_DGRAM, 0);  // create UDP socket
    a.sin_family = AF_INET;               // IPv4
    a.sin_port = htons(PORT);             // server port
    a.sin_addr.s_addr = inet_addr("127.0.0.1"); // local server IP

    sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&a, sizeof(a)); // send request
    recvfrom(s, r, sizeof(r), 0, NULL, NULL); // receive server response

    printf("Server Time: %s\n", r); // print time
    close(s); // close socket
}
