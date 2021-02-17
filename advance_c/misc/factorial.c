/*
3	3 × 2 × 1	= 3 × 2!	= 6
4	4 × 3 × 2 × 1	= 4 × 3!	= 24
*/
#include <stdio.h>

int fact (int n);

int main () { 
	int ret = 0;
	ret = fact (4);
	printf ("ret = %d \n", ret);
} 

int fact (int n) {
	int fac;
	if(n==1)
		return(1);
	else
		fac = n * fact(n-1);
	return (fac);
}
