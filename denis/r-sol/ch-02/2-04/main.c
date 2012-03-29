/*
* Write a program squeeze(s1, s2) that delets each character in s1 that matches
* any character in the string s2.
* Date : Sunday July 24 2011, -05:52PM
*
***/

#include <stdio.h>

int sqeeze (char [], char[]);

int main () {
  int n;
  n = 0;
  char s1[] = "Atul";
  char s2[] = "Raut";
  n = sqeeze (s1, s2);
  printf ("\ns1 = %s\n\n", s1);
  return 0;
}

int sqeeze (char s1[], char s2[]) {
  int i, j, n, k;
  i = 0; 
  j = 0;
  n = 0;
  k = 0;
  for (i=0; s1[i] != '\0'; i++) {
   for (j=0; s2[j] != '\0'; j++) {
      if  (s1[i] == s2[j])
	++i;
      ++j;
   }
   s1[k] = s1[i];
   ++k;
   ++i;
  }
  s1[k] = '\0';
  return 1;
}
