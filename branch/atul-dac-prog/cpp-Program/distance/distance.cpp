#include<stdio.h>
class distance
{
private :
	int feet;
	int inches;
public :
	distance()
	{
		feet = 0;
		inches = 0;
	}
	distance(int a, int b)
	{
		feet = a;
		inches = b;
	}	
	void input()
	{
		printf("\nEnter the  value for feet and inches:");
		scanf("%d%d", &feet, &inches);
	}
	void display()
	{
		printf("\nFeet = %d And Inches = %d\n", feet, inches);
	}
	void setfeet(int ft)
	{
		feet = ft;
	}
	int getfeet()
	{
		return feet;
	}
	void setinches(int inch)
	{
		inches = inch;
	}
	int getinches()
	{
		return inches;
	}
	distance sum(distance dist)
	{
		distance s;
		int a,b,total;
		a = (this->feet * 12) + this->inches;
		b = (dist.feet * 12) + dist.inches;
		total = a + b;
		s.feet = total/12;
		s.inches = total%12;
		return s;
	}
};

distance subtract(distance dist1, distance dist2)
{
	distance s;
	int c, d, total;
	c = (dist1.getfeet() * 12 ) + dist1.getinches();
	d = (dist2.getfeet() * 12 ) + dist2.getinches();
	total = c - d;
	s.setfeet(total/12);
	s.setinches(total%12);
	return s;
}

void main()
{
	distance d1, d2, d3;
	d1.input();
	d2.input();
	d3 = d1.sum(d2);
	printf("\nSum is :");
	d3.display();
	d3 = subtract(d1, d2);
	printf("\nSubtraction is :");
	d3.display();
}