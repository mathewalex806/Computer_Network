#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>


#define BUFFER_SIZE 1024
#define PORT 5555 // Updated port number

int main()
{
    char buffer[BUFFER_SIZE];
    int clientfd;
    struct sockaddr_in server_addr;
    
    // Create socket
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        perror("Socket creation failed");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
    {
        perror("Invalid address / Address not supported");
        close(clientfd);
        exit(1);
    }

    // Connect to the server
    if (connect(clientfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Connection failed");
        close(clientfd);
        exit(1);
    }

    // Send message
    while(true)
    {
    scanf("%s",buffer);
    send(clientfd, buffer, strlen(buffer), 0);
    memset(buffer, 0, BUFFER_SIZE); 
    printf("Message sent to server.\n");

    // Receive response
    memset(buffer, 0, BUFFER_SIZE); // Clear buffer
    recv(clientfd, buffer, BUFFER_SIZE, 0);
    printf("Server Response: %s\n", buffer);
    }
    

    // Close connection
    close(clientfd);

    return 0;
}
