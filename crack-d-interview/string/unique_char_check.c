/*
  Implement an algorithm to determine if a string has all unique characters. What if
  you can not use additional data structures?
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_unique_character(char *str) {
  int i;
  int isPresentstr[256] = {0};
  int len = strlen (str);
  for (i=0; i<len; i++) {
    if (++isPresentstr[str[i]] >=2)
      return 1;
  }
  return 0;
}

/* without using extra buffer */
int check_unique_character2(char *str) { 
  int checker = 0;
  int i, val;
  int len = strlen (str);	
  for (i=0; i<len; ++i) {		
    val = (str[i] - 'a');
    printf ("->str[i]=%c val=%d <<=%d\n", str[i], val, (1<<val));
    printf ("Ret = %d \n", (checker & (1 << val)));  
    if ((checker & (1 << val)) > 0)
      return 1;		
    checker |= (1 << val); // set bit val
    printf ("check-%d\n", checker);
  }
  return 0;
}

int main () {
  char a[] = "atull";
  int c = check_unique_character(a);
  if (c) {
    printf ("Not all Unique \n");
  } else
    printf ("All Unique \n");
}
