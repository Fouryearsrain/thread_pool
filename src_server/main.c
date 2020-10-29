#include<pool.h>
int main()
{
 pthread_mutex_init(&acc_lock,NULL);
 int serverfd=thread_pool_netinit();
 
 task_t task;
 task.job=thread_user_job;
 task.arg=(void *)&serverfd;
 
 printf("task ready!\n");
 pool_t *pool=thread_pool_init(30 ,100 ,120);//min,max,que_max;
 printf("thread_pool_init ready!\n");
 int epfd=thread_epoll_init(serverfd);
 printf("thread_pool_init ready!\n");
 thread_epoll_start(epfd,pool,&task);
 printf("thread_epoll_start ready!\n");
 pthread_mutex_destroy(&acc_lock);
	return 0;
}
