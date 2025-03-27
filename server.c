#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define PORT 5555 // Use a port above 1024

int main()
{
    char buffer[BUFFER_SIZE];
    int serverfd, clientfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addrlen = sizeof(client_addr); // Initialize client_addrlen

    // Create a TCP socket
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == -1)
    {
        perror("Socket creation failed");
        exit(1);
    }

    // Server address setup
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; 

    // Bind the socket
    if (bind(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind failed");
        close(serverfd);
        exit(1);
    }

    // Start listening
    if (listen(serverfd, 5) == -1)
    {
        perror("Listen failed");
        close(serverfd);
        exit(1);
    }
    printf("Server listening on port %d...\n", PORT);

    // Accept client connection
    clientfd = accept(serverfd, (struct sockaddr *)&client_addr, &client_addrlen);
    if (clientfd == -1)
    {
        perror("Accept failed");
        close(serverfd);
        exit(1);
    }

    // Receive data
    while(true)
    {
        recv(clientfd, buffer, BUFFER_SIZE, 0);
        printf("Received: %s\n", buffer);

        scanf("%s",buffer);
        send(clientfd, buffer, strlen(buffer), 0);
        memset(buffer, 0, BUFFER_SIZE);

        
    }
    
// Close connections
close(clientfd);
close(serverfd);
    return 0;
}
