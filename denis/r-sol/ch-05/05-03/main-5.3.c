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
  char dest[10] = "Atul";  // As changing the content it must be array & not pointer. String pointer content we cant change.
  char *src = "Raut";
  char *ret = NULL;
  ret = aStrcat (dest, src);
  printf ("\nr == %s \n", ret);
  return 0;
}

char* aStrcat (char *dest, const char *src) {
  char *d = NULL;
  d = dest;
  while (*d != '\0')
    d++;
  while (*src != '\0')
    *d++ = *src++;
  *d = '\0';  
 return dest;
}
