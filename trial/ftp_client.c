#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main()
{
    int clientfd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrlen = sizeof(serveraddr);

    char filename[1024] = "hello.txt";

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd <0)
    {
        printf("Failed to create socket\n");
        exit(1);
    }

    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(5555);
    serveraddr.sin_family = AF_INET;

    connect(clientfd, (struct sockaddr *)&serveraddr, addrlen);
    send(clientfd, filename, 1024, 0);
    close(clientfd);


}