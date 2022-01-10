/***

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 10 Jan 2022 _ Happy Birthday to dear Mom
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

/*----------------------------------- Micro --------------------------------------*/
#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define arrsz(x)  (sizeof(x) / sizeof((x)[0]))
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

size_t strlen_atclib(const char *str) {
  const char *strcnt;

  debug ("%c %d", *str, *str);
  for (strcnt=str; *strcnt!='\0'; ++strcnt)
    ;
  return (strcnt-str);
}

void test() {
  char test[] = "Atul Raut";

  int len = strlen_atclib(test);
  debug("Output = %d", len);
}

int main (int argc, char **argv) {
  int ret = 0;

  test();
  debug("Output = %d", ret);
  return 0;
}

/**

 **/
