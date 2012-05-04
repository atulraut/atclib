#include<iostream.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

#define MAX 3

class Product
{
public:
	char name[20];
	int price;
	Product()
	{
		strcpy(name,"");
		price = 0;
	}
	Product(char *nm,int pr)
	{
		strcpy(name,nm);
		price = pr;
	}
	virtual void input()
	{
		cout<<"Enter the name :"; 
		cin>>name;
		cout<<"Enter the price : ";
		cin>>price;
	}
	virtual void display()
	{
		cout<<"Name : "<<name<<"Price : "<<price;
	}
	virtual ~Product()
	{
		cout<<"Destructor of Product \n";
	}
};

class Book : public Product
{

	int pages;
public: 
	Book()
	{
		pages = 0;
	}
	Book(char *nm,int pr,int pag):Product(nm,pr)
	{
		pages = pag;
	}
	void input()
	{
		Product::input();
		cout<<"Enter the pages : ";
		cin>>pages;
	}
	void display()
	{
		cout<<"Name : "<<name<<endl<<"Price : "<<price<<endl;
		cout<<"Pages : "<<pages<<endl;
	}
	~Book()
	{
		cout<<"Destructor of Book \n";
	}
};

class Tape : public Product
{
	int playtime;
public: 
	Tape()
	{
		playtime = 0;
	}
	Tape(char *nm,int pr,int play):Product(nm,pr)
	{
		playtime = play;
	}
	void input()
	{
		Product::input();
		cout<<"Enter the playtime : ";
		cin>>playtime;
	}
	void display()
	{
		cout<<"Name : "<<name<<endl<<"Price : "<<price<<endl;
		cout<<"playtime : "<<playtime<<endl;
	}
	~Tape()
	{
		cout<<"Destructor of Tape \n";
	}
};

void main()
{
	Product *ptr[MAX];
	int i,choice;
	for(i=0;i<MAX;i++)
	{
		system("cls");
		cout<<"Press \'1\' to purchase book "<<endl<<"Press \'2\' to purchase tape "<<endl;
		cout<<"Enter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1 :
				ptr[i] = new Book;
				ptr[i]->input();
				break;
			case 2 :
				ptr[i] = new Tape;
				ptr[i]->input();
				break;
			default :
				cout<<"You have entered wrong choice "<<endl;
				i--;
				getch();
		}
	}
	for(i=0;i<MAX;i++)
	{
		ptr[i]->display();
	}
	for(i=0;i<MAX;i++)
	{
		delete ptr[i];
	}
}