#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUF 1024

int s;  // client socket

void *recv_msg(void *p) {  // thread to receive incoming messages
    char b[BUF];
    while (1) {
        int r = recv(s, b, sizeof(b), 0); // receive from server
        if (r <= 0) return NULL;           // server closed
        b[r] = '\0';                       // end string
        printf("\n%s\n", b);            // print message
    }
}

int main() {
    struct sockaddr_in a;  // server address
    pthread_t t;           // receiving thread
    char name[20], msg[BUF], sendbuf[BUF];

    s = socket(AF_INET, SOCK_STREAM, 0); // create TCP socket
    a.sin_family = AF_INET;             // IPv4
    a.sin_port = htons(PORT);           // server port
    a.sin_addr.s_addr = inet_addr("127.0.0.1"); // server IP
    connect(s, (struct sockaddr *)&a, sizeof(a)); // connect to server

    printf("Enter your name: ");
    scanf("%s", name); // read client name

    pthread_create(&t, NULL, recv_msg, NULL); // start receive thread

    while (1) {
        scanf("%s", msg); // read message from keyboard
        if (strcmp(msg, "exit") == 0) break; // stop chat
        sprintf(sendbuf, "%s: %s", name, msg); // add name to message
        send(s, sendbuf, strlen(sendbuf), 0);  // send to server
    }

    close(s); // close socket
}
