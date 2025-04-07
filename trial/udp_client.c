#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define BUFFER 1024

void main()
{
    int clientfd, serverfd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrlen = sizeof(serveraddr);
    char buffer[BUFFER];
    char message[BUFFER] = "Hi server, this is the client.";

    clientfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientfd <0)
    {
        printf("Failed to create socket.\n");
        exit(1);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5556);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(clientfd, message, BUFFER, 0, (struct sockaddr *)&serveraddr, addrlen );
    recvfrom(clientfd, buffer, BUFFER, 0, (struct sockaddr *)&serveraddr, &addrlen );
    printf("%s",buffer);
    close(clientfd);
}