/*
* Aim    : WAP Concating Two String to Form a New String.
* Date   : 30-04-2012
* Author : Atul Ramesh Raut
*
***/

#include <stdio.h>
#include <stdlib.h>

void my_CpyCat (char *, char *);

int main () {
  
  char s1[] = "Atul ";
  char s2[] = "Raut";
  my_CpyCat (s1, s2);
   return 0;
}

void my_CpyCat (char *strS, char *strT) {
  char newStr [10];
  int i=0, j=0;
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
}
