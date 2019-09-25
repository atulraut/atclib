#include<stdio.h>
#include<stdlib.h>

#define MAX 5

class Cqueqe
{
private :
	int queue[MAX];
	int front ,rear;
public :

	Cqueqe()
	{
		front = -1;
		rear = -1;
	}
	void insert(int val)
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

	int removeq()
	{
		int val;
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

	void display()
	{
		int i;
		for(i=front+1; i<=rear; i++)
			printf("  %d",queue[i]);
	}
};
void main()
{
	Cqueqe c1, c2; 
	int val;
	c1.insert(10);
	printf("\nValue inserted is 10 \n");
	c2.insert(20);
	printf("\nValue inserted is 20 \n");
	c1.insert(30);
	printf("\nValue inserted is 30 \n");
	c2.insert(40);
	printf("\nValue inserted is 40 \n");
	printf("\nValue of First queue : ");
	c1.display();
	printf("\nValue of Second queue : ");
	c2.display();
	val = c1.removeq();
	printf("\nValue removed is %d \n",val);
	val = c2.removeq();

	printf("\nValue of First queue : ");
	c1.display();
	printf("\nValue of Second queue : ");
	c2.display();

/*	printf("\nValue removed is %d \n",val);
	val = removeq();
	printf("\nValue removed is %d \n",val);
	val = removeq();
	printf("\nValue removed is %d \n",val);*/
}