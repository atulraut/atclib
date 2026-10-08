/***

    longest k unique character.

    2 - Variable-size sliding window

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Thu Oct  8 09:48:06 PDT 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

int longestKUnique(const char *s, int k) {
  int freq[256] = {0};
  int left = 0, unique = 0;
  int maxLen = -1;

  if (k <= 0)
    return -1;

  for (int right = 0; s[right]; right++) {

    unsigned char c = (unsigned char)s[right];

    // EXPAND
    if (freq[c] == 0)
      unique++;

    freq[c]++;

    // SHRINK if invalid
    while (unique > k) {
      unsigned char ch =
	(unsigned char)s[left];

      freq[ch]--;

      if (freq[ch] == 0)
	unique--;

      left++;
    }

    // UPDATE if exactly K unique
    if (unique == k) {
      int len = right - left + 1;

      if (len > maxLen)
	maxLen = len;
    }
  }

  return maxLen;
}

int test(void) {
  const char *s = "aabacbebebe";
  debug("Length = %d\n", longestKUnique(s, 3));
  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
