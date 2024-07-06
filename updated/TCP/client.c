#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define PORT 8000

int main(){
	int clientsocket,status;
	struct sockaddr_in serv_addr;
	char hello[100] = {0};
	printf("Enter the data to the server: ");
	fgets(hello,sizeof(hello),stdin);
	
	while(1){
		char buffer[1024] = {0};

		clientsocket = socket(AF_INET,SOCK_STREAM,0);
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port= htons(PORT);
		serv_addr.sin_addr.s_addr = INADDR_ANY;

		if(status=connect(clientsocket,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) <0 ){
			perror("cant connect");
			exit;
		}

		send(clientsocket,hello,strlen(hello),0);

		read(clientsocket,buffer,1024);

		printf("msg from server is : %s", buffer);

		printf("Enter the data to the server: ");
		fgets(hello,sizeof(hello),stdin);
	}
	close(clientsocket);
	return 0;

}