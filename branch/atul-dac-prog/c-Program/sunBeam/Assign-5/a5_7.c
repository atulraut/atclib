#include<stdio.h>
#include<conio.h>
int fact(int);
int main()
{
	int n, ibm;
	printf("Enter the no. :");
	scanf("%d",&n);
	ibm = fact(n);
	printf("%d\n",ibm);
}
 int fact(int p)
 {
	int a;
	if(p == 1)
		return 1;	
	a = p * fact(p - 1);
	return(a);
 }