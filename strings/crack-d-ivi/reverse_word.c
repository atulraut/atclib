/***
    https://leetcode.com/problems/reverse-words-in-a-string/
    Reverse Words in a String

    Given an input string s, reverse the order of the words.
    A word is defined as a sequence of non-space characters.
    The words in s will be separated by at least one space.

    Return a string of the words in reverse order concatenated
    by a single space.

    Note that s may contain leading or trailing spaces or
    multiple spaces between two words. The returned string
    should only have a single space separating the words.
    Do not include any extra spaces.

    Input: s = "the sky is blue"
    Output: "blue is sky the"
    Example 2:

    Input: s = "  hello world  "
    Output: "world hello"
    Explanation: Your reversed string should not contain
    leading or trailing spaces.

    Input: s = "a good   example"
    Output: "example good a"
    Explanation: You need to reduce multiple spaces between
    two words to a single space in the reversed string.

    Input: s = "  Bob    Loves  Alice   "
    Output: "Alice Loves Bob"

    Input: s = "Alice does not even like bob"
    Output: "bob like even not does Alice"

    Constraints:
    1 <= s.length <= 104
    s contains English letters (upper-case and lower-case), digits, and spaces ' '.
    There is at least one word in s.

    Follow-up: If the string data type is mutable in your language,
    can you solve it in-place with O(1) extra space?

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fstack-protector-all -fsanitize=address reverse_word.c -lm

    Date: 20 Oct 2021
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

void reverseString(char* start, char* end) {
    while (start < end) {
        char c = *start;
        *start++ = *--end;
        *end = c;
    }
}

char* reverseWords_LeetCode(char* s) {
    char *w = s;
    char *s_ptr = s;
    char *w_ptr = s;
    bool space = true;
    while ((*w_ptr = *s_ptr++) != 0) {
        if (*w_ptr != ' ') {
            space = false;
            w_ptr++;
        }
        else if (!space) {
            space = true;
            reverseString(w, w_ptr++);
            w = w_ptr;
        }
    }
    if (w_ptr == s)
      return s;
    if (space)
      *--w_ptr = 0;
    else
      reverseString(w, w_ptr);

    reverseString(s, w_ptr);
    return s;
}

/* Runtime Error */
void rev(char *l,char *r) {
  char t;
  printf ("[%s] l=%c r=%c L=%d\n",__func__, *l, *r, __LINE__);
  while(l<r) {
    t  = *l;
    *l++ = *r;
    *r-- = t;
  }
}

void reverse_word () {
  char buf[] = "I am a good boy";
  char *end, *x, *y;

  // Reverse the whole sentence first..
  for(end=buf; *end; end++)
            ;
  rev(buf, end-1);

  printf("[%s] %s L=%d \n",__func__, buf, __LINE__);

  // Now swap each word within sentence...
  x = buf-1;
  y = buf;
  while(x++ < end) {
    if(*x == '\0' || *x == ' ') {
      rev(y, x-1);
      y = x+1;
    }
  }

  // Now print the final string....
  printf("[%s] %s L=%d \n",__func__, buf, __LINE__);
}

int main(int argc, char *argv[]) {
  reverse_word();
  return(0);
}

/**
   => ./a.out
   [rev] l=I r=y L=30
   [reverse_word] yob doog a ma I L=46
   [rev] l=y r=b L=30
   [rev] l=d r=g L=30
   [rev] l=a r=a L=30
   [rev] l=m r=a L=30
   [rev] l=I r=I L=30
   [reverse_word] boy good a am I L=59
**/
