// server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 6666
#define BUFFER 1024

int main() {
    int serverfd, clientfd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrlen = sizeof(clientaddr);
    char buffer[BUFFER];

    // Create socket
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Prepare server address
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Bind failed");
        close(serverfd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    listen(serverfd, 5);
    printf("Server: Listening on port %d...\n", PORT);

    // Accept a client
    clientfd = accept(serverfd, (struct sockaddr *)&clientaddr, &addrlen);
    if (clientfd < 0) {
        perror("Accept failed");
        close(serverfd);
        exit(EXIT_FAILURE);
    }

    printf("Server: Client connected.\n");

    for (int i = 0; i < 10; i++) {
        memset(buffer, 0, BUFFER);
        int valread = recv(clientfd, buffer, BUFFER, 0);
        if (valread <= 0) {
            printf("Server: Failed to receive data.\n");
            continue;
        }

        buffer[valread] = '\0';
        printf("Server: Received -> %s\n", buffer);

        // Decide ACK based on packet number (even = ACK, odd = Fail)
        if (i % 2 == 0) {
            char ack[BUFFER];
            sprintf(ack, "ACK %d.", i);
            send(clientfd, ack, strlen(ack), 0);
            printf("Server: Sent -> %s\n", ack);
        } else {
            char fail[] = "Failed ACK";
            send(clientfd, fail, strlen(fail), 0);
            printf("Server: Sent -> %s\n", fail);
        }
    }

    close(clientfd);
    close(serverfd);
    return 0;
}
