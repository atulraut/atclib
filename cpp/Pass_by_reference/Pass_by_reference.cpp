#include<stdio.h>
#include<iostream.h>
class array
{
	int *ptr;
	int size;
public :	
	int& operator[](int);
	array(int);
	array(const array& arr);
	void operator=(array& pq);
	void display();
	void input();
	int getsize();
	friend void sort(array& aa);
	~array();
};
array::array(int size)/* Parametrized Constructor */
{
	this->size = size;
	ptr = new int[size];
	for(int i=0;i<size;i++)
		ptr[i] = 0;
}
array::array(const array& other)/* Parametrized Constructor */
{
	size = other.size;
	ptr = new int[size];
	for(int i=0;i<size;i++)
		ptr[i] = other.ptr[i];
}
void array::operator=(array& arr1)
{
	this->size = arr1.size;
	delete[] ptr;
	ptr  = new int[size];
	for(int i=0; i<size; i++)
		ptr[i] = arr1.ptr[i];
}
/*int array::operator[](int index)
{
	if(index < 0 || index > size)
		return 0;
	else
		return ptr[index];
}*/
int& array::operator[](int index)
{
	if(index < 0 || index > size)
		cout<<"Wrong index"<<endl;
	else
		return ptr[index];
		
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
int array::getsize()
{
	return size;
}
array::~array()
{
	delete[] ptr;
}

void sort(array& aa)
{
	int i, j, temp;
	cout<<"After sorting :"<<endl;
	for(i=0; i<aa.size; i++)
	{
		for(j=i+1; j<aa.size; j++)
		{
			if(aa.ptr[i] > aa.ptr[j])
			{
				temp = aa.ptr[i];
				aa.ptr[i]	= aa.ptr[j];
				aa.ptr[j]	= temp;
			}
		}
	}
}

void main()
{
	//int val;
	array arr1(5);
	arr1.input();
	/*val = arr1.getsize();
	cout<<"Size of Array is :"<<val<<endl;
	arr1.display();
	arr1.setat(3, 90);
	arr1.display();
	val = arr1.getat(2);
	if(val != 0)
		cout<<"Element at Index 2 is :"<<val<<endl;
	else
		cout<<"You have entered incorrect Index"<<endl;
	sort(arr1);
	array aa(arr1);*/

/*	array aa(10);
	aa = arr1;
	arr1.display();
	aa.display();*/

	int num = 100;
	arr1[2] = num;
	arr1.display();
	//cout<<"Num :"<<num;
}
