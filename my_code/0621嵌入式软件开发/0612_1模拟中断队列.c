#include <stdio.h>
#include <iostream>

using namespace std;

typedef struct tagIntQueue//存放中断的队列
{
	int intType;//中断类型
	struct tagIntQueue *next;//做个链表
}IntQueue;
IntQueue lpIntQueueHead;
__interrupt ISRexample()
{
	int intType;
	intType = GetSystem Type();//得到中断类型
	QueueAddTail(lpIntQueueHead,intType);//在队列尾加入新的中断
}
int main()
{
	while(1)
	{
		if(!IsIntQueueEmpty())
		{
			intType = GetFirstInt();
			switch(intType)
			{
				case 1:
					cout << 1 << endl;
					break;
				case 2:
					cout << 2 << endl;
					break;
				case 3:
					cout << 3 << endl;
					break;
				default:
					cout << "!" << endl;
					break;
			}
		}
	}
}