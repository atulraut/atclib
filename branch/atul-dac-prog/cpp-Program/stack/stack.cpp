#include <stdio.h>
#include<iostream.h>
class stack
{
private :
		int size;
		int *arr;
		int top;
public :
	stack(int size)
	{
		this->size = size;
		top = -1;
		arr  = new int[size];
	}
	~stack()
	{
		delete[] arr;

	}
	void push(int val);
	int pop();
	int topele();
	int isEmpty();
	int isFull();
	void display();
};
	void stack::push(int val)
	{
		if(top==size-1)
			cout<<"Stack is full"<<endl;
		else
		{
			top++;
			arr[top]=val;
		}
	}
	int stack::pop()
	{
		int val=0;
		if(top==-1)
		{
			cout<<"Stack is empty "<<endl;
		}
		else
		{
			val = arr[top];
			top--;
		}
		return val;
	}
	int stack::topele()
	{
		return arr[top];
	}
	int stack::isEmpty()
	{
		if(top==-1)
			return 1;
		else
			return 0;
	}
	int stack::isFull()
	{
		if(top==size-1)
			return 1;
		else
			return 0;
	}
	void stack::display()
	{
		int i;
		for(i=top; i>=0; i--)
			cout<<arr[i]<<endl;
	}

void main()
{
	stack s1(5),s2(3);
	int val;
	s1.push(10);
	s1.push(20);
	
	s2.push(30);
	s2.push(40);
	
	cout<<"Value of First stack : "<<endl;
	s1.display();
	cout<<"Value of Second stack : "<<endl;
	s2.display();

	val = s1.pop();
	val = s2.pop();

	cout<<"Value of First stack : "<<endl;
	s1.display();
	cout<<"Value of Second stack : "<<endl;
	s2.display();
}
