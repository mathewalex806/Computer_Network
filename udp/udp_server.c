#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 5556

int main() {
    int server_socket;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    // Create a UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("UDP Server listening on port %d...\n", PORT);

    // Receive data from client
    ssize_t recv_len = recvfrom(server_socket, buffer, BUFFER_SIZE, 0,
                                (struct sockaddr *)&client_addr, &addr_size);
    if (recv_len < 0) {
        perror("recvfrom failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    
    buffer[recv_len] = '\0'; // Null-terminate received data
    printf("Received from client: %s\n", buffer);

    // Prepare and send response
    const char *response = "UDP SERVER ECHO\n";
    ssize_t send_len = sendto(server_socket, response, strlen(response), 0,
                              (struct sockaddr *)&client_addr, addr_size);
    if (send_len < 0) {
        perror("sendto failed");
    }

    // Close the socket
    close(server_socket);
    return 0;
}
