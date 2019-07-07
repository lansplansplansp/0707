#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include<string.h>
#include <errno.h>
#include <sys/ipc.h>

struct student
{
	char name[20];
	int age;
	char email[20];
	char phone[12];
};
struct student stus[] = {{"xiaoma",20,"abc@abc.com","123"},
						 {"xiaoyun",20,"bcd@bcd.com","234"},
						 {"xiaozong",20,"cde@cde.com","345"},
};

struct sembuf sem_p = {0,-1,SEM_UNDO};
struct sembuf sem_v = {0,1,SEM_UNDO};
int main(int argc,char **argv)
{
	int shm_id;//存储内核返回的标识;
	int sem_id;
	char *pstr;
	int num = 0;
	key_t shm_key,sem_key;
	if(argc != 2)
	{
		printf("usage error\n");
		return;
	}
	shm_key = ftok(".",0);//产生标识;
	sem_key = ftok(".",1);//产生标识;
	printf("shm_key: %d,sem_key: %d\n",shm_key,sem_key);
	shm_id = shmget(shm_key,1024,0666|IPC_CREAT|IPC_EXCL);//申请内存:0成功，-1失败;
	if(shm_id == -1)
	{
		shm_id = shmget(shm_key,1024,0666);
		if(shm_id == -1)
		{
			perror("shmget\n");
			return 1;
		}
	}
	sem_id = semget(sem_key,1,0666|IPC_CREAT|IPC_EXCL);//申请内存:0成功，-1失败;
	if(sem_id == -1)
	{
		if(errno == EEXIST)
		sem_id = semget(sem_key,1,0666);
		else
		{
			perror("semget\n");
			return 1;
		}
	}
	semctl(sem_id,0,SETVAL,1);//设置信号量初值；而且只能在一个进程里面设置
										//随机存储
	pstr = (char *)shmat(shm_id,NULL,SHM_RND);//关联共享内存；等价于内存的映射；
	if(pstr ==  (char *)-1)
	{
		perror("shmat\n");
		return 1;
	}
	printf("pstr: %p\n",pstr);
	//sem p option
	while(1)
	{
		printf("%d shm_w sem pend\n",num++);
		if(semop(sem_id,&sem_p,1))
		{
			perror("semop P option");
		}
		*pstr =(char) (sizeof(stus)/sizeof(struct student));
		memcpy(pstr+1,stus,sizeof(stus));
		sleep(1);
		//sem v option
		if(semop(sem_id,&sem_v,1))//sem p option
		{
			perror("semop v option");
		}
	}
	shmdt(pstr);//这个不是删除；//断开和共享内存的关联；这个共享内存还存在的；

	return 0;

}
