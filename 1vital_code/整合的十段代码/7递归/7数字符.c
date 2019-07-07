#include<stdio.h>
#include<string.h>
int i=0;
int fun(char str[])
{
    if(str[i]=='\0')
        return;
    printf("%c",str[i++]);
    fun(str);
}
int main()
{
	printf("please input a string:\n");
	char array[1024];
	scanf("%s",array);
	int n = strlen(array);
	printf("%d\n",n);
	array[n] = '\0';
	fun(array);
	return 0;
}
