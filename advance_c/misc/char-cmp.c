#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main () {
  int i=0;
  char arr[4] = {
    'a', 'b', 'c', 'd'
  };
  char str1 = 'A';
  char str2 = 'Z';
  char str3 = 'a';
  char str4 = 'z';
  i = atoi (&str1);
  //i = strcmp (str1, str2);
  printf ("\ni = %d str1=%d, str2=%d\n", i, str1, str2);
  printf ("\nstr3=%d, str4=%d\n", str3, str4);
  
  if (str1 == str2)
    printf ("\nIsEqual = \n");
  else if (str1 > str2)
    printf ("\nIs  > \n");
  else
    printf ("\nIs < \n");
  for (i=0; i<4; i++) {
    if (arr[i] == str2)
      printf ("\nIsEqual = \n");
    else if (str1 > str2)
      printf ("\nIs  > \n");
    else
      printf ("\nIs < \n");
  return 0;
}
