#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define BUFFER 1024

int main()
{
    int serverfd, clientfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len= sizeof(client_addr);
    char filename[BUFFER] = {0};
    char messge[BUFFER] = "Hello, world";

    //Create socket
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd<0)
    {
        printf("Failed to create socket.\n");
        exit(1);
    }

    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5555);
    

    //Bind socket
    int k = bind(serverfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (k<0)
    {
        printf("Failed to bind to port");
        exit(1);
    }

    int l = listen(serverfd, 5);
    printf("Listening on port 5555\n");
    fflush(stdout);

    clientfd = accept(serverfd, (struct sockaddr *)&client_addr, &len);
    if (clientfd==-1)
    {
        printf("Failed to connect");
    }

    //Recieve the filename from the client.
    recv(clientfd, filename,BUFFER, 0);
    printf("%s", filename);

    FILE *f1 = fopen(filename, "r");
    if (f1 == NULL)
    {
        printf("File does not exits\n");
    }
    char buffer[BUFFER];
    while(fgets(buffer, BUFFER, f1)!=NULL)
    {
        send(clientfd, buffer, BUFFER, 0);
        memset(buffer, 0, BUFFER);
    }

    fflush(stdout);
    close(clientfd);
    close(serverfd);

}