/*
 * Implement the at_strstr() function in C.
 * Date : 3-07-2013
 ***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  memcmp -- compare two memory regions.
  Credit -- linux.org
*/
int memcmp(const void *cs, const void *ct, size_t count) {
  const unsigned char *su1 = cs;
  const unsigned char *su2 = ct;
  const unsigned char *end = su1 + count;
  int res = 0;

  while (su1 < end) {
    printf ("s1 = %c s2 = %c \n", *su1, *su2);
    res = *su1++ - *su2++;
    printf ("s1 = %c s2 = %c \n", *su1, *su2);
    printf ("res = %d\n", res);
    if (res)
      break;
  }
  return res;
}

/* Linux kernel Implementation : lib/string.c
 * strstr - Find the first substring in a NUUL terminated string
 * @s1: The string to be searched
 * @s2: The string to search for
 */
char *linux_strstr(const char *s1, const char *s2) {
  size_t l1, l2;

  l2 = strlen(s2);
  if (!l2)
    return (char *)s1;
  l1 = strlen(s1);
  while (l1 >= l2) {
    l1--;
    if (!memcmp(s1, s2, l2))
      return (char *)s1;
    s1++;
  }
  return NULL;
}

/*
  Apple opensource : Bug it has 2 while loop & if string
  key > origin case not handle.
*/
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

int main () {
  char s11 [] = "AtRAJ";
  char s22 [] = "ATULRAJ";
  char s1[] = "GeeksforGeeks";
  char s2[] = "for";

  //printf ("[%s] Returned String 1: %s\n", __func__,  m_strstr (s1, "House"));
  printf ("[%s] Returned String 2: %s\n", __func__, linux_strstr (s1, s2));

  return 0;
}

/***
    => ./a.out
    s1 = G s2 = f
    s1 = e s2 = o
    res = -31
    s1 = e s2 = f
    s1 = e s2 = o
    res = -1
    s1 = e s2 = f
    s1 = k s2 = o
    res = -1
    s1 = k s2 = f
    s1 = s s2 = o
    res = 5
    s1 = s s2 = f
    s1 = f s2 = o
    res = 13
    s1 = f s2 = f
    s1 = o s2 = o
    res = 0
    s1 = o s2 = o
    s1 = r s2 = r
    res = 0
    s1 = r s2 = r
    s1 = G s2 =
    res = 0
*/
