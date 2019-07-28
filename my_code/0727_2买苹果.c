#include <stdio.h>

//超市中购买苹果，若购买10斤以下，则2元一斤，则购买10斤以上，则打8折，请设计一个程序，输入购买的斤数，输出应付款总额
int main()
{
	int iapple = 0;
	int num = 0;
	while(1)
	{
		printf("How many apples do you want to buy?\n");
		scanf("%d",&iapple);
		if(iapple<0)
		{
			perror("input is error number\n");
			continue;
		}
		iapple>=10?(num=1):(num=-1);
		switch(num)
		{
			case 1:
				printf("total amount due:%f\n",1.0*iapple*2*0.8);
				break;
			case -1:
				printf("total amount due:%d\n",iapple*2);	
				break;
			default:
				break;
		}
	}
	
	return 0;
}