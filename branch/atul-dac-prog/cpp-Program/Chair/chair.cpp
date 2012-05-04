#include<stdio.h>
#include<string.h>
class chair 
{
private :
	int height, weight;
	char colour[10];

public :
	static int price;
	chair()
	{
		height = 0;
		weight = 0;
		strcpy(colour,"");
	}
	chair(int height, int weight, char *colour)
	{
		this->height = height;
		this->weight = weight;
		strcpy(this->colour,colour);
	}
	void setprice(int price)
	{
		this->price = price;
	}
	static int getprice()
	{
		return price;
	}
	void setheight(int height)
	{
		this->height= height;
	}
	int getheight()
	{
		return height;
	}
	void setweight(int weight)
	{
		this->weight = weight;
	}
	int getweight()
	{
		return weight;
	}
	void setcolour(char *colour)
	{
		strcpy(this->colour,colour);
	}
	char * getcolour()
	{
		return colour;
	}
	void display()
	{
		printf("\nPrice= %d\nHeight= %d\nWeight= %d\nColour= %s\n",price,height,weight,colour);
	}
};
int chair::price = 200;
void main()
{	
//	chair c1;
	chair c2(12,45,"Red");
//	chair::price = 300;
	printf("\nData of c2 ");
	c2.display();
//	printf("\nPrice = %d\n",chair::price);
//	c1.setheight(50);
//	printf("\nHeight = %d\n",c2.getheight());
//	printf("\nData of c1");
//	c1.display();
}