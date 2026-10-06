/***
 * Print 2D array using, given just pointer of 1st element of array.
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

int **getDynamicArray(int row, int col) {
  int i, j;
  int **ar;
  ar = (int **)malloc(row * sizeof(int *));
  for (i=0; i<row; i++)
    ar[i] = (int *)malloc(col * sizeof(int));
  printf ("In getDynamicArray \n");
  return ar;
}

/***
    M ATRIX -M ULTIPLY .A; B/
    1 if A:columns ¤ B:rows
    2    error “incompatible dimensions”
    3 else let C be a new A:rows * B:columns matrix
    4 for i = 1 to A:rows
    5     for j = 1 to B:columns
    6           c ij = 0
    7           for k = 1 to A:columns
    8              c-ij = c-ij + a-ik * b-kj
    9     return C
*/
int** array_multiplication (int (*a)[3], int (*b)[3], int row, int col) {
  int **c;
  if (row != col)
    debug("Incompatible dimensions");
  else {
    c = getDynamicArray(row, col);
    for (int i=0; i<row; i++) {
      for (int j=0; j<col; j++) {
	c[i][j] = 0;
	for (int k=0; k<col; k++) {
	  c[i][j] = c[i][j] + a[i][k] * b[k][j];
	}
      }
    }
  }
  return c;
}

int print_array (int *arr, int r, int c) {
  int i, j;
  debug("Enter !");
  for(i=0; i<3; i++) {
    for(j=0; j<3; j++) {
      printf ("--> %d \t", (*(arr+i) +j) );
    }
    arr++;
    arr++;
    printf ("\n");
  }
}

int main() {
    int arr[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,8},
    };
    int brr[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,8},
    };
    print_array (&arr[0][0], 3, 3);

    int **retC = array_multiplication(arr, arr, 3, 3);
    print_array (&retC[0][0], 3, 3);
    return 0;
}

/***
    => ./a.out
    --> 1 	--> 2 	--> 3
    --> 4 	--> 5 	--> 6
    --> 7 	--> 8 	--> 9
*/
