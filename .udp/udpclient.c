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
    int clientfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t server_addr_size = sizeof(server_addr);

    // Create UDP socket
    clientfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientfd < 0)
    {
        perror("Failed to create socket");
        exit(1);
    }

    // Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5600);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("UDP client sending data to port 5600...\n");

    // Sending data
    strcpy(buffer, "Hello server, this is the client.");
    ssize_t sen = sendto(clientfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, server_addr_size);
    if (sen < 0)
    {
        perror("sendto() failed");
        close(clientfd);
        exit(1);
    }

    // Receive response
    memset(buffer, 0, BUFFER_SIZE);
    ssize_t rec = recvfrom(clientfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &server_addr_size);
    if (rec < 0)
    {
        perror("recvfrom() failed");
        close(clientfd);
        exit(1);
    }

    buffer[rec] = '\0'; // Null-terminate the received message
    printf("Received from server: %s\n", buffer);

    close(clientfd);
    return 0;
}
