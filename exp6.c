#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5000

void translate(char *msg)
{
    char *words[] = {"btw", "idk", "atm", "irl", "lol",
                     "omg", "tbh", "asap", "ty", "thx"};

    char *meaning[] = {"by the way", "I do not know", "at the moment",
                       "in real life", "laughing out loud", "oh my god",
                       "to be honest", "as soon as possible",
                       "thank you", "thanks"};

    char result[2048] = "";
    char *word = strtok(msg, " \n");
    int i;

    while (word != NULL)
    {
        for (i = 0; i < 10; i++)
        {
            if (strcmp(word, words[i]) == 0)
            {
                word = meaning[i];
                break;
            }
        }

        strcat(result, word);
        strcat(result, " ");

        word = strtok(NULL, " \n");
    }

    strcpy(msg, result);
}

int main()
{
    int s;
    char msg[1024];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(s, (struct sockaddr *)&server, sizeof(server));

    printf("Server running...\n");

    while (1)
    {
        recvfrom(s, msg, sizeof(msg), 0,
                 (struct sockaddr *)&client, &len);

        translate(msg);

        sendto(s, msg, strlen(msg), 0,
               (struct sockaddr *)&client, len);
    }
}