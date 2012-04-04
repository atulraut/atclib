/*
* Aim : Initialization of Pointer to Arrays.
* Auther : Atul Ramesh Raut
* Date   : Tuesday April 03, 2012. 09:45PM
***/

#include <stdio.h>
#include <stdlib.h>

char *month_name (int n);

int main () {
  char *str;
  str = month_name (2);
  printf ("\nMonth is = %s\n", str);
  return 0;
}

/* month_name : return name of n-th month */
char *month_name (int n) {
    static char *name [] = {
    "Illegal month",
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "Octomber", "November", "December" 
  };
  printf ("\n Month = %s , n = %d\n", name [1], n);
  return (n < 1 || n > 12) ? name[0] : name [n];
} 
