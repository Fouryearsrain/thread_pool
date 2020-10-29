#include<pool.h>

void *thread_manger_job(void *arg){
	pool_t *pool=(pool_t *)arg;
	int i=0,add=0,ret;
	int num_cur;
	int num_alive;
	int num_busy;
	int num_queue_max=pool->queue_max;
	int num_queue_min=pool->thread_min;
	while(!pool->thread_shutdown){
		pthread_mutex_lock(&pool->plock);
		num_cur=pool->queue_cur;
		num_alive=pool->thread_alive;
		num_busy=pool->thread_busy;
		pthread_mutex_unlock(&pool->plock);

		if(((num_cur>num_alive-num_busy)||(num_busy/(double)num_alive>0.7))&&(num_alive+_THREAD_DFL_CODE_<num_queue_max)){
		
		for(i=0,add=0;i<num_queue_max&&add<_THREAD_DFL_CODE_;i++,add++){
		if(pool->tids[i]==0||thread_if_alive(pool->tids[i])==0)
		if((ret=pthread_create(&pool->tids[i],NULL,thread_customer_job,(void*)pool))!=0){
	thread_pool_strerror("thread_pool_init failed create thread error",-2,ret);	
			
				}
		pthread_mutex_lock(&pool->plock);
		++pool->thread_alive;
		pthread_mutex_unlock(&pool->plock);
			}
		
		}

		//刪減

		if((num_busy/(double)num_alive<0.3)&&num_alive-_THREAD_DFL_CODE_>num_queue_min){
		
		pthread_mutex_lock(&pool->plock);
		pool->thread_exitcode=_THREAD_DFL_CODE_;
		pthread_mutex_unlock(&pool->plock);
			for(i=0;i<_THREAD_DFL_CODE_;i++){
			pthread_cond_signal(&pool->pnot_empty);	
			}
		}
		sleep(_TIMEOUT_);
	}
	pthread_exit(NULL);
}
