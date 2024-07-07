#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 6543

int main(){
    int sockfd,size=4,current=0;
    char buffer[1000] = {0};
    char data[100][100];

    struct sockaddr_in addr;
    int len = sizeof(addr);
   
    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    addr.sin_family=AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr=INADDR_ANY;


    for(int current =0 ; current < size; current++){
        printf("SEND >> ");
        scanf("%s",data[current]);
        sendto(sockfd,data[current],strlen(data[current])+1,0,(struct sockaddr*)&addr,len);
    }

    while(1){
      
            recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,&len);
            printf("\nrecv >> %s\n", buffer);
            if(buffer[1]=='N'){
                //send again
                sendto(sockfd,data[current-size],strlen(data[current-size])+1,0,(struct sockaddr*)&addr,len);
                printf("\nRESEND %s", data[current-size]);
                continue;
            }
            printf("SEND >> ");
            scanf("%s",data[current]);
            sendto(sockfd,data[current],strlen(data[current])+1,0,(struct sockaddr*)&addr,len);
            current+=1;
    }

}
