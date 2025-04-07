#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER 1024

int main()
{
    int clientfd;
    struct sockaddr_in clientaddr, serveraddr;
    socklen_t addrlen = sizeof(serveraddr);
    char message[BUFFER] = "Hello server, This is the client.";
    char buffer[BUFFER];

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd<0)
    {
        printf("Failed to create socket.\n");
        exit(1);
    }

    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5555);
    
    int c = connect(clientfd, (struct sockaddr *)&serveraddr, addrlen);
    if (c <0)
    {
        printf("Failed to connect to server \n");
        exit(1);
    }

    send(clientfd, message, BUFFER, 0);
    recv(clientfd, buffer, BUFFER, 0);
    printf("%s", buffer);
    close(clientfd);




}