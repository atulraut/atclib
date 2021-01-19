/***
    Write code to sum 2 integer but u cant use a+b method,
    you have to use either ++ or --. How you will handle
    negative numbers.
*/
#include <stdio.h>
#define SQUARE(a) (a)*(a)

/***
    We can optimize this further by adding swap before the increment
    or decrement begins.
    To exemplify, imagine a = 100000, b = 1 ==> then we would increment
    b 100000 times, instead we can introduce a swap and instead
    increment a by 1.
*/
int sum(int a, int b) {
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
  if (b == 0)
    return a;
  else if (b > 0)
    return sumRecursive(++a, --b);
  else
    return sumRecursive(--a, ++b);
}

/*How can we get square of a number without using * or carrot sign.*/
int square(int num) {
  int i,sum=0,j=1;
  for(i=0;i<num;i++,j+=2)
    sum+=j;
  return sum;
}

int main() {
  printf("\n -> [%d] \n", SQUARE(4));
  int x = 3;
  printf("\n -> [%d] \n", SQUARE(++x));
  printf("\n -> [%d] \n", sum(-15,10));
  printf("\n -> [%d] \n", sumRecursive(-15,10));
}

/***
    => ./a.out
    -> [16]
    -> [25]
    2. a = -14, b = 9
    2. a = -13, b = 8
    2. a = -12, b = 7
    2. a = -11, b = 6
    2. a = -10, b = 5
    2. a = -9, b = 4
    2. a = -8, b = 3
    2. a = -7, b = 2
    2. a = -6, b = 1
    2. a = -5, b = 0
    2. a = -4, b = -1
    2. a = -3, b = -2
    2. a = -2, b = -3
    2. a = -1, b = -4
    2. a = 0, b = -5
    -> [-5]
    -> [-5]
*/
