#include<iostream.h>
#include<stdlib.h>
#include<conio.h>

class  Shape
{
public :

	virtual void input() = 0;
	virtual double  Area() =0 ;
	virtual double  Perimeter() = 0;
};

class Circle : public Shape
{
	int rad;
public :	
	Circle()
	{
		rad = 0;
	}
	Circle(int R)
	{
		this->rad = R;
	}
    void input()
	{
		cout<<"Enter Radius of the Cirlce"<<endl;
		cin>>rad;
	}
	double Area()
	{
		return (3.14 * rad * rad) ;
	}
	double Perimeter()
	{
		return (2 * 3.14 * rad);
	}
	~Circle()
	{
		cout<<"Destructor of Circle \n";
	}
};

class  Rectangle : public Shape
{
private :
		int Length;
		int Breadth;
public :
		Rectangle()
	{
		Length = 0;
		Breadth = 0;
	}
	Rectangle(int Len, int Bre)
	{
		Length = Len;
		Breadth = Bre;
	}
	void input()
	{
		cout<<"Enter the Length and breadth for Rectangle"<<endl;
		cin>>Length>>Breadth;
	}
	double Area()
	{
		return (Length * Breadth) ;
	}
	double  Perimeter()
	{
		return (2 * (Length + Breadth));
	}
	~Rectangle()
	{
		cout<<"Destructor of Rectangle \n";
	}
};
void main()
{
	Shape *ptr;
	int choice;
	double area,perimeter;
	while(1)
	{
		system("cls");
		cout<<"Press \'1\' for Circle "<<endl<<"Press \'2\' for Rectangle "<<endl<<"Press \'0\' for Exit "<<endl;
		cout<<"Enter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1 :
				ptr = new Circle;
				ptr->input();
				area = ptr->Area();
				perimeter = ptr->Perimeter();
				cout<<"Area of Circle is "<<area<<endl;
				cout<<"Perimeter of Circle is "<<perimeter<<endl;
				delete ptr;
				break;
			case 2 :
				ptr = new Rectangle;
				ptr->input();
				area = ptr->Area();
				perimeter = ptr->Perimeter();
				cout<<"Area of Rectangle is "<<area<<endl;
				cout<<"Perimeter of Rectangle is "<<perimeter<<endl;
				delete ptr;
				break;
			case 0 :
				exit(0);
			default :
				cout<<"You have entered wrong choice "<<endl;
		}
		getch();
	}
}












