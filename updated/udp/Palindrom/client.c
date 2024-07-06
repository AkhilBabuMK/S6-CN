#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#define PORT  8082
int main(){
    int sockfd,n;
    //only one structure variable in udp client hence it is used every where but serever has 2 variables
    struct sockaddr_in serv_addr;
    int len = sizeof(serv_addr);

    memset(&serv_addr,0,sizeof(serv_addr));

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=INADDR_ANY;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        perror("failed to create socket");
        return -1;
    }
    
    while(1){
        char buffer[1024]={0};
        char hello[100]={0};

        printf("Enter the data to server \n:");
        gets(hello);

        if(strcmp(hello,"exit")==0){
            break;
        }

        if(sendto(sockfd,(char *)hello,strlen(hello),0,(struct sockaddr*)&serv_addr,len)<0){
            perror("failed to send");
            return -1;
        }
        printf("data sended");

        n=recvfrom(sockfd,(char *)buffer,1024,0,(struct sockaddr*)&serv_addr,&len);
        buffer[n]='\0';
        printf("data from server is : %s\n", buffer);

    }
    
    close(sockfd);
    return 0;
    
    
}

