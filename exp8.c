#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUF 128

int main() {
    int s;                       // UDP socket
    struct sockaddr_in a, c;     // server and client addresses
    socklen_t l = sizeof(c);     // client address length
    char msg[BUF];               // message buffer
    time_t t;                    // current time
    struct tm *tm;               // time structure

    s = socket(AF_INET, SOCK_DGRAM, 0); // create UDP socket
    a.sin_family = AF_INET;             // IPv4
    a.sin_addr.s_addr = INADDR_ANY;     // accept all local requests
    a.sin_port = htons(PORT);           // port number
    bind(s, (struct sockaddr *)&a, sizeof(a)); // bind to port

    printf("Time Server Started...\n");

    while (1) {
        recvfrom(s, msg, sizeof(msg), 0, (struct sockaddr *)&c, &l); // receive request
        time(&t);                         // get current time
        tm = localtime(&t);               // convert to date/time
        strftime(msg, sizeof(msg), "%Y-%m-%d %H:%M:%S", tm); // format time string
        sendto(s, msg, strlen(msg), 0, (struct sockaddr *)&c, l); // send time back
    }
}
