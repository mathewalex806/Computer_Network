#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define BUFFER 1024 

void main()
{
    struct sockaddr_in server_addr, client_addr;
    socklen_t addrlen = sizeof(client_addr);
    char buffer[BUFFER] = "Hi Client, This is the server.";
    char message[BUFFER];
    int clientfd, serverfd;

    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0)
    {
        printf("Failed to create socket\n");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5555);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int k = bind(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (k <0)
    {
        printf("Failed to bind to socket.\n");
        exit(1);
    }

    int l = listen(serverfd, 5);
    printf("Listeniing on port 5555\n");
    fflush(stdout);

    clientfd = accept(serverfd, (struct sockaddr *)&client_addr, &addrlen);
    if (clientfd<0)
    {
        printf("Failed to connect to the client\n");
        exit(1);
    }
    recv(clientfd, message, BUFFER, 0);
    printf("%s", message);
    send(clientfd, buffer, BUFFER, 0);

    close(clientfd);
    close(serverfd);
}