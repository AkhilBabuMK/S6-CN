#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define PORT 8000
#define SO_REUSEPORT 15

int main(){
	int clientsocket,serversocket,opt=1;
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	int addrlen = sizeof(address);
	

	serversocket = socket(AF_INET,SOCK_STREAM,0);
	setsockopt(serversocket,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));

	if(bind(serversocket,(struct sockaddr*)&address,sizeof(address) )<0 ){
		printf("failed the bind");
		exit;
	}

	if(listen(serversocket,5)<0){
		perror("faild to listen");
		exit;
	}

	while(1){
		char buffer[1024] = {0};
		char hello[100]= {0};

		clientsocket=accept(serversocket,(struct sockaddr*)&address,(socklen_t*)&addrlen);
		

		read(clientsocket,buffer,sizeof(buffer));
		printf("the data from client is : %s" , buffer);

		printf("Enter the data to the client: ");
		fgets(hello,sizeof(hello),stdin);

		send(clientsocket,hello,sizeof(hello),0);

	}
	close(clientsocket);
	shutdown(serversocket,SHUT_RDWR);
	return 0;
	
}