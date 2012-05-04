/*
* Aim    : WAP Concating Two String to Form a New String using Malloc.
* Date   : 30-04-2012
* Author : Atul Ramesh Raut
*
***/

#include <stdio.h>
#include <stdlib.h>

char* my_CpyCat (char *, char *);

int main () {
  
  char s1[] = "Atul ";
  char s2[] = "Raut";
  char *rStr = NULL;
  rStr = my_CpyCat (s1, s2);
  printf ("\n rStr = %s\n", rStr);
  return 0;
}

char* my_CpyCat (char *strS, char *strT) {

  char *newStr = NULL;
  int i=0, j=0;
  int m, n;

  m = strlen (strS);
  n = strlen (strT);

  newStr = (char*)malloc(sizeof (m+n+1));

  while (strS[j] != '\0') {
    newStr[i] = strS[j];
    i++; j++;
  }
  j = 0;
  while (strT[j] != '\0') {
    newStr [i] = strT[j];
    i++; j++;
  }
  newStr[i] = '\0';
  printf ("\n newStr = %s \n", newStr);
  return newStr;
}
