/*
 * Google: Check if two integers are equal without using any comparision
 * operators.
 * Date : 18/Jan/2020
 * Place : San Diego, CA, USA 
*/
#include <stdio.h>
#include <stdlib.h>

/* In case the return is 0 then the numbers are
   equal else not equal.
*/
int compare (int i, int j) {
  return i ^ j;
}

int main () {
  int i = 2;
  int j = 2;
  if(!compare(i,j))
    printf ("O/P -Number's are Equal\n ");
  else
    printf ("O/P -Number's are NOT Equal\n ");

}

