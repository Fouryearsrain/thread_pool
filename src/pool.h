#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<fcntl.h>
#include<signal.h>
#include<errno.h>
#include<sys/epoll.h>
#include<sys/types.h>
#include<sys/stat.h>

#define _THREAD_DFL_CODE_ 10
#define _SERVER_IP_ "192.168.159.148"
#define _SERVER_PORT_ 11111
#define _TRUE_ 1
#define _FALSE_ 0
#define _LISTEN_SIZE_ 128
#define _BUFFER_SIZE_ 1500
#define _TIMEOUT_ 1

pthread_mutex_t acc_lock;

typedef struct {
	void * (*job)(void *);
	void *arg;
}task_t;

typedef struct {
	int thread_shutdown;
	int thread_max;
	int thread_min;//初始化時的線程數
	int thread_alive;
	int thread_busy;
	int thread_exitcode;//?

	task_t *task_queue;
	int queue_max;
	int queue_cur;//當前正在等待被除離的任務數
	int queue_front;
	int queue_rear;

	pthread_t *tids;
	pthread_t mtid;

	pthread_mutex_t plock;//?
	pthread_cond_t pnot_full;
	pthread_cond_t pnot_empty;
}pool_t;
int thread_pool_netinit(void);
void thread_pool_strerror(const char *,int ,int );//int1進程 int2線程
void *thread_user_job(void *);//用戶自定義的任務
pool_t * thread_pool_init(int ,int ,int);//線程池初始化 min max que_max
void *thread_manger_job(void *);//線程池管理者
void *thread_customer_job(void *);//線程的處理函數
int thread_epoll_init(int );//epoll初始化 接收socket
void thread_epoll_start(int ,pool_t *,task_t *);//線程池開始工作 epfd, pool,task
int thread_epoll_addtask(pool_t *,task_t *);//網線城池加任務
int thread_if_alive(pthread_t );
