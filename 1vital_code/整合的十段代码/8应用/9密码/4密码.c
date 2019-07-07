#include<stdio.h>
#include<string.h>
typedef struct node
{
	int data;
	struct node *next;
}qnode_t;
typedef struct queue
{
	qnode_t *left;
	qnode_t *right;
}queue_t;
void enqueue(queue_t *phead,char value){
	
}
void dequeue(queue_t *phead){

}
int main()
{
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	FILE *ofp = NULL;
	fp1 = fopen("password.txt","r");
	fp2 = fopen("word.txt","r");
	ofp = fopen("1.c.bak","w+");
	if(fp1 == NULL)
	{
		printf("file not exist\n");
		return 1;
	}
	if(fp2 == NULL)
	{
		printf("file not exist\n");
		return 1;
	}
	if(ofp == NULL)
	{
		printf("file not exist\n");
		return 1;
	}
	int i=0;
	char a[100],b[100],c[100],d[100];
	int ret;
	for(i=0;;i++){
		ret = fscanf(fp1,"%s",&a[i]);
		if(ret = EOF)
			break;
	}
	for(i=0;;i++){
		ret = fscanf(fp2,"%s",&b[i]);
		if(ret = EOF)
			break;
	}
	for(i=0;b[i]!='\0';i++){
		if(b[i]>='0'&&b[i]<='9')
			d[i]=b[i]-'0';
		if(b[i]>='a'&&b[i]<='z')
			d[i]=b[i]-'a';
		if(b[i]>='A'&&b[i]<='Z')
			d[i]=b[i]-'A';
	}
	for(i=0;a[i]!='\0';i++){
		c[i]=a[i]+d[i];
		dequeue(queue_t *qhead,d[i]);
		enqueue(queue_t *qhead,d[i]),
	}
		c[i]='\0';	     
	for(i=0;c[i]!='\0';i++){
		fprintf(ofp,"%c",c[i]);
	}
	for(i=0 ; c[i] != '\0'; i++)
	printf("%c",c[i]);
	printf("\n");
	return 0;
}
