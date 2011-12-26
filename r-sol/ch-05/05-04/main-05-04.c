/*
* Name : Atul Raut
* Date : Sat Dec 24, 2011, 01:38PM
* Aim :  Write a function strend (s, t), which returns 1 if the string
* t occurs at the end of the string s and zero otherwise.
*
***/

#include <stdio.h>

int aStrend (char *, char *);

int main () {
  char *s = "RajAtul";
  char *t = "Atul";
  int r;
  r = aStrend (s, t);
  printf ("\n r = %d\n", r);
}

/* aStrend : return 1 if string t occurs at the end of s */
int aStrend (char *s, char *t) {
  char *bs = s; /* Remember begining of strs */
  char *bt = t;
  
  for (; *s; s++) /* end of string s */
    ;
  for (; *t; t++) /* end of string t */
    ;
  for (; *s == *t; s--, t--)
    if (t == bt | s == bs)
      break;                    /* at the begining of the string */

  if (*s == *t && t == bt && *s != '\0')
    return 1;
  else
    return 0;
      
}

