/*
Will their be any compilation errors while trying to print the below?
     int *ptr=NULL;
     printf("%d",*ptr);
will their be any warning if yes when at compile time or run time?
O/P --> Run time Error, segmentation fault
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
  int *ptr=NULL;
  printf("\n ATUL = %d \n",*ptr);
  return 0;
}
