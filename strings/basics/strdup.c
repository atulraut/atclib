/***
    Write a C program to implement your own strdup() function.
    The strdup() function returns a pointer to a new string
    which is a duplicate of the string s. Memory for the new
    string is obtained with malloc(3), and can be freed with
    free.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 10242021 Oct
    Fair Oaks, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ typeof (a) _a = (a);	\
    typeof (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

char *my_strdup (char *s) { /* make a duplicate of s */
  char *p = NULL;
  p = (char *) malloc (strlen (s)+1);  /* +1 for '\0'*/
  if (p != NULL)
    strcpy (p, s);
  return p;
}

/* May not compile: FixMe*/
char* kstrndup_linux(const char *s, size_t max) {
  size_t len;
  char *buf;

  if (!s)
    return NULL;

  len = strnlen(s, max);
  buf = malloc(strlen(s)+1);
  //  buf = kmalloc_track_caller(len+1, gfp);
  if (buf) {
    memcpy(buf, s, len);
    buf[len] = '\0';
  }
  return buf;
}

int main (int argc, char **argv) {
  char* ret;
  char s[] = "Atul Raut";
  size_t max = 4;
  ret = kstrndup_linux(s, max);
  debug("Output = %s", ret);
  free(ret);
  ret = NULL;

  return 0;
}

/**
   => ./a.out
   [main] L=66 :Output = Atul
**/
