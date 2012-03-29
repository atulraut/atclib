
 /*
* Write a function any(s1, s2), which returns the first location
* in the string s1 where any character from the string s2 occurs,
* or -1 if s1 contains no characters from s2. (The standards library function strpbrk does
* the same job but returns a pointer to the location.)
* Date : Sunday July 24 2011 7:00PM
***/

#include <stdio.h>

char any (char [], char[]);

int main () {
  char ch;
  char s1[] = "Atul";
  char s2[] = "Raut";
  ch = any (s1, s2);
  printf ("\ns1 = %c\n\n", ch);

  return 0;
}

char any (char s1[], char s2[]) {
  int i, j;
  for (i=0; s1[i] != '\0'; i++) {
   for (j=0; s2[j] != '\0'; j++) {
     if  (s1[i] == s2[j]) {        /* Match found */
       return s1[i];               /* Location first match */
      } // if loop                
      ++i;
   } // 2nd while
  } // 1st while

  return -1;
}
