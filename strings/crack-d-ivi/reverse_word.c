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

/**
   Algo -
   I - Each word reverse
   II - Reverse Entire Sentence
*/
char* reverseWords_LeetCode(char* s) {
  char *save = s;
  char *s_ptr = s;
  char *e_ptr = s;
  bool space = true;

  while ((*e_ptr = *s_ptr++) != 0) {
    if (*e_ptr != ' ') {
      space = false;
      e_ptr++;
    }
    else if (!space) {
      space = true;
      reverseString(save, e_ptr++);
      debug ("save=%s e_ptr=%s", save, e_ptr);
      save = e_ptr;
    }
  }

  if (e_ptr == s)
    return s;
  if (space)
    *--e_ptr = 0;
  else {
    debug ("save=%s e_ptr=%s", save, e_ptr);
    reverseString(save, e_ptr);
  }
  debug ("s=%s e_ptr=%s", s, e_ptr);

  // Individual works are reverse now, reverse entire string
  reverseString(s, e_ptr);
  debug ("save=%s e_ptr=%s", s, e_ptr);
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

void test () {
  char str1[] = "the sky is blue";
  char str[] = "Atul Raut";
  debug("Output = %s", reverseWords_LeetCode(str1));	
}

int main(int argc, char *argv[]) {
  test();
  return(0);
}

/**
   >> ./a.out
   [reverseWords_LeetCode] L=90 :save=eht sky is blue e_ptr=sky is blue
   [reverseWords_LeetCode] L=90 :save=yks is blue e_ptr=is blue
   [reverseWords_LeetCode] L=90 :save=si blue e_ptr=blue
   [reverseWords_LeetCode] L=100 :save=blue e_ptr=
   [reverseWords_LeetCode] L=103 :s=eht yks si eulb e_ptr=
   [reverseWords_LeetCode] L=107 :save=blue is sky the e_ptr=
   [test] L=150 :Output = blue is sky the

   >> ./a.out
   [rev] l=I r=y L=114
   [reverse_word] yob doog a ma I L=131
   [rev] l=y r=b L=114
   [rev] l=d r=g L=114
   [rev] l=a r=a L=114
   [rev] l=m r=a L=114
   [rev] l=I r=I L=114
   [reverse_word] boy good a am I L=144
**/
