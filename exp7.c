#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5000
#define MAX 10
#define BUF 1024

int clients[MAX], n = 0;  // connected client sockets and count

void send_all(char *msg, int skip) {  // send to every client except sender
    for (int i = 0; i < n; i++)
        if (clients[i] != skip)
            send(clients[i], msg, strlen(msg), 0);
}

int main() {
    int s, c, r;                // server socket, accepted socket, receive length
    struct sockaddr_in a;        // server address
    char buf[BUF];              // message buffer

    s = socket(AF_INET, SOCK_STREAM, 0);   // create TCP socket
    a.sin_family = AF_INET;                // IPv4
    a.sin_addr.s_addr = INADDR_ANY;        // use local machine IP
    a.sin_port = htons(PORT);              // port number
    bind(s, (struct sockaddr *)&a, sizeof(a)); // bind socket to port
    listen(s, 5);                          // wait for clients

    printf("Chat Server Started...\n");

    while (1) {
        c = accept(s, NULL, NULL);         // accept one client
        clients[n++] = c;                  // save client socket

        while (1) {
            r = recv(c, buf, sizeof(buf), 0); // receive message
            if (r <= 0) break;                // client disconnected
            buf[r] = '\0';                    // end string
            printf("%s\n", buf);           // show message on server
            send_all(buf, c);                // send to all other clients
        }
    }
}
