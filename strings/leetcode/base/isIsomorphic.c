/***
    https://leetcode.com/problems/isomorphic-strings/
    Isomorphic Strings

    Given two strings s and t, determine if they are isomorphic.

    Two strings s and t are isomorphic if the characters in
    s can be replaced to get t.

    All occurrences of a character must be replaced with another
    character while preserving the order of characters. No two
    characters may map to the same character, but a character
    may map to itself.

    Input: s = "egg", t = "add"
    Output: true

    Input: s = "foo", t = "bar"
    Output: false

    Input: s = "paper", t = "title"
    Output: true

    Constraints:
    1 <= s.length <= 5 * 104
    t.length == s.length
    s and t consist of any valid ascii character.

    Date: 10182021 Oct
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

bool isIsomorphic(char* s, char* t) {
  char charArrS[256] = { 0 };
  char charArrT[256] = { 0 };
  int i = 0;

  while (s[i] !=0) {
    if (charArrS[s[i]] == 0 && charArrT[t[i]] == 0) {
      charArrS[s[i]] = t[i];
      charArrT[t[i]] = s[i];
    } else if (charArrS[s[i]] != t[i] || charArrT[t[i]] != s[i])
      return false;
    i++;
  }
  return true;
}

bool isIsomorphic2(char * s, char * t){
  int map[256] = {0}, revmap[256] = {0};

  int idx = 0;
  while(s[idx]) {
    if(!map[s[idx]]) {
      map[s[idx]] = t[idx];
      // if our new mapping already has been taken by a different mapping 0
      if(revmap[t[idx]])
	return 0;
      revmap[t[idx]] = s[idx];

    } else if(t[idx] != map[s[idx]])
      return 0;
    ++idx;
  }

  return 1;
}

int main (int argc, char **argv) {
  bool ret = 0;
  char* s = "egg";
  char* t = "add";
  char* s1 = "badc";
  char* t1 = "baba";

  ret =  isIsomorphic(s, t);
  debug("Output = %d", ret);

  ret =  isIsomorphic(s1, t1);
  debug("Output = %d", ret);

  return 0;
}

/**
   => ./a.out
   [main] L=90 :Output = 1
   [main] L=93 :Output = 0
**/
