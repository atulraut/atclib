/***
    https://leetcode.com/problems/longest-common-prefix/
    Longest Common Prefix

    Write a function to find the longest common prefix
    string amongst an array of strings.
    If there is no common prefix, return an empty string "".

    Input: strs = ["flower","flow","flight"]
    Output: "fl"

    Input: strs = ["dog","racecar","car"]
    Output: ""
    Explanation: There is no common prefix among the input
    strings.

    Constraints:
    1 <= strs.length <= 200
    0 <= strs[i].length <= 200
    strs[i] consists of only lower-case English letters.

    Date: 17102021 Oct
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

char* longestCommonPrefix(char** strs, int strsSize) {
  int failed = 0;
  int i = 0;
  int currentChar = -1;

  if (strsSize == 0)
    return "";
  if (strsSize == 1)
    return strs[0];

  while(!failed && strs[0][++currentChar]) {
    for(int j=1; j<strsSize; j++) {
      debug ("-> %c --> %c", strs[0][currentChar], strs[j][currentChar]);
      if(strs[0][currentChar] != strs[j][currentChar] || !strs[j][currentChar]) {
	failed = 1;
	break;
      }
    }
  }

  debug("currentChar = %d", currentChar);
  strs[0][currentChar] = '\0';
  return strs[0];
}


/**
    AR Solution - Yet to finish
 **/
char* longestCommonPrefix2(char** strs, int strsSize) {
  int isCnt[26] = {0};
  int k;

  for (int i=0; i<strsSize; ++i) {
    char* str = strs[i];
    debug ("str = %s", str);
    int len = strlen(str);

    for (int j=0; j<len; ++j) {
      k = str[j]-97;
      debug ("k=%d", k);
      isCnt[k]++;
    }
  }

  for (int i=0; i<strsSize; ++i) {
    char* str = strs[i];
    int len = strlen(str);
    debug ("str = %s len=%d", str, len);
    for (int j=0; j<len; ++j) {
      k = str[j]-97;
      debug ("isCnt = %d", isCnt[k]);
    }
  }
}

char** getString() {
  debug ("Enter ");
  /***
       Allocate input string, as we are going to
       modify it in passing func, to avoid sigsegv falut
  */
  char** strs;
  char* strs2[] = {"flower","flow","flight"};
  // Allocate Rows & Cols
  strs= (char**)malloc(sizeof(char) * 3);
  for (int i=0; i<3; ++i)
    strs[i] = (char*)malloc(sizeof(char) * strlen(strs2[i]));
  // Copy strings we wanted as an example
  for (int i=0; i<3; ++i)
    strncpy(strs[i], strs2[i], strlen(strs2[i]));
  return strs;
}

/* Sigsegv fault if Debug is 0 */
#define DEBUG 0
int main (int argc, char **argv) {
  char* ret = 0;
  int strsSize = 3;

  #if DEBUG
    char** strs = getString();
  #else
    char* strs[] = {"flower","flow","flight"};
  #endif

  ret = longestCommonPrefix(strs, strsSize);
  debug("Output = %s", ret);
  return 0;
}

/**

 **/
