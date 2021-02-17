#include <stdio.h>

int main () {
	int max, a, b, c;
	a = 10; b = 20; c = 15;

	max = ((a>b) ? ((a>c) ? a:c) : ((b>c) ? b:c));

	printf ("\n max = %d \n", max);

	max = ((a>b) ? a:b) > c ? ((a>b) ? a:b) : c;

	printf ("max = %d \n", max);
}
