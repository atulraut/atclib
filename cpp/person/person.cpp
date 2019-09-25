#include<iostream.h>
#include<string.h>
class date
{
	int day,month,year;
public :
	date()
	{
		day = 1;
		month = 1;
		year = 1;
	}
	date(int dd,int mm,int yy)
	{
		day = dd;
		month = mm;
		year = yy;
	}
	void input()
	{
		cout<<"Enter the date :";
		cin>>day>>month>>year;
	}
	void display()
	{
		cout<<"Date is :"<<day<<"-"<<month<<"-"<<year<<endl;
	}
};
class Person : public date
{
	char name[20];
	char email[20];
	date birthdate;
public:
	Person()
	{
		strcpy(name,"");
		strcpy(email,"");
	}
	Person(char *name,char *email,  
		int day,int month,int year) 
		:birthdate(day,month,year)
	{
		strcpy(this->name,name);
		strcpy(this->email,email);		
	}
	void input()
	{
		cout<<"Enter Name : ";
		cin>>name;
		cout<<"Enter Email : ";
		cin>>email;
		birthdate.input();
	}
	void display()
	{
		cout<<"Name: "<<name<<endl<<"Email: "<<email<<endl;
		birthdate.display();
	}
};
class Employee  :public Person
{
public :
	int empno;
	Employee()
	{
		empno = 0;
	}
	Employee(char *name,char *email,
		int day,int month,int year,
		int empno) 
		:Person(name, email, day,month, year)
	{
		empno = 1;
	}
	void input()
	{
		Person::input();
		cout<<"Enter Employee Number : ";
		cin>>empno;
	}
	void display()
	{
		Person::display();
		cout<<"Emplyee No: "<<empno<<endl;
	}
};
class Student  :public Person
{
	int rollno;
	int std;
	int marks;
public :
	Student()
	{
		rollno = 0;
		std = 0;
		marks = 0;
	}
	Student(char *name,char *email,
		int day,int month,int year, 
		int rlno,int st, int mrk) 
		:Person(name, email, day,month, year)
	{
		 rollno = rlno;
		 std = st;
		 marks = mrk ;
	}
	void input()
	{
		Person::input();
		cout<<"Enter Roll No.,Standard and Marks";
		cin>>rollno>>std>>marks;
	}
	void display()
	{
		Person::display();				
		cout<<"Roll No: "<<rollno<<endl<<"Standard : "<<std<<endl<<"Marks : "<<marks<<endl;
	}
};
class SalesPerson :virtual public Employee
{
	int totalsales;
	int commision;
public:
	SalesPerson()
	{
		totalsales = 0;
		commision = 0;
	}
	SalesPerson(char *name,char *email,
		int day,int month,int year,int empno, 
		int ts,int com)
		:Employee(name, email, day, month, year,empno)
	{
		totalsales = ts;
		commision = com;
	}
	void input()
	{
		Employee::input();
		cout<<"Enter Totalsales and Commision : ";
		cin>>totalsales>>commision;
	}
	void display()
	{
		Employee::display();
		cout<<"Totalsales :"<<totalsales<<endl<<"Commision : "<<commision<<endl;
	}
	void inputSalesPerson()
	{
		cout<<"Enter Totalsales and Commision : ";
		cin>>totalsales>>commision;
	}
	void displaySalesPerson()
	{
		cout<<"Totalsales :"<<totalsales<<endl<<"Commision : "<<commision<<endl;
	}
};

class Manager : virtual public Employee 
{
	int incentive;
	char dept[10];
public:
	Manager()
	{
		incentive = 0;
		strcpy(dept, "");
	}
	Manager(char *name,char *email,
		int day,int month,int year,
		int empno,int incen,char *dpt) 
		:Employee(name, email, day, month, year,empno)
	{
		incentive = incen;
		strcpy(dept, dpt);
	}
	void input()
	{
		Employee::input();
		cout<<"Enter Incentive and Department ";
		cin>>incentive>>dept;
	}
	void display()
	{
		Employee::display();
		cout<<"Incentive : "<<incentive<<endl<<"Department :"<<dept;
	}
	void inputManager()
	{
		cout<<"Enter Incentive and Department ";
		cin>>incentive>>dept;
	}
	void displayManager()
	{
		cout<<"Incentive : "<<incentive<<endl<<"Department :"<<dept;
	}
};

class SalesManager : public Manager ,public SalesPerson
{
public:
	0.




	SalesManager(char *name,char *email,
		int day,int month,int year,int empno,
		int ts,int com,int incen,char *dpt) 
		:Employee(name, email, day, month, year,empno),
		 Manager(name,email,day,month,year,empno,incen,dpt),
		 SalesPerson(name,email,day,month,year,empno,ts,com)
	{
	}
	void input()
	{
		Employee::input();
		SalesPerson::inputSalesPerson();
		Manager::inputManager();
	}
	void display()
	{
		Employee::display();
		SalesPerson::displaySalesPerson();
		Manager::displayManager();
	}
};



void main()
{
	/*Person p1("Samir Kadam","kadam.sam@gmail.com",22,06,1984);
	p1.display();
	Person p2("Atul Raut","atulraut17@gmail.com",17,10,1981);
	p2.display();*/

	SalesManager s1;
	s1.input();
	s1.display();
}