#include<stdio.h>
#include<stdlib.h>

#define MAX 5

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
}NODE;

NODE * root = NULL;

NODE * stack[MAX];
int top = -1;
NODE * queue[MAX];
int front ,rear;
front = -1;
rear = -1;

void push(NODE * val)
{
	if(top == MAX-1)
		printf("\nStack is full \n");
	else
	{
		top++;
		stack[ top] = val;
	}
}

NODE * pop()
{
	NODE *val;
	if(top == -1)
	{
		printf("\nStack is empty \n");
		return 0;
	}
	else
	{
		val = stack[top];
		top--;
		return val;
	}
}

int isempty()
{
	if(top == -1)
		return 1;
	else
		return 0;
}

int isemptyq()
{
	if(rear == front && front == -1)
		return 1;
	else
		return 0;
}

void insert(NODE * val)
{
	if((front == -1 && rear ==MAX-1) || (rear == front && rear != -1))
		printf("\nQueue is full \n");
	else
	{
		if(rear == MAX-1)
			rear = -1;
		else
		{
			rear++;
			queue[rear] = val;
		}
	}
}

NODE * removeq()
{
	NODE * val;
	if(front == rear)
		front = rear = -1;
	if(rear == front && front == -1)
		printf("\nQueue is empty \n");
	else
	{
		if(front ==MAX-1)
			front = 0;
		else
		{
			front++;
			val = queue[front];
			return val;
		}
	}
	return 0;
}

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

void inorder(NODE * trav)
{
	trav = root;
	while(!isempty() || trav != NULL)
	{
		while(trav != NULL)
		{
			push(trav);
			trav = trav->left;
		}
		if(!isempty())
		{
			trav = pop();
			printf("  %d",trav->data);
			trav = trav->right;
		}
	}
}

void preorder(NODE * trav)
{
	trav = root;
	while(!isempty() || trav != NULL)
	{
		while(trav != NULL)
		{
			printf("  %d",trav->data);
			if(trav->right != NULL)
				push(trav->right);
			trav = trav->left;
		}
		if(!isempty())
		{
			trav = pop();
		}
	}
}

NODE * DFS(int val)
{
	static NODE *trav;
	trav = root;
	push(trav);
	while(!isempty())
	{
		trav = pop();
		if(trav->data == val)
			return trav;
		if(trav->right != NULL)
			push(trav->right);
		if(trav->left != NULL)
			push(trav->left);
	}
	return NULL;
}

NODE * BFS(int val)
{
	static NODE *trav;
	trav = root;
	insert(trav);
	while(!isemptyq())
	{
		trav = removeq();
		if(trav->data == val)
			return trav;
		if(trav->right != NULL)
			removeq(trav->right);
		if(trav->left != NULL)
			removeq(trav->left);
	}
	return NULL;
}

int level(int val)
{
	NODE * trav;
	int cnt = 0;
	trav = root;
	while(trav != NULL)
	{
		if(trav->data == val)
			return cnt;
		if(val < trav->data)
		{
			trav = trav->left;
			cnt++;
		}
		else
		{
			trav = trav->right;
			cnt++;
		}
	}
	return -1;
}

int height(NODE * trav)
{
	int htleft,htright;
	if(trav == NULL)
		return -1;
	htleft = height(trav->left);
	htright = height(trav->right);
	return ((htleft>htright?htleft:htright)+1);
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

NODE * searchnode(int val,NODE ** parent)
{
	NODE * trav;
	trav = root;
	while(trav != NULL)
	{
		if(trav->data == val)
			return trav;
		*parent = trav;
		if(val < trav->data)
			trav = trav->left;
		else
			trav = trav->right;
	}
	*parent = NULL;
	return NULL;
}

void deletenode(int val)
{
	NODE *temp,*parent;
	temp = searchnode(val,&parent);
	if(temp == NULL)
	{
		printf("\nNode not fount \n");
		return;
	}
	if(temp->left == NULL)
	{
		if(parent == NULL)
			root = temp->right;
		if(temp == parent->left)
			parent->left = temp->right;
		else
			parent->right = temp->right;
		free(temp);
	}
	if(temp->right == NULL)
	{
		if(parent == NULL)
			root = temp->left;
		if(temp == parent->right)
			parent->right = temp->left;
		else
			parent->left = temp->left;
		free(temp);
	}
	if(temp->left != NULL && temp->right != NULL)
	{
		NODE *succ;
		succ = temp->right;
		while(succ->left != NULL)
		{
			parent = succ;
			succ = succ->left;
		}
		parent->left = succ->right;
		temp->data = succ->data;
		temp = succ;
		free(temp);
	}
}

void main()
{
	NODE * temp;
	int n;
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
	addnode(78);
	temp = DFS(50);
	printf("\nAddress of 50 is (DFS) %u \n",temp);
	printf("\nInOrder - ");
	inorder(root);
	
	printf("\nPreOrder - ");
	preorder(root);
	printf("\n");

	temp = BFS(50);
	printf("\nAddress of 50 is (BFS) %u \n",temp);

	printf("\nLevel of 85 is %d \n",level(85));

	n = height(root);
	printf("\nHeight of Tree is %d \n",n);

	deletenode(70);

	printf("\nInOrder - ");
	inorder(root);
	printf("\n");

	FreeTree();
}
