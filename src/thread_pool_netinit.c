#include<pool.h>
int thread_pool_netinit(void)
{
	int serverfd;
	struct sockaddr_in serveraddr;
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(_SERVER_PORT_);
	inet_pton(AF_INET,_SERVER_IP_,&serveraddr.sin_addr.s_addr);

	if((serverfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		thread_pool_strerror("thread_pool_netinit call failed socket create",-1,0);	
	}
	if((bind(serverfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)))==-1)
	{
		thread_pool_strerror("thread_pool_netinit call failed socket bind",-1,0);	
	}

	if((listen(serverfd,_LISTEN_SIZE_))==-1)
	{
		thread_pool_strerror("thread_pool_netinit call failed socket listen",-1,0);	
	}
	return serverfd;
}

