#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5000
#define BUF 1024

int main(void)
{
    const char *short_forms[] = {"btw", "idk", "atm", "irl", "lol", "omg",
                                 "tbh", "asap", "ty", "thx"};
    const char *meanings[] = {"by the way", "I do not know", "at the moment",
                              "in real life", "laughing out loud", "oh my god",
                              "to be honest", "as soon as possible",
                              "thank you", "thanks"};
    int server = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in address = {0};
    char message[BUF], result[BUF * 8];

    if (server < 0) {
        perror("socket");
        return 1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind");
        close(server);
        return 1;
    }

    puts("UDP translation server running...");
    for (;;) {
        struct sockaddr_in client;
        socklen_t length = sizeof(client);
        ssize_t n = recvfrom(server, message, sizeof(message) - 1, 0,
                             (struct sockaddr *)&client, &length);
        char *word;
        size_t used = 0;

        if (n < 0) {
            perror("recvfrom");
            close(server);
            return 1;
        }
        message[n] = '\0';
        result[0] = '\0';
        for (word = strtok(message, " \t\r\n"); word; word = strtok(NULL, " \t\r\n")) {
            size_t i;
            size_t end = strlen(word);
            char punctuation[BUF];
            const char *translated = word;
            while (end && strchr(".,!?", word[end - 1]))
                end--;
            strcpy(punctuation, word + end);
            word[end] = '\0';
            for (i = 0; i < sizeof(short_forms) / sizeof(short_forms[0]); i++)
                if (strcasecmp(word, short_forms[i]) == 0) {
                    translated = meanings[i];
                    break;
                }
            used += (size_t)snprintf(result + used, sizeof(result) - used,
                                     "%s%s%s", used ? " " : "", translated,
                                     punctuation);
            word[end] = '\0';
        }
        if (sendto(server, result, strlen(result), 0,
                   (struct sockaddr *)&client, length) < 0)
            perror("sendto");
    }
}
