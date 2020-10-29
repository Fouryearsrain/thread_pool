#include<pool.h>

void *thread_customer_job(void *arg)
{
	pthread_detach(pthread_self());
	pool_t *pool=(pool_t *)arg;

task_t task;
while(!pool->thread_shutdown){
pthread_mutex_lock(&pool->plock);

while(pool->queue_cur==_FALSE_){
		if(pool->thread_exitcode>0){
			break;
			}
			pthread_cond_wait(&pool->pnot_empty,&pool->plock);
		}
	if(pool->thread_shutdown||pool->thread_exitcode>0){
		--pool->thread_exitcode;
		--pool->thread_alive;
		pthread_mutex_unlock(&pool->plock);
		pthread_exit(NULL);
	}
	task.job=pool->task_queue[pool->queue_rear].job;
	task.arg=pool->task_queue[pool->queue_rear].arg;
	pool->queue_rear=(pool->queue_rear+1)%pool->queue_max;
	++pool->thread_busy;
	--pool->queue_cur;
	pthread_mutex_unlock(&pool->plock);
	task.job(task.arg);
	pthread_cond_signal(&pool->pnot_full);
	pthread_mutex_lock(&pool->plock);
	--pool->thread_busy;
	pthread_mutex_unlock(&pool->plock);
		
	}
	pthread_exit(NULL);//應該是走不到這一步
}
