#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<ctype.h>
#define SERVER_IP "192.168.159.148"
#define PORT 11111
int main()
{
	int socketfd,clientfd;
	if((clientfd=socket(AF_INET,SOCK_STREAM,0))<0){
	printf("socket error\n");
	return 1;
		
	}
	struct sockaddr_in server_addr,client_addr;
	bzero(&server_addr,sizeof(server_addr));
	int ret=0;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	//inet_pton(AF_INET,SERVER_IP,&server_addr.sin_addr.s_addr);
	server_addr.sin_addr.s_addr=inet_addr("192.168.159.148");
	if(connect(clientfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
	printf("connect error\n");
	return ;
	}
			printf("success\n");
			char buf[1024];
			while(1)
			{
				fgets(buf,sizeof(buf),stdin);
				write(clientfd,buf,strlen(buf));
				int n = read(clientfd,buf,sizeof(buf));
				write(STDOUT_FILENO,buf,n);
			}
			close(socketfd);
			close(clientfd);
			return 0;
}


