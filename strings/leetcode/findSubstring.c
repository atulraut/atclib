/***
    https://leetcode.com/problems/substring-with-concatenation-of-all-words/
    Substring with Concatenation of All Words

    You are given a string s and an array of strings words of the same length.
    Return all starting indices of substring(s) in s that is a concatenation
    of each word in words exactly once, in any order, and without any
    intervening characters.

    You can return the answer in any order.

    Input: s = "barfoothefoobarman", words = ["foo","bar"]
    Output: [0,9]
    Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
    The output order does not matter, returning [9,0] is fine too.

    Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
    Output: []

    Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
    Output: [6,9,12]

    Constraints:
    1 <= s.length <= 104
    1 <= words.length <= 5000
    1 <= words[i].length <= 30
    s and words[i] consist of lowercase English letters.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Aug 12 11:36:38 PM PDT 2022
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
  char *temp;
  int slen = strlen(s);
  int *pmark;
  int dictlen=0, count=0;
  char *p=NULL;
  int regwordlen = strlen(words[0]);
  dictlen=regwordlen*wordsSize;
  temp = calloc((dictlen+1),sizeof(char));

  pmark = calloc((slen+1),sizeof(int));

  for(int i=0; i<= slen-dictlen;) {
    strncpy(temp, &s[i],dictlen);
    for(int j=0; j< wordsSize; j++) {

      for(int k=0; k<dictlen ;) {
	p=strstr(temp+k, words[j]);
	if(p!= NULL && ((p-temp) % regwordlen)==0)//poistion check
	  break;
	else if(NULL!=p) {
	  k=p-temp+1;
	  p=NULL;
	} else if(NULL==p)
	  goto nextseg;
      }
      if(NULL!=p )
        memset(p, '.', regwordlen);
      else
        goto nextseg;
    }
    if(slen!=0 && dictlen!=0)
      pmark[count++]=i;

  nextseg:
    i++;
  }
  *returnSize = count;
  return pmark;
}

void test() {
  char arr[] = "barfoothefoobarman";
  char *words[] = {"foo","bar"};
  int wordsSize = 2;
  int returnSize;

  int*ret = findSubstring(arr, words, wordsSize, &returnSize);
  for (int i=0; i<returnSize; ++i)
    debug("Output = %d", ret[i]);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=113 :Output = 0
   [test] L=113 :Output = 9
**/
