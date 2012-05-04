#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
}NODE;

NODE * root = NULL;

NODE * createnode(int val)
{
	NODE * nn;
	nn = (NODE *)malloc(sizeof(NODE));
	nn->data = val;
	nn->left = NULL;
	nn->right = NULL;
	return nn;
}

void addnode(int val)
{
	NODE * nn,*trav;
	nn = createnode(val);
	if(root == NULL)
		root = nn;
	else
	{
		trav = root;
		while(trav != NULL)
		{
			if(nn->data < trav->data)
			{
				if(trav->left == NULL)	
				{
					trav->left = nn;
					break;
				}
				else
					trav = trav->left;
			}
			else
			{
				if(trav->right == NULL)			
				{
					trav->right = nn;
					break;
				}
				else
					trav = trav->right;
			}
		}
	}
}

void preorder(NODE * trav)
{
	if(trav == NULL)
		return;
	printf(" %d",trav->data);
	preorder(trav->left);
	preorder(trav->right);
}

void inorder(NODE * trav)
{
	if(trav == NULL)
		return;
	inorder(trav->left);
	printf(" %d",trav->data);
	inorder(trav->right);
}


void postorder(NODE * trav)
{
	if(trav == NULL)
		return;
	postorder(trav->left);
	postorder(trav->right);
	printf(" %d",trav->data);
}

NODE * searchnode(int val)
{
	NODE * trav;
	trav = root;
	while(trav != NULL)
	{
		if(trav->data == val)
			return trav;
		else
		{
			if(val < trav->data)
				trav = trav->left;
			else
				trav = trav->right;
		}
	}
	return NULL;
}

void freetree(NODE * trav)
{
	if(trav == NULL)
		return;
	freetree(trav->left);
	freetree(trav->right);
	free(trav);
}

void FreeTree()
{
	freetree(root);
	root = NULL;
}

void main()
{
	NODE * temp;
	addnode(50);
	addnode(30);
	addnode(20);
	addnode(40);
	addnode(70);
	addnode(65);
	addnode(60);
	addnode(80);
	addnode(75);
	addnode(85);
	preorder(root);
	printf("\n");
	inorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	
	temp = searchnode(20);
	if(temp == NULL)
		printf("Value not present ");
	else
		printf("Value is present at address : %d\n",temp);
	FreeTree();
}
