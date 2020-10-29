#include<pool.h>

int thread_epoll_init(int serverfd)
{
	int epfd,ret;
	struct epoll_event ep_eve;
	if((epfd=epoll_create(_TRUE_))==-1){
		thread_pool_strerror("epoll_init failed epoll_create error",-1,0);
	}
	ep_eve.data.fd=serverfd;
	ep_eve.events=EPOLLIN;
	ep_eve.events|=EPOLLET;
	if((ret=epoll_ctl(epfd,EPOLL_CTL_ADD,serverfd,&ep_eve))==-1){
		thread_pool_strerror("epoll_init failed epoll_ctl error",-1,0);
	}
	return epfd;

}
