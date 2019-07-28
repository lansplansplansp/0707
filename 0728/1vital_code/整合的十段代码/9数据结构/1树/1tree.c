#include<stdio.h>
#include<stdlib.h>

typedef struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
}tree_t;
tree_t *create_newnode(int value)
{
	tree_t *newnode = (tree_t *)malloc(sizeof(tree_t));
	newnode->data = value;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}
void pre_order(tree_t *root)
{
	if(root == NULL)
		return;
	printf("%d\n",root->data);
	pre_order(root->left);
	pre_order(root->right);
}
tree_t *tree_insert2(tree_t *root,int value)
{
	if(root == NULL)
		root = reate_newnode(value);
	else if(root->data > value)
		root->left = tree_insert(root->left,value);
	else if(root->data < value)
		root->right = tree_insert(root->right,value);
	return root;
}
int main()
{
	tree_t *root = NULL;
	tree_t *A,*B,*C,*D,*E,*F;
	A=create_newnode(1);
	B=create_newnode(2);
	C=create_newnode(3);
	D=create_newnode(4);
	E=create_newnode(5);
	F=create_newnode(6);
	root = A;
	A->left = B;
	A->right = C;
	B->left = D;
	B->right = E;
	C->right = F;
	pre_order(root);
	return 0;
}
