#include <stdio.h>

int my_atoi (char s[]);

int main () {
  
  char *str = "Atul";
  int i = 5;
  i = my_atoi (str);
  printf ("\ni = %d\n", i);
}

/*my_atoi : convert s to integer; version 2*/
int my_atoi (char s[]) {
  printf ("s = %s", s);
}
