/*
 * String Revese Routine
   1. In place String Reverse
   2. String Reverse using Recursive.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  In Place String Reverse 
*/
void reverse(char *str) {
  char * end = str;
  char tmp;

  if (str) {
    while (*end) {
      ++end;
    }
    --end;
    while (str < end) {
      tmp = *str;
      *str++ = *end;
      *end-- = tmp;
    }
  }
}

char* string_reverse(char *str) {
  int i, j;
  char temp;
  int len = strlen(str);
  for(i=0,j=len-1; i<j; ++i, --j) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
  return str;
}

/*
  Recursive String Reverse
*/
void str_rev(char *str, int index, int last) {
  int temp;

  if (index > last)
    return;
  temp = str[index];
  str[index] = str[last];
  str[last] = temp;
  str_rev(str, ++index, --last);
}

int main() {
  char st[] = "Atul Ram";
  char *t = string_reverse(st);
  printf ("--> %s\n", t);
  int len = strlen(st);
  str_rev(t, 0, len-1);
  printf ("--> %s\n", st);
}

/*
  O/P :
  --> maR lutA
  --> Atul Ram
*/
