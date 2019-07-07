#include<stdio.h>
#include<stdlib.h>

typedef struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
}tree_t;
tree_t *create_newnode(int value){
      tree_t *newnode = (tree_t *)malloc(sizeof(tree_t));
	  newnode->data = value;
	  newnode->left = NULL;  
	  newnode->right = NULL;  
	  return newnode;
}
void pre_order(tree_t *root){
	if(root == NULL)
		return;
	printf("%d\n",root->data);
	pre_order(root->left);
	pre_order(root->right);
}
void mid_order(tree_t *root){
	if(root == NULL)
		return;
	mid_order(root->left);
	printf("%d\n",root->data);
	mid_order(root->right);
}
void tree_insert(tree_t *root,int value)
{
	tree_t *p = root;
	tree_t *parent = root;
	while(p!=NULL)
	{
		if(p->data == value)			
			return;
		else if(p->data > value){
			parent = p;
			p = p -> left;
		}
		else
		{
			parent = p;
			p = p ->right;
		}
	}
	tree_t *newnode = create_newnode(value);
	if(parent->data>value)
		parent->left = newnode;
	else
		parent->right = newnode;
}
tree_t *tree_init(int value)//初始一个根；
{
	tree_t *root = NULL;
	root = create_newnode(value);
	return root;
}
tree_t *tree_insert2(tree_t *root,int value)
{
	if(root == NULL)
		root = create_newnode(value);
	else if(root->data > value)
		root->left = tree_insert2(root->left,value);
	else if(root->data < value)
		root->right = tree_insert2(root->right,value);
	return root;
}
int main()
{   tree_t *root = tree_init(50);
	tree_insert(root,14);
	tree_insert(root,30);
	tree_insert(root,56);
	tree_insert(root,33);
	tree_insert(root,54);
	tree_insert(root,35);
	tree_insert2(root,14);
	tree_insert2(root,30);
	tree_insert2(root,56);
	tree_insert2(root,33);
	tree_insert2(root,54);
	tree_insert2(root,35);
	mid_order(root);
	printf("-------------------\n");
	pre_order(root);
	printf("-------------------\n");
	mid_order(root);
	return 0;
}
