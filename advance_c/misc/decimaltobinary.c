/*
  Write a C program to convert a decimal number into a binary number.
*/
#include <stdio.h>

/*
  3 2 1 0 [Index]
  8 4 2 1 [Power]
  << ==   [Multiplication *]
  >> ==   [Divide  /]
  4 / 
*/
void generatebits(int num);

void generatebits(int num) {
	int temp;
	printf ("[%s] num = %d >> =  %d\n",__func__, num, (num >>1));
	if(num) {
		temp = num % 2;
		generatebits(num >> 1);
		printf("%d",temp);
	}
}

int main() {
	int num;
	printf("\nEnter a number\n");
	scanf("%d", &num);
	printf("\n\n");
	generatebits(num);
	return(0);
}
