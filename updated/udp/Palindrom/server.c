#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

#define PORT 8082
int main(){

    int isPalindrome(char *str){
        
        int l=0;
        int r=strlen(str)-1;
        while(l<=r){
            if(str[l++]!=str[r--]){
                 return 0;
            }

        }
        return 1;
    }

    int sockfd,n;
    struct sockaddr_in serv_addr,client_addr;
    int len = sizeof(client_addr);
    memset(&serv_addr,0,sizeof(serv_addr));
    memset(&client_addr,0,sizeof(client_addr));   

    time_t t;
    time(&t);
    char *hello = ctime(&t);
    char *ack = "SERVER ACK";

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    
    

    while(1){   
        char buffer[1024]={0};
        n = recvfrom(sockfd,(char*)buffer,1024,0,(struct sockaddr*)&client_addr,&len);
       
        buffer[n]='\0';

        
        printf("\nmessage from the client is : %s\n",buffer);
        // printf("\nMsg from client : %s\n",buffer);
        if(strcmp(buffer,"time")==0){
            sendto(sockfd,(char*)hello,strlen(hello),0,(struct sockaddr*)&client_addr,len);
            printf("data send to client\n");

        }
        else{
            if(isPalindrome(buffer)){
                char result[100] = "palindrome";
                sendto(sockfd,(char*)result,strlen(result),0,(struct sockaddr*)&client_addr,len);
                printf("data send to client\n");
            }
            else{
                char not_resul[100]="notPalindrom";
                sendto(sockfd,(char*)not_resul,strlen(not_resul),0,(struct sockaddr*)&client_addr,len);
                printf("data send to client\n");
            }
            
        }


    }
    close(sockfd);
    return 0;
}