/***
    151. Reverse Words in a String

    https://leetcode.com/problems/reverse-words-in-a-string/description/

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Sep 26 16:16:02 PDT 2026
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

/**
   Input:
"  the   sky is  blue  "

            |
            | removeSpaces()        <-- I
            v

"the sky is blue"

            |
            | reverse whole string  <-- II
            v

"eulb si yks eht"

            |
            | reverse each word      <-- III
            v

"blue is sky the"
 **/
// <-- I
void removeSpaces(char* s) {
  int i, j;
  for (i = 0, j = 0; s[i]; ++i)
    if (s[i] != ' ' || (i > 0 && s[i - 1] != ' '))
      s[j++] = s[i];
  if (j > 0 && s[j - 1] == ' ')
    j--;
  s[j] = '\0';
}

void reverse(char* s, int start, int end) {
  while (start < end) {
    char tmp = s[start];
    s[start] = s[end];
    s[end] = tmp;
    start++;
    end--;
  }
}

char* reverseWords(char* s) {
  removeSpaces(s);  // <-- I

  int n = strlen(s);

  for (int i = 0; i < n / 2; i++) {  // <-- II : Reverse entire string
    char tmp = s[i];
    s[i] = s[n - i - 1];
    s[n - i - 1] = tmp;
  }

  int start = 0;     // <-- III : Find each word and reverse it
  for (int end = 0; end < n; end++) {
    if (s[end] == ' ') {
      reverse(s, start, end - 1);
      start = end + 1;
    }
  }

  reverse(s, start, n - 1);  // <-- IV : Last eht needs reverse
  return s;
}

void test() {
  char str[] = "the sky is blue";

  debug("Output = %s", reverseWords(str));
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   L=[71][2_reverse_words_string_LC-151.c]->[test] :| Output = blue is sky the
**/
