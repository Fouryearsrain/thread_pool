#include<pool.h>

void thread_pool_strerror(const char * str,int errcode,int errnum)
{

if(errnum)//線程錯誤會
{
	printf("%s:[%s]:\n",str,strerror(errnum));
	pthread_exit(NULL);
}
perror(str);
exit(errcode);//進程錯誤
	
}
