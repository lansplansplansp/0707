#include <stdio.h>
#include <iostream>

using namespace std;

//将菜单和属性和操作封装在一起，声明菜单项的类
typedef struct tagSysMenu
{
	char *text;
	unsigned char xPos;
	unsigned char yPos;
	void (*onOkFun)();//在该菜单上按下ok键的处理函数指针
	void (*onCancelFun)();//在该菜单上按下cancel键的处理函数指针
}SysMenu,*LPSysMenu;

//用结构体数组来实现每个菜单项
static SysMenu menu[MENU_NUM] = 
{
	{"menu1",0,48,menu1OnOk,menu1OnCancel}
	{"menu2",7,48,menu2OnOk,menu2OnCancel}
	{"menu3",14,48,menu3OnOk,menu3OnCancel}
	{"menu4",21,48,menu4OnOk,menu4OnCancel}
}

//按下Ok键
void onOkKey()
{
	menu[currenFocusMenu].onOkFun();
}

//按下Cancel键
void onCancelKey()
{
	menu[currenFocusMenu].onCancelFun();
}
/*
//按下Ok键
void onOkKey()
{
	//判断在什么焦点菜单上按下OK键，调用相应处理函数
	switch(currenFocus)
	{
		case MENU1:
			menu1OnOk();
			break;
		case MENU2:
			menu2OnOk();
			break;
		case MENU3:
			menu3OnOk();
			break;
		case MENU4:
			menu4OnOk();
			break;
		default:
			break;
	}
}

//按下Cancel键
void onCancelKey()
{
	//判断在什么焦点菜单上按下OK键，调用相应处理函数
	switch(currenFocus)
	{
		case MENU1:
			menu1OnCancel();
			break;
		case MENU2:
			menu2OnCancel();
			break;
		case MENU3:
			menu3OnCancel();
			break;
		case MENU4:
			menu4OnCancel();
			break;
		default:
			break;
	}
}
*/
int main()
{
	return 0;
}