#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{
    int clientfd, serverfd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t addrlen = sizeof(clientaddr);
    char message[1024] = "123";
    char buffer[1024];

    serverfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverfd <0)
    {
        printf("Failed to create socket\n");
        exit(1);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(6666);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("UDP server listening on port 6666\n");
    fflush(stdout);

    recvfrom(serverfd, buffer, 1024, 0, (struct sockaddr *)&clientaddr, &addrlen);
    

    //converting number to string
    printf("%s\n",buffer);
    float num = atof(buffer);
    printf("%f",num);
    // int cpy = num;
    // while(cpy>0)
    // {
    //     int digit = cpy%10;
    //     if (digit == 1)
    //     printf("one ");
    //     else if (digit == 2)
    //     printf("two ");
    //     else if (digit == 3)
    //     printf("three ");
    //     else if (digit == 4)
    //     printf("four ");
    //     else if (digit == 5)
    //     printf("five ");
    //     else if (digit == 6)
    //     printf("six ");
    //     else if (digit == 7)
    //     printf("seven ");
    //     else if (digit == 8)
    //     printf("eight ");
    //     else if (digit == 9)
    //     printf("nine ");
    //     else if (digit == 0)
    //     printf("zero "); 

    //     else
    //     printf("\n");

    //     cpy=cpy/10;
    // }

    sendto(serverfd, message, 1024, 0, (struct sockaddr *)&clientaddr, addrlen);
    close(serverfd);
}