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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

void substr(char *dest, char *src, int position, int length) {
  dest[0]='\0';
  strncat(dest, (src + position), length);
}

int main() {
  char str1[] = "India";
  char str2[25];
  substr(str2, str1, 1, 3);
  debug("\nstr2 : [%s]", str2);
  return(0);
}

/**
   => ./a.out
   [main] L=23 :
   str2 : [ndi]
**/
