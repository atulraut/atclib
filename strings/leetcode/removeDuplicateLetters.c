/***
    https://leetcode.com/problems/remove-duplicate-letters
    Remove Duplicate Letters

    Given a string s, remove duplicate letters so that every letter
    appears once and only once. You must make sure your result
    is the smallest in lexicographical order among all possible results.

    Input: s = "bcabc"
    Output: "abc"

    Input: s = "cbacdcbc"
    Output: "acdb"

    Constraints:

    1 <= s.length <= 104
    s consists of lowercase English letters.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Sat Mar 19 10:32:36 PDT 2022
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

char * removeDuplicateLetters_AR(char * s) {
    int i=0, j=0;
    int isPresent[256] = {0};
    int len = strlen(s);
    char* arr = (char *)malloc(sizeof(char) * len+1 );
    for (int i=0; i<len; ++i)
        isPresent[s[i]]++;

    for (int i=0; i<len; ++i) {
        debug("i=%d s[i]=%c is=%d",i,s[i], isPresent[s[i]]);
        if (isPresent[s[i]] >= 2) {
            isPresent[s[i]]--;
        } else
            arr[j++] = s[i];;
    }
    arr[j] = '\0';
    debug ("arr = %s", arr);
    return arr;
}

char* removeDuplicateLetters (char* s) {
  int i,j=0, alphabet[26]={0},choosen[26]={0}, count=0, len = strlen(s);

  char *out = (char*)calloc(sizeof(char), 27);

  for(i = 0; s[i]!='\0'; i++)
    alphabet[s[i]-'a']++;

  for (i = 0; i < len; i++) {
    alphabet[s[i] - 'a']--;
    if (choosen[s[i] - 'a'])
      continue;
    while (j > 0 && s[i] < out[j - 1] && alphabet[out[j - 1] - 'a'] > 0)
      choosen[out[--j] - 'a'] = 0;
    choosen[s[i] - 'a'] = out[j++] = s[i];;
  }
  out[j] = '\0';
  return out;
}

void test() {
  char str[] = "cbacdcbc";
  char* ret = NULL;

  ret = removeDuplicateLetters(str);
  debug("Output = %s", ret);
  free(ret);
  ret = NULL;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=80 :Output = acdb
**/
