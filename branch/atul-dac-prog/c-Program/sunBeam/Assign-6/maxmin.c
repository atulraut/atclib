#include<stdio.h>

void maxmin(int *p)
{
	int i,max=*p,min=*p;
	for(i=1;i<10;i++)
	{
		if(*(p+i)>max)
			max = *(p+i);
		if(*(p+i)<min)
			min = *(p+i);
	}
	printf("\nMinimum = %d and Maximum = %d \n",min,max);
}