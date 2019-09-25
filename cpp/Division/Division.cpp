#include<iostream.h>
class MyException
{
private :
	int num1, num2;
public :
	MyException();
	void input();
	void display();
	void divide();
};
MyException::MyException()
{
	num1 = 0;
	num2 = 0;
}
void MyException::input()
{
	cout<<"Enter two numbers : "<<endl;
	cin>>num1>>num2;
}
void MyException::divide()
{
	if( this->num2 == 0)
		throw(0);
	else
		cout<<"Division is :"<<num1/num2<<endl;
}
void main()
{
	MyException d1;
	d1.input();
	try
	{
		d1.divide();
	}
	catch(int )
	{
		cout<<"Division by zero is not possible "<<endl;
	}
}

