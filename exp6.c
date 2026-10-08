#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5000
#define BUF 1024

static const char *words[][2] = {
    {"btw", "by the way"}, {"idk", "I do not know"},
    {"atm", "at the moment"}, {"irl", "in real life"},
    {"lol", "laughing out loud"}, {"omg", "oh my god"},
    {"tbh", "to be honest"}, {"asap", "as soon as possible"},
    {"ty", "thank you"}, {"thx", "thanks"}
};

int main(void)
{
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in address = {0};
    char message[BUF], result[BUF * 8];

    if (s < 0) { perror("socket"); return 1; }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(s, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind"); close(s); return 1;
    }
    puts("UDP translation server running...");

    for (;;) {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        ssize_t n = recvfrom(s, message, sizeof(message) - 1, 0,
                             (struct sockaddr *)&client, &len);
        size_t used = 0;

        if (n < 0) { perror("recvfrom"); close(s); return 1; }
        message[n] = '\0';
        result[0] = '\0';
        for (char *word = strtok(message, " \t\r\n"); word;
             word = strtok(NULL, " \t\r\n")) {
            char tail[BUF];
            size_t end = strlen(word), i;
            const char *translation = word;
            while (end && strchr(".,!?", word[end - 1])) end--;
            strcpy(tail, word + end);
            word[end] = '\0';
            for (i = 0; i < sizeof(words) / sizeof(words[0]); i++)
                if (!strcasecmp(word, words[i][0])) {
                    translation = words[i][1];
                    break;
                }
            used += (size_t)snprintf(result + used, sizeof(result) - used,
                                     "%s%s%s", used ? " " : "",
                                     translation, tail);
        }
        if (sendto(s, result, strlen(result), 0,
                   (struct sockaddr *)&client, len) < 0)
            perror("sendto");
    }
}
