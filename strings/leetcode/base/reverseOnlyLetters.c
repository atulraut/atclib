/***
    Reverse Only Letters

    Given a string s, reverse the string according to
    the following rules:

    All the characters that are not English letters
    remain in the same position.
    All the English letters (lowercase or uppercase)
    should be reversed.
    Return s after reversing it.

    Input: s = "ab-cd"
    Output: "dc-ba"

    Input: s = "a-bC-dEf-ghIj"
    Output: "j-Ih-gfE-dCba"

    Input: s = "Test1ng-Leet=code-Q!"
    Output: "Qedo1ct-eeLg=ntse-T!"

    Constraints:
    1 <= s.length <= 100
    s consists of characters with ASCII values in the range [33, 122].
    s does not contain '\"' or '\\'.

    https://leetcode.com/problems/reverse-only-letters/

    Date: 15 September 2021 - Happy Engineers Day!
    Fair Oaks, CA.
*/

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

char* reverseOnlyLetters(char* s){
  char *save = s;
  char *e = save + strlen(s) - 1;
  while (save < e) {
    if (!isalpha(*save)) {
      save++;
      continue;
    }
    if (!isalpha(*e)) {
      e--;
      continue;
    }
    // swap
    char c = *save;
    *save = *e;
    *e = c;
    save++;
    e--;
  }
  return s;
}

void swap(int index, int i, char* s) {
  while (index < i) {
    char temp = s[index];
    s[index]  = s[i];
    s[i]      = temp;
  ++index;
  --i;
  }
}

char* reverseOnlyLetters__(char* s) {
  char *save = s;
  int i = 0;
  int index = 0;
  int len = strlen(s);

  for(i=0; i<=len; ++i) {
    if (s[i] == '-' || s[i] == '\0') {
      swap(index, i-1, s);
      index = i + 1;
    }
  }
  return save;
}

int main (int argc, char **argv) {
  char* ret;
  char s[] = "ab-cd";

  ret = reverseOnlyLetters(s);
  debug("Output = %s", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=72 :Output = dc-ba
**/
