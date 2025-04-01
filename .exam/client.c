#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main()
{
    int clientfd, serverfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    //Socket creation
    clientfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientfd <0)
    {
        printf("Failed to create socket");
        exit(1);
    }

    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5666);

    strcpy(buffer, "hello from client.");

    socklen_t server_addr_size = sizeof(server_addr);
    ssize_t sen = sendto(clientfd, buffer, BUFFER_SIZE,0,(struct sockaddr *)&server_addr, sizeof(server_addr));
    if (sen < 0)
    {
        printf("failed to send");
        exit(1);
    }
    memset(buffer, 0, BUFFER_SIZE);
    ssize_t rec = recvfrom(clientfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &server_addr_size);

    if (rec < 0)
    {
        printf("failed ot recieve");
        exit(1);

    }
    else
    {
        printf("%s", buffer);
    }
    close(clientfd);
}