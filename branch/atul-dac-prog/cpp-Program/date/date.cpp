#include<iostream.h>
#include<stdlib.h>
#include<conio.h>
class date
{
private :	
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
	void setday(int d1)
	{
		if(!checkday(d1))
			cout<<"Invalid Day"<<endl;
		else
			day = d1;
	}
	void setmonth(int m1)
	{
		if(m1>0 && m1<=12)
			month = m1;
		else
			cout<<"Invalid Month "<<endl;
	}
	void setyear(int y1)
	{
		if(y1>0)
			year = y1;
		else
			cout<<"Invalid Year"<<endl;

	}
	int getday()
	{
		return day;
	}
	int getmonth()
	{
		return month;
	}
	int getyear()
	{
		return year;
	}
	int checkday(int d1)
	{
		if(month==1 ||month==3 ||month==5 ||month==7 ||month==8 ||month==10 ||month==12 )
		{
			if(d1 > 31)
				return 0;
			else
				return 1;
		}
		else if(month==4 ||month==6 ||month==9 ||month==11)
		{
			if(d1 > 30)
				return 0;
			else
				return 1;
		}
		else
		{
			if(year%400==0 ||( year%4==0 && year%100!=0))
			{
				if(d1 > 29)
					return 0;
				else
					return 1;
			}
			else
			{
				if(d1 > 28)
					return 0;
				else
					return 1;
			}
		}
	}
	void input()
	{
		int flag=0;
		do
		{
			system("cls");
			if(flag==0)
			{
				cout<<"Enter the date : "<<endl;
				cin>>day>>month>>year;
			}
			else
			{
				cout<<"Please enter the correct date : "<<endl;
				cin>>day>>month>>year;
			}
			flag++;
		}while(!this->isvalid());
	}
	void display()
	{
		cout<<"Date is"<<day<<"-"<<month<<"-"<<year<<endl;
	}
	int isvalid()
	{
		if(month==1 ||month==3 ||month==5 ||month==7 ||month==8 ||month==10 ||month==12 )
		{
			if(day > 31)
				return 0;
			else
				return 1;
		}
		else if(month==4 ||month==6 ||month==9 ||month==11)
		{
			if(day > 30)
				return 0;
			else
				return 1;
		}	
		else if(month == 2)
		{
			if(year%400==0 ||( year%4==0 && year%100!=0))
			{
				if(day > 29)
					return 0;
				else
					return 1;
			}
			else
			{
				if(day > 28)
					return 0;
				else
					return 1;
			}
		}
		else
			return 0;
	}
	date operator++(int)
	{
		date d;
		if(month==1 ||month==3 ||month==5 ||month==7 ||month==8 ||month==10 ||month==12 )
		{
			if(day == 31)
			{
				d.day = 1;
				d.month = month+1;
				d.year = year;
			}
			else
			{
				d.day = day+1;
				d.month = month;
				d.year = year;
			}
		}
		else if(month==4 ||month==6 ||month==9 ||month==11)
		{
			if(day == 30)
			{
				d.day = 1;
				d.month = month;
				d.year = year;
			}
			else
			{
				d.day = day+1;
				d.month = month;
				d.year = year;
			}
		}	
		else
		{
			if(year%400==0 || ( year%4==0&&year%100!=0))
			{
				if(day == 29)
				{
					d.day = 1;
					d.month=month+1;
					d.year = year;
				}
				else
				{
					d.day = day+1;
					d.month = month;
					d.year = year;
				}
			}
			else
			{
				if(day == 28)
				{
					d.day = 1;
					d.month=month+1;
					d.year = year;
				}
				else
				{
					d.day = day+1;
					d.month = month;
					d.year = year;
				}
			}
		}
		if(d.month == 13)
		{
			d.month = 1;
			d.year=year+1;
		}
		return d;
	}
	date operator--(int)
	{
		date d;
		if(month==5 ||month==7 ||month==10 ||month==12 )
		{
			if(day == 1)
			{
				d.day = 30;
				d.month=month-1;
				d.year = year;
			}
			else
			{
				d.day=day-1;
				d.month = month;
				d.year = year;
			}
		}
		else if(month==1 ||month==2 ||month==4 ||month==6 ||month==8 ||month==9 ||month==11)
		{
			if(day == 1)
			{
				d.day = 31;
				d.month=month-1;
				d.year = year;
			}
			else
			{
				d.day=day-1;
				d.month = month;
				d.year = year;
			}
		}	
		else
		{
			if(year%400==0 || ( year%4==0&&year%100!=0))
			{
				if(day == 1)
				{
					d.day = 29;
					d.month=month-1;
					d.year = year;
				}
				else
				{
					d.day=day-1;
					d.month = month;
					d.year = year;
				}
			}
			else
			{
				if(day == 1)
				{
					d.day = 28;
					d.month=month-1;
					d.year = year;
				}
				else
				{
					d.day=day-1;
					d.month = month;
					d.year = year;
				}
			}
		}
		if(d.month == 0)
		{
			d.month = 12;
			d.year = year-1;
		}
		return d;
	}
	void swap(date *d1)
	{	
		date temp;
		temp = *d1;
		*d1 = *this;
		*this = temp; 
	}
};



void main()
{
	date d1,d2,d3;
	d1.input();
	d3 = d1++;
	d3.display();
	d3 = d1--;
	d3.display();
/*	d3 = d1.nextdate();
	cout<<"Next ";
	d3.display();
	d3 = d1.prevdate();
	cout<<"Previous ";
	d3.display();
	getch();
	d2.input();
	d2.setday(29);
	d2.display();*/
	

/*	d1.swap(&d3);
	cout<<"Date of d1 : ";
	d1.display();
	cout<<"Date of d2 : ";
	d3.display();*/
}