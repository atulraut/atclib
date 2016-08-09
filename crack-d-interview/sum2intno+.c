/*
Write code to sum 2 integer but u cant use a+b method, 
you have to use either ++ or --. How you will handle negative numbers.
*/
#include <stdio.h>
#define SQUARE(a) (a)*(a)

int sum(int a, int b);
int sumRecursive(int a, int b);

int main() {
  printf("\n -> [%d] \n", SQUARE(4));
  int x = 3;
  printf("\n -> [%d] \n", SQUARE(++x));
  printf("\n -> [%d] \n", sum(-15,10));
  printf("\n -> [%d] \n", sumRecursive(-15,10));
}

/*
We can optimize this further by adding swap before the increment or decrement begins. 
To exemplify, imagine a = 100000, b = 1 ==> then we would increment b 100000 times, instead we can introduce a swap and instead increment a by 1.
*/
int sum(int a, int b){
  if(a > b) {
    int temp = a;
    a = b;
    b = temp;
  }
  while(a > 0) { 
    --a; ++b;
    printf ("1. a = %d, b = %d\n", a, b);
  };
  while(a < 0) { 
    ++a; --b; 
    printf ("2. a = %d, b = %d\n", a, b);
  };
  return b;
}

/* Recursive version */ 
int sumRecursive(int a, int b) {
  if (b == 0) return a;
  else if (b > 0) return sumRecursive(++a, --b);
  else return sumRecursive(--a, ++b);
}

/*How can we get square of a number without using * or carrot sign.*/
int square(int num){
	
	int i,sum=0,j=1;
	for(i=0;i<num;i++,j+=2)
		sum+=j;
	return sum;
}
