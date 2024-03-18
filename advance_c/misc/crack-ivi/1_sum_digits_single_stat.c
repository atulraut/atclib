/***

    How can we sum the digits of a given number in single statement ?

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri 08 Mar 2024 06:29:15 PM PST
    Folsom, CA.
*/

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

void test() {
  int num=123456;
  int sum=0;
  for(; num>0; sum+=num%10,num/=10)
    ;
  // This is the "single line".
  printf("\nsum = [%d]\n", sum);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
