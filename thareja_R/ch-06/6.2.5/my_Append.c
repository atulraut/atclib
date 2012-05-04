/*
* Aim    : WAP Appeding S1 String to S2 String. S2 = S2 + S1;
* Date   : 30-04-2012
* Author : Atul Ramesh Raut
*
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * my_strCpy (char *, char *);

int main () {
  char s1[] = "Atul ";
  char s2[] = "Raut ";

  my_strCpy (s1, s2);
  //printf ("\n newString = %s \n", newString);
}

char * my_strCpy (char *s1, char *s2) {
  printf ("\n newString s1 = %s s2=  %s\n", s1, s2);
  int m=0, n=0;
  while (s2[m] != '\0') {
    m++;
  }
  
  while (s1[n] != '\0') {
    s2[m] = s1[n];
    m++;
    n++;
  }

  s2[m] = '\0';
  printf ("\n newString = %s\n", s2);

  return 0;
}

