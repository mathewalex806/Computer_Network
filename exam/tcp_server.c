//Tcp server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main()
{
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addrleen = sizeof(client_addr);
    int serverfd, clientfd;

    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0)
    {
        printf("Failed to create socket.\n");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5555);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //binding 

    int k = bind(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (k<0)
    {
        printf("Failed to bind to socket.\n");
        exit(1);
    }

    //listen for connection

    if (listen(serverfd, 5)==-1)
    {
        printf("Failed to listen for connections.\n");
        exit(1);
    }
    printf("Listening on port 5555 for connections.\n");

    //accept connection
    clientfd = accept(serverfd, (struct sockaddr *)&client_addr, &client_addrleen);
    if (clientfd ==-1)
    {
        printf("Failed to accept connection.\n");
        exit(1);
    }

    recv(clientfd, buffer, BUFFER_SIZE, 0);
    printf("Message from client %s", buffer);

    memset(buffer, 0, BUFFER_SIZE);
    strcpy(buffer, "Hello from the server.");
    send(clientfd, buffer, BUFFER_SIZE, 0);
    printf("Sent message to the client.");

    close(clientfd);
    close(serverfd);
    return 0;

}