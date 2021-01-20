/*
 * Copying a 4 element character array into an integer in C
*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MAX 2
#define SZ  6

union {
  char str[4];
  unsigned int ui;
} u;

int main() {
  int i, j;
  int arr[2][5] = {
    {11111234,11111235, 3, 4, 5},
    {11111236,11111237, 6, 7, 8},
  };
  char crr[2][5] = {
    {"Atul"},
    {"Raut"}
  };
  for (i=0; i<2; i++) {
    for (j=0; j<4; j++) {
      printf("I/P -crr[%d][%d] ->[%c] crr->[%p] arr->[%p]\n", i,j, crr[i][j], (*(crr + i) + j), (*(arr + i) + j));
    }
  }
  for (i=0; i<2; i++) {
    for (j=0; j<4; j++) {
      //      printf("arr ->[%08X]  ", *(*(arr + i) + j));
      printf ("crr[%d][%d] crr ->[%c] crr ->[%p], val=%c \n",i,j, crr[i][j], (*(crr + i) + j), *(*(crr + i) + j) );
      memcpy((*(arr + i) + j), (*(crr + i) + j), sizeof(char));
      printf("RAJ arr[%d][%d]->[%c] \n",i,j, arr[i][j]);
    }
    printf("MEET arr[%d][%d]->[%c] \n",i,j, arr[i][j]); 
  }
  printf("RAJ ->[%c] \n", arr[0][2]);
  for (i=0; i<2; i++) {
    for (j=0; j<4; j++) {
      printf("O/P -arr[%d][%d] ->[%c] ->[%p]\n", i,j, arr[i][j], (*(arr + i) + j));
    }
  }
  return 0;
}
