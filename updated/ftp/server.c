//accept, recvfrom  and sendto

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
void main()
{
    struct sockaddr_in serveraddr;
    int serversock,clientsocket,n,f;
    char filename[100],filedata[300];
    fflush(stdin);
    serversock=socket(AF_INET,SOCK_STREAM,0);
    bzero((char*)&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=2000;
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(serversock,(struct sockaddr*)&serveraddr,sizeof(serveraddr));   
    listen(serversock,5);
    while(1)
    {
        // clientsize=sizeof(clientaddr);
        socklen_t len = sizeof(serveraddr);
        clientsocket=accept(serversock,(struct sockaddr*)&serveraddr,&len);
        n=read(clientsocket,filename,sizeof(filename));
        filename[n]='\0';
        printf("\nThe requested file from the client is %s.\n",filename);
        //write(1,filename,n);
        f=open(filename,O_RDWR);
        if (f<0) {
        	strcpy(filedata,"No such file");
        	printf("No such file\n");
        	write(clientsocket,filedata,strlen(filedata));
        	break;
        }
        n=read(f,filedata,sizeof(filedata));
        printf("\nThe contents of the file: \n\n");
        printf("%s\n",filedata);
        write(clientsocket,filedata,sizeof(filedata));
    }
    close(serversock);
    close(clientsocket);
}

