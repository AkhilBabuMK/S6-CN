#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
#define SO_REUSEPORT 15

int main(int argc, char const* argv[])
{
    char buffer[1024] = { 0 };
    int serversocket, clientsocket, valread, opt = 1;
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    int addrlen = sizeof(address);
    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(serversocket, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt));
    bind(serversocket, (struct sockaddr*)&address,sizeof(address));
    listen(serversocket, 3);
    while(1)
    {
        char hello[100]={0};
        char buffer[1024] = { 0 };
        clientsocket= accept(serversocket, (struct sockaddr*)&address,(socklen_t*)&addrlen);
        valread= read(clientsocket,buffer,1024);
        printf("%s received from client\n\n", buffer);
        printf("Enter message from server:");
        gets(hello);
        printf("\n");
        if(strcmp(hello,"exit")==0)
        {
            printf("\nServer closed\n");
            send(clientsocket, hello, strlen(hello), 0);
            break;
        }
        else{
            send(clientsocket, hello, strlen(hello), 0);
            printf("%s message sent to client\n\n",hello);
        }
    }
    close(clientsocket);
    shutdown(serversocket, SHUT_RDWR);
    return 0;
}
