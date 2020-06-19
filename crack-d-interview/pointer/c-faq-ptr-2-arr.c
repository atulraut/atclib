#include <stdio.h>
#include <stdlib.h>

int a1[3] = {0, 1, 2};
int a2[2][3] = {{3, 4, 5}, {6, 7, 8}};
int *ip;/* pointer to int */
int (*ap)[3];/* pointer to array [3] of int */

// you could use the simple pointer-to-int, ip, to access the
// one-dimensional array a1:

int main () {
  ip = a1;
  printf("*ip =  %d \n", *ip);
  ip++;
  printf("*ip = %d \n", *ip);

  // This fragment would print
  // 0 1
  // An attempt to use a pointer-to-array, ap, on a1:

  ap = &a1;
  printf("--> **ip = %d \n", **ap);
  ap++;/* WRONG */
  printf("**ap %d \n", **ap);/* undefined */
  /*** would print 0 on the first line and something undefined on the
   * second (and might crash). The pointer-to-array would only be at
   * all useful in accessing an array of arrays, such as a2:
  */

  ap = a2;
  printf(" (*ap)[0] =  %d (*ap)[1] =  %d\n", (*ap)[0], (*ap)[1]);
  ap++;/* steps over entire (sub)array */
  printf(" (*ap)[0] =  %d (*ap)[1] =  %d\n", (*ap)[0], (*ap)[1]);

  //This last fragment would print
  // 3 4
  // 6 7
}
