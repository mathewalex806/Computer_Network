#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define SERVER_PORT 5556
#define SERVER_IP "127.0.0.1"

int main() {
    int client_socket;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    socklen_t addr_size = sizeof(server_addr);

    // Create UDP socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Prepare message
    const char *message = "UDP CLIENT ECHO\n";
    ssize_t send_len = sendto(client_socket, message, strlen(message), 0,
                              (struct sockaddr *)&server_addr, addr_size);
    if (send_len < 0) {
        perror("sendto failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Receive response from server
    ssize_t recv_len = recvfrom(client_socket, buffer, BUFFER_SIZE, 0,
                                (struct sockaddr *)&server_addr, &addr_size);
    if (recv_len < 0) {
        perror("recvfrom failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    
    buffer[recv_len] = '\0'; // Null-terminate received data
    printf("Received from server: %s\n", buffer);

    // Close the socket
    close(client_socket);
    return 0;
}
