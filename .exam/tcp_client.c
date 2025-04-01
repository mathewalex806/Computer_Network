#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024 

int main()
{
    char buffer[BUFFER_SIZE];
    int clientfd;
    struct sockaddr_in server_addr;

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd ==-1)
    {
        printf("Failed to create socket.\n");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5555);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int k = connect(clientfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (k==-1)
    {
        printf("Failed to connect");
        exit(1);
    }

    scanf("%s",buffer);
    send(clientfd, buffer, strlen(buffer), 0);
    memset(buffer, 0, BUFFER_SIZE); 
    printf("Message sent to server.\n");
    fflush(stdout);

    // Receive response
    memset(buffer, 0, BUFFER_SIZE); // Clear buffer
    recv(clientfd, buffer, BUFFER_SIZE, 0);
    printf("Server Response: %s\n", buffer);

    close(clientfd);
}