#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main()
{
    int clientfd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrlen = sizeof(serveraddr);

    char buffer[1024];
    char message[1024] = "1234";

    clientfd = socket(AF_INET, SOCK_DGRAM, 0);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(6666);

    sendto(clientfd, message, strlen(message), 0, (struct sockaddr *)&serveraddr, addrlen);
    recvfrom(clientfd, buffer, 1024, 0, (struct sockaddr *)&serveraddr, &addrlen);
    printf("%s", buffer);
    close(clientfd);
}