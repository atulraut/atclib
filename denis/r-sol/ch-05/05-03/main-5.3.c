/*
* Auther : Atul R. Raut 
* Date   : Fri Dec 23, 2011, 09.30PM
* Aim : WAP, a pointer version fo the functoin strcat. 
* strcat(s, t), copies the string t to the end of s.
*
***/
#include <stdio.h>

char* aStrcat (char *src, char *target);

int main () {
  char *s = "Atul";
  char *t = "Raut";
  char *r = NULL;
  r = aStrcat (s, t);
  printf ("\n111");
  *r = '\0';  
  printf ("\nr == %c\n", *r);
}

char* aStrcat (char *s, char *t) {
  printf ("\ns = %s, t= %s \n", s, t);
  while (*s != '\0')
    s++;
  printf ("\n000111");
  while (*s++ = *t++)
    ;
  printf ("\n000");
 return s;
}
