#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#define PORT 8081
int main()
{
    int sockfd,n;
    struct sockaddr_in servaddr;
    int len = sizeof(servaddr);
  
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  
    while(1)
    {
        char buffer[1024]={0};
        char hello[100]={0};
        printf("\nenter data to send : ");
        gets(hello);
        if(strcmp(hello,"exit")==0)
            break;        
	sendto(sockfd, (char *)hello, strlen(hello), 0, (struct sockaddr*)&servaddr, len);
        printf("Data sent to the Server.\n");
        n = recvfrom(sockfd, (char *)buffer, 1024, 0, (struct sockaddr*)&servaddr, &len);
        printf("Response from server : %s\n", buffer);
    }
      close(sockfd);
      return 0;
}


