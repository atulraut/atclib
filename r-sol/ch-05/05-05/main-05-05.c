/*
* Auther : Atul R. Raut
* Date   : Sun Dec 25th 2011, 10:32PM 
* AIM    : Write versions of the library functions strncpy, strncat and strncmp,
*          which operate on at most the first n characters of their argument strings
*          For ex. strncpy (s,t,n) copies at most n characters of t to s.
***/
#include <stdio.h>

void aStrncpy (char *s, char *t, int n);
char*  aStrncat (char *s, char *t, int n);
int aStrncmp (char *s, char *t, int n);

int main () {
  char *str = "Atul";
  char *tar = "Raut";
  
  aStrncpy (str, tar, 4);

  //char*  aStrncat (char *s, char *t, int n);
  //int aStrncmp (char *s, char *t, int n);

  return 0;
}

void aStrncpy (char *s, char *t, int n) {
  //  while (*s++ = *t++)
  //  ;
  while (*t != '\0' && n-- > 0)
    *s++ = *t++;
  while (n-- > 0)
    *s = '\0';
  printf ("\ns = %s\n", s);
}

char*  aStrncat (char *s, char *t, int n) {

}

int aStrncmp (char *s, char *t, int n) {

}
