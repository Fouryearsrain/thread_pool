#include<pool.h>
void *thread_user_job(void *arg)
{
	int serverfd=*(int *)arg;
	int clientfd;
	struct sockaddr_in clientaddr;
	socklen_t addrsize=sizeof(clientaddr);

	pthread_mutex_lock(&acc_lock);
	if((clientfd=accept(serverfd,(struct sockaddr *)&clientaddr,&addrsize))==-1)
	{
	thread_pool_strerror("thread_user_job call failed accept error\n",-1,0);	
	}
	pthread_mutex_unlock(&acc_lock);

	int buffer_len;
	char buffer[buffer_len];
	int j;
	while((buffer_len=recv(clientfd,buffer,sizeof(buffer),0))>0)
	{
		j=0;
		while(j<buffer_len)
		{
		buffer[j]=toupper(buffer[j]);
		j++;
		}
		send(clientfd,buffer,buffer_len,0);
		bzero(buffer,sizeof(buffer));
	}
	if(buffer_len==_FALSE_)
	{
	close(clientfd);
	return NULL;
	}
	return NULL;
}
