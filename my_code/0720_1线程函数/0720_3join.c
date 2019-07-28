#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>

void* pthread_running(void *_val)
{
    printf("pthred_self pid:%d,getpid:%d,getppid:%d\n",pthread_self(),getpid(),getppid());
    printf("%d:%s\n",__LINE__, (char*)_val);
    return NULL;
}

int main()
{
    pthread_t tid;
	int cnt=0;;
 	printf("%d:tid:%d\n",__LINE__,tid);
    int ret = pthread_create(&tid, NULL, pthread_running, "main thread is running");//成功返回0，错误返回-1
	printf("%d:ret:%d\n",__LINE__,ret);
 	printf("%d:tid:%d\n",__LINE__,tid);
	if(ret != 0)
    {
        printf("create thread error! info is:%s\n", strerror(ret));
        return ret;
    }

    if(cnt = pthread_join(tid,NULL)!=0)
	{
		printf("%d:pthread pthread_join failed\n",__LINE__);
		return -1;
	}
	else
	{
		printf("%d:pthread_join return success:%d\n",__LINE__,cnt);//成功时返回0，失败返回其他值
	}

    return 0;
}
