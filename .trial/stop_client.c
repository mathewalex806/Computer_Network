// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define SERVER_IP "127.0.0.1"
#define PORT 6666
#define BUFFER 1024
#define TIMEOUT 3  // Timeout in seconds

int main() {
    int clientfd;
    struct sockaddr_in serveraddr;
    char buffer[BUFFER] = {0};
    char packet[BUFFER];

    // Create socket
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to server
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Connection failed");
        close(clientfd);
        exit(EXIT_FAILURE);
    }

    printf("Client: Connected to server.\n");

    int packet_number = 0;
    while (packet_number < 5) {
        sprintf(packet, "Packet %d", packet_number);
        printf("Client: Sending -> %s\n", packet);
        send(clientfd, packet, strlen(packet), 0);

        int valread = recv(clientfd, buffer, BUFFER, 0);

        if (valread > 0) {
            buffer[valread] = '\0';
            printf("Client: Received -> %s\n", buffer);

            if (strncmp(buffer, "ACK", 3) == 0) {
                printf("Client: ACK received for packet %d\n\n", packet_number);
                packet_number++;  // Move to next packet
            } else {
                printf("Client: Invalid ACK. Retransmitting packet %d...\n\n", packet_number);
            }
        } else {
            printf("Client: Timeout! Retransmitting packet %d...\n\n", packet_number);
        }

        memset(buffer, 0, BUFFER); // Clear buffer
        sleep(1); // Optional delay
    }

    printf("Client: All packets sent successfully.\n");
    close(clientfd);
    return 0;
}
