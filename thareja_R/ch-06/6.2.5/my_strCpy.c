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
  char t[] = "Raut";
  char *newString = NULL;
  newString = my_strCpy (s1, t);
  printf ("\n newString = %s \n", newString);
}

char * my_strCpy (char *s1, char *t) {
  int m=0, n=0;
  char *temp = NULL;

  //  m = strlen (s1);
  //n = strlen (t);

  temp = (char*)malloc(sizeof (m+n+1));

  //  while (s1 != '\0') {}
  temp =  strcpy (s1, t);  
  printf ("\n newString = %s\n", temp);
  return 0;
}

