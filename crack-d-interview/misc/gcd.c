#include <stdio.h>

// Iterative algorithm
int gcd(int a, int b) {
	int temp;
	while(b) {
		temp = a % b;
		printf ("-->%d\n", temp);
		a = b;
		b = temp;
	}
	return(a);
}

/* Recursive algorithm */
int gcd_recurse(int a, int b) {
	int temp;
	temp = a % b;
	if (temp == 0) {
		return(b);
	} else {
		return(gcd_recurse(b, temp));
	}
}

int check1LinePwrOf2(int num) {

	printf ("-> %d \n", !(num & num-1));
	printf ("-> %d \n", (!(num & num-1) && num));
	
	if(!(num & (num - 1)) && num) {
		printf ("is power of 2 \n");
        } else
		printf ("is !power of 2 \n");
}
int main() {
//   check1LinePwrOf2(4);
//	printf ("--> %d\n", gcd (12, 4));
	printf ("--> %d\n", gcd (4, 12));
}

