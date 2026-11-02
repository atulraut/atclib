/***
    https://leetcode.com/problems/decode-string
    Decode String

    Given an encoded string, return its decoded string.

    The encoding rule is: k[encoded_string], where the
    encoded_string inside the square brackets is being repeated
    exactly k times. Note that k is guaranteed to be a positive integer.

    You may assume that the input string is always valid; No extra
    white spaces, square brackets are well-formed, etc.

    Furthermore, you may assume that the original data does not contain
    any digits and that digits are only for those repeat numbers, k.
    For example, there won't be input like 3a or 2[4].

    Input: s = "3[a]2[bc]"
    Output: "aaabcbc"

    Input: s = "3[a2[c]]"
    Output: "accaccacc"

    Input: s = "2[abc]3[cd]ef"
    Output: "abcabccdcdcdef"

    Input: s = "abc3[cd]xyz"
    Output: "abccdcdcdxyz"

    Constraints:

    1 <= s.length <= 30
    s consists of lowercase English letters, digits, and square brackets '[]'.
    s is guaranteed to be a valid input.
    All the integers in s are in the range [1, 300].

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/18/2021
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

char* decodeString(char* s) {
  char *stack = malloc(100001);
  int top = -1;

  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] != ']') {
      stack[++top] = s[i];
      continue;
    }

    // 1. Pop characters until '['
    char temp[100001];
    int len = 0;

    while (stack[top] != '[')
      temp[len++] = stack[top--];

    top--;  // Remove '['

    // 2. Extract repeat count
    int num = 0, place = 1;

    while (top >= 0 && stack[top] >= '0' && stack[top] <= '9') {
      num += (stack[top--] - '0') * place;
      place *= 10;
    }

    // 3. Push decoded string back
    while (num--) {
      for (int j = len - 1; j >= 0; j--)
	stack[++top] = temp[j];
    }
  } // for ends

  stack[top + 1] = '\0';
  return stack;
}

int main (int argc, char **argv) {
  char* ret;
  char s[] = "3[a2[c]]";

  ret = decodeString(s);
  debug("Output = %s", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=219 :Output = accaccacc
**/
