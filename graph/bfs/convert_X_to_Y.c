/***
    https://www.geeksforgeeks.org/minimum-steps-to-convert-x-to-y-by-repeated-division-and-multiplication/

    Minimum steps to convert X to Y by repeated division and multiplication

    Given two integers X and Y, the task is to find the minimum number of steps
    to convert integer X to Y using any of the operations in each step:

    Divide the number by any natural number
    Multiply the number with any natural number

    Input: X = 8, Y = 12
    Output: 2
    Explanation:
    First divide 8 by 2: 8/2 = 4
    Then multiply by 3: 4*3 = 12

    Input: X = 4, Y = 8
    Output: 1
    Explanation:
    To convert 4 to 8 multiply 4 by 2: 4 * 2 = 8

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon 08 Apr 2024 08:34:40 PM PDT
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

int solve(int X, int Y) {
  // Check if X is greater than Y
  // then swap the elements
  if (X > Y) {
    int temp = X;
    X = Y;
    Y = temp;
  }

  // Check if X equals Y
  if (X == Y)
    debug("Ouput = [1]");

  else if (Y % X == 0)
    debug("Ouput = [1]");
  else
    debug("Ouput = [2]");
}

void test() {
  //  int X = 8, Y = 13;
  int X = 2;
  int Y = 5;
  solve(X, Y);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
