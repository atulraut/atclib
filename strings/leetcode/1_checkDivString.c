/***
    Divisibility of strings in C

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri 09 Aug 2024 02:50:04 PM PDT
    Folsom, CA.
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

#define debug(str,args...) printf("L=[%d] [%s] :| "str"\n", __LINE__, __func__, ##args)

int a_memcmp(const void *cs, const void *ct, size_t count) {

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

/***
  sometime its slower so avoid using it.
  Here it looks faster
*/
int checkDivStr_memcmp(const char* src, const char* tar) {
  int ret = 0;
  size_t i = 0;
  size_t s_len = strlen(src);
  size_t t_len = strlen(tar);

  if (s_len % t_len != 0)
    return 0;
  debug("s_len = %ld", s_len);
  while (i < s_len-1) {
    debug ("i=%ld s_len=%ld ret=%d src=%s tar=%s", i, s_len, ret, src+i, tar);

    ret = memcmp(src+i, tar, t_len);
    i += t_len;
    debug ("ret = %d i=%ld", ret, i);
    if (ret != 0) // src < target
      return 0;

  }
  return 1;
}

int test () {

  char* s = "ABCDABCDABCD";
  char* t = "ABCD";
  int ret = checkDivStr_memcmp(s, t);
  debug("Output = %d", ret);
}


int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   L=[55] [checkDivStr_memcmp] :| s_len = 12
   L=[57] [checkDivStr_memcmp] :| i=0 s_len=12 ret=0 src=ABCDABCDABCD tar=ABCD
   L=[61] [checkDivStr_memcmp] :| ret = 0 i=4
   L=[57] [checkDivStr_memcmp] :| i=4 s_len=12 ret=0 src=ABCDABCD tar=ABCD
   L=[61] [checkDivStr_memcmp] :| ret = 0 i=8
   L=[57] [checkDivStr_memcmp] :| i=8 s_len=12 ret=0 src=ABCD tar=ABCD
   L=[61] [checkDivStr_memcmp] :| ret = 0 i=12
   L=[74] [test] :| Output = 1
**/
