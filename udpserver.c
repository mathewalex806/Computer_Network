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
    int serverfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_size = sizeof(struct sockaddr_in);

    // Create UDP socket
    serverfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverfd < 0)
    {
        perror("Error creating socket");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5600);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind socket
    if (bind(serverfd, (struct sockaddr *)&server_addr, addr_size) < 0)
    {
        perror("Failed to bind");
        close(serverfd);
        exit(1);
    }

    printf("UDP listening on port 5600...\n");

    // Receive data from client
    socklen_t client_addr_size = sizeof(client_addr);
    ssize_t rec = recvfrom(serverfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_size);
    if (rec < 0)
    {
        perror("recvfrom() failed");
        close(serverfd);
        exit(1);
    }

    buffer[rec] = '\0';  // Null-terminate received string
    printf("Received: %s\n", buffer);

    // Send response to client
    memset(buffer, 0, BUFFER_SIZE);
    strcpy(buffer, "Hello from the server");

    ssize_t sen = sendto(serverfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, client_addr_size);
    if (sen < 0)
    {
        perror("sendto() failed");
    }

    close(serverfd);
    return 0;
}
