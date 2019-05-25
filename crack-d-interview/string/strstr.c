/*
* Implement the at_strstr() function in C.
* Date : 3-07-2013
* Author : Atul Ramesh Raut
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
    res = *su1++ - *su2++;
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
  char s1 [] = "My House is small";
  char s2 [] = "My Car is green";

  printf ("Returned String 1: %s\n", m_strstr (s1, "House"));
  printf ("Returned String 2: %s\n", linux_strstr (s2, "Car"));
  return 0;
}
