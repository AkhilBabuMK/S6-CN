#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
int main(int argc, char const* argv[])
{
    int status, valread, clientsocket;
    char hello[100];
    struct sockaddr_in serv_addr;
    printf("Enter message from client:");
    gets(hello);
    while(strcmp(hello,"exit")!=0)
    {
        char buffer[1024] = { 0 };
        clientsocket = socket(AF_INET, SOCK_STREAM, 0);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr= INADDR_ANY;
        serv_addr.sin_port = htons(PORT);
        status= connect(clientsocket, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
        send(clientsocket, hello, strlen(hello), 0);
        printf("%s message sent to server\n\n",hello);
        valread = read(clientsocket, buffer, 1024);
        if(strcmp(buffer,"exit")==0){
        printf("Server Terminated\n");
        break;
        }
        printf("%s received from server\n\n",buffer);
        printf("Enter message from client:");
        gets(hello);
    }
close(clientsocket);
return 0;
}
