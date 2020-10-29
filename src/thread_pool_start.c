#include<pool.h>

void thread_epoll_start(int epfd,pool_t *pool,task_t *task){

 int num_ready;
 struct epoll_event arr[_TRUE_];
	while(pool->thread_shutdown==0){
		
			printf("ready\n");
		if((num_ready=epoll_wait(epfd,arr,_TRUE_,-1))==-1){
			thread_pool_strerror("thread_epoll_start call failed,wpoll_wait error\n",-1,9);
		}
		if(num_ready>0)
		{
			printf("accept\n");
			thread_epoll_addtask(pool,task);
			--num_ready;
		}
	}

}
