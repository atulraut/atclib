/***
    Count numbers of Zero's in array without using
    comparison operators

    https://www.teksmart.in/search/label/C

    Date: 21 Sept 2021
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

int zeros_in_array(int a[] , int count) {
  int i, sum = 0 ;
  for (i =0 ; i < count ; i++) {
    sum+=!a[i];
  }
  return sum;
}

int non_zeros_in_array ( int a[] , int count) {
  int i, sum = 0 ;
  for (i =0 ; i < count ; i++) {
    sum+=!(!a[i]);
  }
  return sum;
}

int main (int argc, char **argv) {
  int ret = 0;
  int arry[] = {5,0,6,9,0,4,0,1,0,6};
  int num = 10; // Array values count

  ret = zeros_in_array(arry, num);
  debug("Zeros in array : %d", ret);

  ret = non_zeros_in_array(arry, num);
  debug("Zeros in array : %d", ret);

  return 0;
}

/**
   => ./a.out
   [main] L=38 :Zeros in array : 4
   [main] L=49 :Zeros in array : 6
**/
