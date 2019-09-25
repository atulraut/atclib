#include<iostream.h>

int sum(int a,int b,int c=0,int d=0,int e=0);

void main()
{
	int a=10,b=12,res;
	res = sum(a,b,10,20);
	cout<<res<<endl;
}

int sum(int a,int b,int c,int d,int e)
{
	return a+b+c+d+e;
}