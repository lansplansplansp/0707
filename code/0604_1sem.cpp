#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

class Z
{
public:
	int x;
};
typedef struct a 
{
	int x;
	int y;
}a_t;
union senum{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);
static int sem_id;

int main(int argc, char *argv[])
{
	a_t *aa = NULL;
	aa = new a_t;
	cout << aa << endl;
	Z a;
	cout << a.x << endl;
	int i;
	cout << i << endl;
	int pause_time;
	char op_char = 'O';
	srand((unsigned int)getpid());
	sem_id = semget((key_t)1234,1,0666 | IPC_CREAT);
	
	if(argc > 1)
	{
		if(!set_semvalue())
		{
			fprintf(stderr,"Failed to initialize semaphroe\n");
			exit(EXIT_FAILURE);
		}
		op_char = 'X';
		sleep(5);
	}
	
	for(i=0;i<10;i++)
	{
		if(!semaphore_p())
		{
			exit(EXIT_FAILURE);
		}
		printf("%c",op_char);
		fflush(stdout);
		pause_time = rand()%3;
		sleep(pause_time);
		printf("%c",op_char);
		fflush(stdout);
		if(!semaphore_v())
		{
			exit(EXIT_FAILURE);
		}
		pause_time = rand()%2;
		sleep(pause_time);
	}
	printf("\n%d - finished\n",getpid());

	if(argc > 1)
	{
		sleep(10);
		del_semvalue();
	}
	exit(EXIT_SUCCESS);
}

static int set_semvalue(void)
{
	union senum sem_union;
	sem_union.val = 1;
	if(semctl(sem_id,0,SETVAL,sem_union)==-1)
	{
		return(0);
	}
	return(1);
}

static void del_semvalue(void)
{
	union senum sem_union;
	if(semctl(sem_id,0,IPC_RMID,sem_union)==-1)
	{
		fprintf(stderr,"Failed to delete semaphroe\n");
	}
}

static int semaphore_p(void)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	if(semop(sem_id,&sem_b,1)==-1)
	{
		fprintf(stderr,"semaphore_p failed\n");
		return(0);
	}
	return(1);
}
static int semaphore_v(void)
{
	struct sembuf sem_b;
	
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	if(semop(sem_id,&sem_b,1)==-1)
	{
		fprintf(stderr,"semaphore_v failed\n");
		return(0);
	}
	return(1);
}