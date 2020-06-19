/***
 * Given a string s and a string t, check if s is subsequence of t.
 * A subsequence of a string is a new string which is formed from the
 * original string by deleting some (can be none) of the characters without
 * disturbing the relative positions of the remaining characters. (ie, "ace"
 * is a subsequence of "abcde" while "aec" is not).
 * Follow up:
 * If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and
 * you want to check one by one to see if T has its subsequence. In this scenario,
 * how would you change your code?
 * Example 1:
 * Input: s = "abc", t = "ahbgdc"
 * Output: true
 * Example 2:
 * Input: s = "axc", t = "ahbgdc"
 * Output: false
 * Logic:  https://www.youtube.com/watch?v=PwQnydsKk_I
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Approch-2: 4ms */
int isSubsequence2(char *s, char *t){
  int i, x = 0;
    for(i = 0; i < strlen(t); i++){
        if(s[x] == t[i]){
            x++;
        }
    }
    if(x == strlen(s)){
        return 1;
    }
    return -1;
}

/* Approch-1: 0ms */
int isSubsequence(char * s, char * t){
  for (; *s && *t ; s += *s == *t++) {
    printf ("--> *s=%c s=%p *t=%c t=%p \n", *s, s, *t, t);
  }
  return !*s;
}

int main () {
  char s[] = "axc";
  char t[] = "ahbgdc";
  int ret;

  ret = isSubsequence (s, t);

  printf ("[%s] ret = %d L=%d\n", __func__, ret, __LINE__);
}
