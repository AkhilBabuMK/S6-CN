#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#define PORT 8081
int main()
{
    int sockfd,n;
    time_t t;
    time(&t);
    char *hello = ctime(&t);
    char *ack= "Server Acknowledged";
    struct sockaddr_in servaddr, cliaddr;
    int len = sizeof(cliaddr);
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    
    while(1)
    {
        char buffer[1024] = {0};
        n = recvfrom(sockfd, (char *)buffer, 1024, 0, (struct sockaddr*)&cliaddr, &len);
        buffer[n] = '\0';
        printf("\nMsg from client : %s\n",buffer);
        if(strcmp(buffer,"time")==0){
            sendto(sockfd, (char *)hello, strlen(hello), 0, (struct sockaddr*)&cliaddr, len);
            printf("TIME sent to the Client\n\n");
        }
        else{
            sendto(sockfd, (char *)ack, strlen(ack), 0, (struct sockaddr*)&cliaddr, len);
            printf("Acknowledgement sent to Client\n\n");
        }
    }
    return 0;
}
