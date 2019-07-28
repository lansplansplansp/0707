#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>

using namespace std;

struct ITEM
{
    int key;
    int value;
};
/*add item to list,make sure list is not null*/
void additem(struct ITEM* itemptr)
{
    assert(itemptr!=NULL);
    /*additemtolist*/
}
int main(void)
{
	float a,b;
	a = 9.9;
	b = 5.0;
	cout << a/b << endl;
    additem(NULL);
    return 0;
}