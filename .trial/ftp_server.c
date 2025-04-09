#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER 1024

int main()
{
    int clientfd, serverfd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrlen = sizeof(clientaddr);
    char buffer[BUFFER];
    char message[BUFFER] = "hello.txt";

    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd <0)
    {
        printf("Failed to create socket.\n");
        exit(1);
    }

    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(5555);
    serveraddr.sin_family = AF_INET;

    int b = bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (b <0)
    {
        printf("Failed to bind to port.\n");
        exit(1);
    }

    int l = listen(serverfd, 5);
    printf("Listening on port 5555\n");
    fflush(stdout);

    clientfd = accept(serverfd,(struct sockaddr *)&clientaddr, &addrlen);
    if (clientfd <0)
    {
        printf("Failed to accept connection.\n");
        exit(1);
    }

    recv(clientfd, buffer, BUFFER, 0);
    printf("%s",buffer);
    FILE *f1 = fopen(buffer, "r");
    if (f1 == NULL)
    {
        printf("Failed to open file\n");
        exit(1);
    }
    fgets(buffer, BUFFER, f1);
    printf("%s", buffer);
    close(serverfd);
    close(clientfd);

}








