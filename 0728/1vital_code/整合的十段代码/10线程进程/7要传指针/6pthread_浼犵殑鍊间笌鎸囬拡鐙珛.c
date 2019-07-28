//函数传的值和指针相互独立，互不影响；
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *routine1(void *arg)
{
	int x1 = (int)arg;
	while(1)
	{
		x1++;
		printf("x1 = %d\n",x1);
		sleep(1);
	}
}
void *routine2(void *arg)
{
	int x2 = *(int *)arg;
	int *x3 = (int *)arg;
	while(1)	
	{
		(*x3)++;
		printf("x2 = %d,x3 = %d\n",x2,*x3);
		sleep(1);
	}
}
void *routine3(void *arg)
{
	char ch1 = *(char *)arg;
	char *pch = (char *)arg;
	while(1)
	{
		ch1++;
		printf("%c,%c\n",ch1,*pch);
		sleep(1);
	}
}
int main()
{
	pthread_t tid1 ;
	pthread_t tid2 ;
	pthread_t tid3 ;
	int x = 100;
	char ch = 'A';
	pthread_create(&tid3,NULL,routine3,(void *)&ch);
	pthread_create(&tid1,NULL,routine1,(void *)x);
	pthread_create(&tid2,NULL,routine2,(void *)&x);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	return 0;
}
