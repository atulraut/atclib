/*
  Aim : Write your own trim() or squeeze() function to remove
  the spaces from a string.
  Note :
  T h i s   i s A t u l '\0'
  0 1 2 3 4 5 6 7 8 9 10
*/

#include <stdio.h>
#include "../../at_lib.h"

char *atclib_trim (char *s) {
  int i = 0, j = 0;
  char *gs = NULL;
  gs = s;
  while (s[i] != '\0') {
    if (!isspace(s[i])) {
      s[j++] = s[i++];
    } else
      i++;
  }
  s[j] = '\0';
  printf ("[%s]-->[%s]\n", __func__, gs);

  return s;
}

char *atclib_trim_ptr (char *s) {
  /* Alternate Using Pointers only */
  char *p = NULL;
  char *ps = NULL;
  for (ps=p=s; *s!='\0'; s++) {
    if (!isspace(*s))
      *p++ = *s;
  }
  *p = '\0';
  printf ("[%s]-->[%s]\n", __func__, (ps));
  return (ps);
}


int main () {
  char str[] = "This is Atul";
  char str_ptr[] = "This is Atul";
  char *ret;
  ret = atclib_trim (str);
  printf ("[%s]-->[%s]\n", __func__, ret);

  ret = atclib_trim_ptr (str_ptr);
  printf ("[%s]-->[%s]\n", __func__, ret);
}

/**
   => ./a.out
   [atclib_trim]-->[ThisisAtul]
   [main]-->[ThisisAtul]
   [atclib_trim_ptr]-->[ThisisAtul]
   [main]-->[ThisisAtul]
**/
