#include <stdio.h>
#include <sys/time.h>

int main(int argc,char * argv[])
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	int fruntime = tv.tv_sec*1000+tv.tv_usec/1000;
	while(1)
	{
		if(tv.tv_sec*1000+tv.tv_usec/1000>fruntime+10000)
		{
			printf("fruntime:%d\n",fruntime);
			break;
		}
		gettimeofday(&tv,NULL);
		printf("time %u:%u\n",tv.tv_sec,tv.tv_usec);
		sleep(2);
	}
	return 0;
}