#include<stdio.h>
#include<iostream.h>
class array
{
private :
	int *ptr;
	int size;
public :
	int getat(int);
	void setat(int, int);
	array(int);
	void display();
	void input();
	int getsize();
	void sort();
};
array::array(int size)
{
	this->size = size;
	ptr = new int[size];		
}
int array::getat(int index)
{
	if(index < 0 || index > size)
		return 0;
	else
		return *(ptr + index);
}
void array::setat(int index, int val)
{
	if(index < 0 || index > size)
		cout<<"You have enter wrong index"<<endl;
	else
		*(ptr + index) = val;
}

void array::input()
{
	int i;
	cout<<"Enter the element of Array :";
	for(i=0; i<size; i++)
		cin>>*(ptr+i);
}
void array::display()
{
	int i;
	cout<<"Element of the array are :";
	for(i=0; i<size; i++)
		cout<<" "<<*(ptr + i);
	cout<<endl;
}
void array::sort()
{
	int i, j, temp;
	cout<<"After sorting :"<<endl;
	for(i=0; i<size; i++)
	{
		for(j=i+1; j<size; j++)
		{
			if(*(ptr + i) > *(ptr + j))
			{
				temp = *(ptr + i);
				*(ptr + i)	= *(ptr + j);
				*(ptr + j)	= temp;
			}
		}
	}
}

int array::getsize()
{
	return size;
}

void main()
{
	int val;
	array arr1(5);
	arr1.input();
	val = arr1.getsize();
	cout<<"Size of Array is :"<<val<<endl;
	arr1.display();
	arr1.setat(3, 90);
	arr1.display();
	val = arr1.getat(2);
	if(val != 0)
		cout<<"Element at Index 2 is :"<<val<<endl;
	else
		cout<<"You have entered incorrect Index"<<endl;
	arr1.sort();
	arr1.display();
}
