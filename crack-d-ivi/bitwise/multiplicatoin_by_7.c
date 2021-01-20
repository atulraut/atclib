/*
* Program to multiplication by 7 using bitwise operator.
*/

#include<stdio.h>

void multiplication_by_7 (int x);
int multiply(int x, int y); 

int main() {
  multiplication_by_7(2);
  printf("\n %d \n", multiply(5, -11));
  return (0);
}

void multiplication_by_7 (int x) {
  int i;
  unsigned int y;
  for (i=1; i<=10; i++) {
    y = (i << 3) - (i << 0);
    printf ("\n Mul by 07 = ->[%d] ", y);
  }
  for (i=1; i<=10; i++) {
    y = (i << 3) + (i << 1);
    printf ("\n Mul by 10 = ->[%d] ", y);
  }
  x=1;
  printf ("\nx[0] = %d ", (x << 0));
  printf ("\nx[1] = %d ", (x << 1));
  printf ("\nx[2] = %d ", (x << 2));
  printf ("\nx[3] = %d ", (x << 3));
  printf ("\nx[4] = %d \n",(x << 4));
}

/*by geeksforgeeks.org function to multiply two numbers x and y*/
int multiply(int x, int y) {
  static int cnt;
  printf ("cnt =[%d] x = %d, y=%d \n", cnt, x, y);
  /* 0  multiplied with anything gives 0 */
  if(y == 0)
    return 0;
 
  /* Add x one by one */
  if(y > 0 )
    return (x + multiply(x, y-1));
  
  /* the case where y is negative */
  if(y < 0 )
    return -multiply(x, -y);
}
