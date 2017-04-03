/*
* Implement the at_strstr() function in C.
* Date : 3-07-2013
* Author : Atul Ramesh Raut
***/
#include <stdio.h>
#include <stdlib.h>

char* my_strstr (const char *src, const char *loc);
char *m_strstr(const char *string, const char *substring);

int main () {
  char s1 [] = "My House is small";
  char s2 [] = "My Car is green";

  printf ("Returned String 1: %s\n", m_strstr (s1, "House"));
  printf ("Returned String 2: %s\n", m_strstr (s2, "Car"));
  return 0;
}

char* my_strstr (const char *string, const char *substring) {
  char *a = NULL;
  char *b = (char*)substring;
  if (*string == 0)     // if string is null return
         return (char *)string;
  for (; *string != '\0'; string = string+1) {
        if (*string != *b) 
          continue;
        a = ((char *)string);
        while(1) {
          if (*b == '\0') 
            return ((char *)string);
          if (*a != *b)
            break;
          a++;
          b++;
        } // end while
        b = (char *)substring;
  } // end for
  return (char *) 0;
}

char *m_strstr(const char *origin, const char *key) {
  char k;
  size_t len;
  k = *key++;
  if (!k)
    return (char *) origin;// Trivial empty string case
  len = strlen(key);
  do {
    char o;
    do {
      o = *origin++;
      if (!o)
        return (char *) 0;
    } while (o != k);
  } while (strncmp(origin, key, len) != 0);
  return (char *) (origin - 1);
}
