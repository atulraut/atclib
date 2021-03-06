/***
    https://leetcode.com/problems/custom-sort-string/
    Medium: Custom Sort String
    S and T are strings composed of lowercase letters.
    In S, no letter occurs more than once.

    S was sorted in some custom order previously. We want to permute
    the characters of T so that they match the order that S was sorted.
    More specifically, if x occurs before y in S, then x should occur
    before y in the returned string.

    Return any permutation of T (as a string) that satisfies this property.

    Example :
    Input:
    S = "cba"
    T = "abcd"
    Output: "cbad"
    Explanation:
    "a", "b", "c" appear in S, so the order of "a", "b", "c" should
    be "c", "b", and "a".
    Since "d" does not appear in S, it can be at any position in T.
    "dcba", "cdba", "cbda" are also valid outputs.

    Note:
    S has length at most 26, and no character is repeated in S.
    T has length at most 200.
    S and T consist of lowercase letters only.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/***
    0ms :
*/
char* customSortString(char* S, char* T) {
  int* a = (int*) malloc (26*sizeof(int));
  for(int i=0; i<26; i++)
    a[i] = 0;

  char* temp = T;
  while(*temp!='\0') {
    a[*temp-'a']++;
    temp++;
  }
  temp=T;
  while(*S!='\0') {
    for(;a[*S-'a']>0; a[*S-'a']--) {
      *temp = *S;
      temp++;
    }
    S++;
  }

  for(int i=0; i<26; i++) {
    for(int j=0; j<a[i]; j++) {
      *temp = 'a'+i;
      temp++;
    }
  }

  debug ("T = %s ", T);
  return T;
}

/***
     4ms :
*/
char * customSortString2 (char* src, char* T) {
  int i;
  int j;
  int count = 0;
  char temp;

  for(i=0; i<strlen(src); i++) {
    for(j=0; j<strlen(T); j++) {
      if(src[i]==T[j]) {
	temp = T[count];
	T[count] = T[j];
	T[j] = temp;
	count++;
      }
    }
  }
  return T;
}

int main() {
  char S[] = "cba";
  char T[] = "abcd";

  char*ret = customSortString2(S, T);

  debug(" Ret = %s ", ret);

  return 0;
}

/**

 **/
