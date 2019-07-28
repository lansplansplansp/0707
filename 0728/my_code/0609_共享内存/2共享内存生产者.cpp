#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "share.h"

int main()
{
	int running = 1;
	void *shared_memory = (void *)0;//保存shmat返回的共享内存指针
	struct shared_use_st *shared_stuff;
	char buffer[TEXT_SZ];
	int shmid;
	srand((unsigned int)getpid());
	shmid = shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);//申请内存:0成功，-1失败;
	
	if(shmid == -1)
	{
		shmid = shmget((key_t)1234,sizeof(struct shared_use_st),0666);
		if(shmid == -1)
		{
			perror("shmget\n");
			return 1;
		}
	}
	
	shared_memory = shmat(shmid,(void *)0,0);//将共享内存连接到自己的空间中
	if(shared_memory == (void *)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n",(int)shared_memory);
	shared_stuff = (struct shared_use_st *)shared_memory;
	shared_stuff->written_by_you = 0;
	while(running)
	{
		while(shared_stuff->written_by_you == 1)
		{
			sleep(1);
			printf("waitting for client...\n");
		}
		printf("Enter some text: ");
		fgets(buffer,TEXT_SZ,stdin);
		
		strncpy(shared_stuff->some_text,buffer,TEXT_SZ);
		shared_stuff->written_by_you = 1;
		if(strncmp(buffer,"end",3) == 0)
		{
			running = 0;
		}
	}
}