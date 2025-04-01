//UDP server

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
    int serverfd, clientfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size  = sizeof(struct sockaddr_in);
    char buffer[BUFFER_SIZE];

    //Socket
    serverfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if( serverfd< 0)
    {
        printf("Failed to create socket");
        exit(1);
    }

    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5666);

    //BInding
    int k = bind(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(k <0)
    {
        printf("Failed to bind to socket.");
        exit(1);
    }
    printf("UDP server listening on pport 5666");
    fflush(stdout);
    
    //reciving data
    socklen_t client_addr_size = sizeof(client_addr);
    ssize_t rec = recvfrom(serverfd, buffer, BUFFER_SIZE -1, 0, (struct sockaddr *)&client_addr, &client_addr_size);
    if (rec < 0)
    {
        printf("failed to recieve");
        exit(1);
    }
    
    printf("%s", buffer);
    strcpy(buffer, "Hello");
    ssize_t sen = sendto(serverfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, client_addr_size);
    if (sen <0)
    {
        printf("failed to send");
        exit(1);
    }


    close(serverfd);

}