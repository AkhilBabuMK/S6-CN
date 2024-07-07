#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define PORT 6543

int main(){
    int sockfd,size=4,current=0;
    char buffer[1000] = {0};

    struct sockaddr_in addr;
    int len = sizeof(addr);
    
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    addr.sin_family=AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr=INADDR_ANY;

    bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)); //check

    for(int i =0 ; i < size; i++){
        recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,&len);
        printf("recv >> %s\n", buffer);
    }

    while(1){
        if(current==4){

            sprintf(buffer,"%dNACK",current);
            sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,len);
            printf("\nSEND %s", buffer);
            recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,&len);
            printf("\nrecv >> %s\n", buffer);
            
        }
        
            sprintf(buffer,"%dACK",current);
            sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,len);
            printf("\nSEND %s", buffer);
            recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,&len);
            printf("\nrecv >> %s\n", buffer);
            current+=1;
    }

}
