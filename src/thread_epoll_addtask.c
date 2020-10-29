#include<pool.h>

int thread_epoll_addtask(pool_t *pool,task_t *task){
	if(pool->thread_shutdown==0)
	{
	
	pthread_mutex_lock(&pool->plock);

	while(pool->queue_max==pool->queue_cur)
		pthread_cond_wait(&pool->pnot_full,&pool->plock);
	
	if(pool->thread_shutdown){
		
	pthread_mutex_unlock(&pool->plock);
	return _FALSE_;
	}
	pool->task_queue[pool->queue_front].job=task->job;
	pool->task_queue[pool->queue_front].arg=task->arg;
	pool->queue_front=(pool->queue_front+1)%pool->queue_max;

	pthread_mutex_unlock(&pool->plock);
	pthread_cond_signal(&pool->pnot_empty);
	}
	else
	return _FALSE_;
	return _TRUE_;
}
