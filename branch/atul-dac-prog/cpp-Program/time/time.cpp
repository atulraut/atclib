#include<stdio.h>

class time
{
private :	
	int hour,minute,second;
public :
	time()
	{
		hour = 0;
		minute = 0;
		second = 0;
	}
	time(int dd,int mm,int yy)
	{
		hour = dd;
		minute = mm;
		second = yy;
	}
	void sethour(int t1)
	{
		if(t1 < 0 || t1 >23)
			printf("\nInvalid Time");
		else
		hour = t1;
	}
	void setminute(int m1)
	{
		if(m1 < 0 || m1 >59)
			printf("\nInvalid Time");
		else
		minute = m1;
	}
	void setsecond(int s1)
	{
		if(s1 < 0 || s1 > 59)
			printf("\nInvalid Time");
		else
		second = s1;
	}
	int gethour()
	{
		return hour;
	}
	int getminute()
	{
		return minute;
	}
	int getsecond()
	{
		return second;
	}
	void input()
	{
		printf("\nEnter the time : ");
		scanf("%d%d%d",&hour,&minute,&second);
	}
	void display()
	{
		printf("\n%d-%d-%d\n",hour,minute,second);
	}
	int isvalid()
	{
		if(hour > 23 || minute > 59 || second > 59)
			return 0;
		else
			return 1;
	}
};


void main()
{
	time t1;
	t1.input();
	if(t1.isvalid())
	{
		printf("\nValid Time \n");
	}
	else 
		printf("\nInvalid time \n");
}