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
		if(rear ==MAX-1)
			printf("\nQueue is full \n");
		else
		{
			rear++;
			queue[rear] = val;
		}
	}

	int removeq()
	{
		int val;
		if(rear == front)
			printf("\nQueue is empty \n");
		else
		{
			front++;
			val = queue[front];
			return val;
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
	c2.insert(20);
	c1.insert(30);
	c2.insert(40);
	
	printf("\nValue of First queue : ");
	c1.display();
	printf("\nValue of Second queue : ");
	c2.display();
	
	val = c1.removeq();
	val = c2.removeq();

	printf("\nValue of First queue : ");
	c1.display();
	printf("\nValue of Second queue : ");
	c2.display();

	c1.insert(10);
	c2.insert(20);
	c1.insert(30);
	c2.insert(40);
	c1.insert(10);
	c2.insert(20);
	c1.insert(30);
	c2.insert(40);

	printf("\nValue of First queue : ");
	c1.display();
	printf("\nValue of Second queue : ");
	c2.display();
	printf("\n");
}