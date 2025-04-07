#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER 1024

int main()
{
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrlen = sizeof(clientaddr);
    char message[BUFFER] = "Hi client, This is the server.";
    char buffer[BUFFER];

    int clientfd, serverfd;

    serverfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverfd <0)
    {
        printf("Failed to create socket.");
        exit(1);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5556);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b  = bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (b <0)
    {
        printf("Failed to bind to port\n");
        exit(1);
    }

    printf("UDP server listening on port 5556\n");
    fflush(stdout);

    recvfrom(serverfd, buffer, BUFFER, 0, (struct sockaddr *)&clientaddr, &addrlen);
    printf("%s", buffer);
    sendto(serverfd, message, BUFFER, 0, (struct sockaddr *)&clientaddr, addrlen );

    close(clientfd);
    close(serverfd);


}