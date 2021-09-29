/***
    Count the number of bits set in a floating
    point number?

    Date: 27 Sept 2021
    Fair Oaks, CA.
 */

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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

unsigned int countSetBitsChar(char n) {
  unsigned int count = 0;
  while (n) {
    n &= (n-1);
    count++;
  }
  return count;
}

// Returns set bits in binary representation of x
unsigned int countSetBitsFloat(float x) {
  // Count number of chars (or bytes) in binary representation of float
  unsigned int n = sizeof(float)/sizeof(char);

  // typecast address of x to a char pointer
  char *ptr = (char *)&x;

  int count = 0;   // To store the result
  for (int i = 0; i < n; i++) {
    count += countSetBitsChar(*ptr);
    ptr++;
  }
  return count;
}

int main() {
  float x1 = 0.15625;
  float x = 0.234;

  debug ("Binary representation of %f has %u set bits ", x,
	 countSetBitsFloat(x));
  return 0;
}

/**

 **/
