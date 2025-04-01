#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define BUFFER 1024

int main()
{
    int clientfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(server_addr);
    char message[BUFFER];
    char filename[BUFFER] = "hello.txt";
    
    //socket creation

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd<0)
    {
        printf("Failed to create socket.");
        fflush(stdout);
        exit(1);
    }
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5555);

    //connect to server socket
    int c = connect(clientfd, (struct sockaddr *)&server_addr, sizeof(server_addr) );
    if (c<0)
    {
        printf("Failed to connect to server");
        exit(1);
    }

    send(clientfd, filename, sizeof(filename), 0);
    recv(clientfd, message, BUFFER, 0);
    printf("Message recieved from the server: %s\n", message);
    fflush(stdout);

    close(clientfd);


}