#include<pool.h>

pool_t *thread_pool_init(int min,int max,int que_max)
{

	pool_t *pool=NULL;
	if((pool=(pool_t *)malloc(sizeof(pool_t)))==NULL){
		thread_pool_strerror("thread_pool_init failed pool_t mallocerror\n",-1,0);
	}
	if((pool->task_queue=(task_t *)malloc(sizeof(task_t)*que_max))==NULL){
		thread_pool_strerror("thread_pool_init failed pool->task_queue mallocerror\n",-1,0);
		
	}
	if((pool->tids=(pthread_t *)malloc(sizeof(pthread_t)*max))==NULL){
		thread_pool_strerror("thread_pool_init failed pool_t->tids malloc error\n",-1,0);

	}
	pool->thread_shutdown=_FALSE_;//關閉
	pool->thread_max=max;
	pool->thread_min=min;
	pool->thread_alive=0;
	pool->thread_busy=0;
	pool->thread_exitcode=0;

	pool->queue_max=que_max;
	pool->queue_cur=0;
	pool->queue_front=0;
	pool->queue_rear=0;

	//鎖和條件變量初始化
	int ret=0;
	if((ret=pthread_mutex_init(&pool->plock,0))!=0||(ret=pthread_cond_init(&pool->pnot_full,NULL))!=0||(ret=pthread_cond_init(&pool->pnot_full,NULL))!=0){
	thread_pool_strerror("thread_pool_init failed mutex or cond init error",-2,ret);	
	}

	//線程初始化
	for(int i=0;i<pool->thread_min;i++){
		if((ret=pthread_create(&pool->tids[i],NULL,thread_customer_job,(void*)pool))!=0){
	thread_pool_strerror("thread_pool_init failed create thread error",-2,ret);	
			
		}
		++pool->thread_alive;
	}
		if((ret=pthread_create(&pool->mtid,NULL,thread_manger_job,(void *)pool))!=0){
	thread_pool_strerror("thread_pool_init failed create thread error",-2,ret);	
			
	}
	return pool;
}

