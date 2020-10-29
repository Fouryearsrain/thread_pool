#include<pool.h>

int thread_if_alive(pthread_t tid)
{
int errcode;
if((errcode=pthread_kill(tid,0))>0){
	
	if(errcode==ESRCH)
	{
	return _FALSE_;	
	}
	
	}
	return _TRUE_;

}
