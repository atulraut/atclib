/***
    https://leetcode.com/problems/determine-if-string-halves-are-alike/
    1704. Determine if String Halves Are Alike
    Easy

    You are given a string s of even length. Split this string into two halves
    of equal lengths, and let a be the first half and b be the second half.

    Two strings are alike if they have the same number of vowels
    ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'). Notice that s contains
    uppercase and lowercase letters.

    Return true if a and b are alike. Otherwise, return false.

    Input: s = "book"
    Output: true
    Explanation: a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.

    Input: s = "textbook"
    Output: false
    Explanation: a = "text" and b = "book". a has 1 vowel whereas b has 2. Therefore, they are not alike.
    Notice that the vowel o is counted twice.

    Input: s = "MerryChristmas"
    Output: false

    Input: s = "AbCdEfGh"
    Output: true

    Constraints:
    2 <= s.length <= 1000
    s.length is even.
    s consists of uppercase and lowercase letters.

    Date : 4/8/21 - April
    San Diego, CA
    Author - Rauji(Atul) Raut
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

#define NHASH 256
enum ops {
  LOOKUP = 1,
  INSERT = 2
};

struct nameval {
  char c;
  int val;
};
struct nameval *systab[NHASH];

int get_hash(char c) {
  return (c % NHASH);
}

char lookup(char c, int val, int ops) {
  int h = get_hash(c);
  struct nameval *sys = NULL;

  sys = systab[h];
  if (ops == LOOKUP) {
    if (sys)
      return sys->c;
    else
      return -1;
  }

  if (ops == INSERT) {
    sys = (struct nameval*)malloc(sizeof(struct nameval));
    sys->c = c;
    sys->val = val;
    systab[h] = sys;
  }
  return 1; // to avoid error
}

void atclib_hashSetUp() {
  char str[] = "aeiouAEIOU";
  int len = strlen(str);
  for (int i=0; i<len; i++) {
    debug ("char = %c val = %d", str[i], str[i]);
    lookup(str[i], str[i], INSERT);
  }
}

/**
   4ms
 **/
bool atclib_halvesAreAlike(char* s) {
  int len = strlen(s);
  int scnt = 0, mcnt = 0;
  if (len <= 0 || (len%2) != 0)
    return 0;
  int midl = len/2;
  char *start = s;
  char *mid   = s+midl;
  debug ("len = %d mid = %d start = %c mid = %c", len, midl, start[0], mid[0]);
  atclib_hashSetUp();

  for (int i=0; i<midl; i++) {
    char s = lookup(start[i], start[i], LOOKUP);
    char m = lookup(mid[i], mid[i],     LOOKUP);
    debug ("[%d] start[i]=%c s=%c s=%d mid[i]=%c m=%c m=%d",i, start[i],s, s, mid[i], m, m);
    if (s != -1)
      scnt++;
    if(m!= -1)
      mcnt++;
  }
  if (scnt == mcnt)
    return true;
  else
    return false;
}

bool leetcode_halvesAreAlike(char * s){
    int count = 0, length = strlen(s) / 2;
    char c1, c2;
    for (int i = 0; i < length; i++) {
        c1 = *(s + i);
        if (c1 == 'a' || c1 == 'o' || c1 == 'e' || c1 == 'i' || c1 == 'u' || c1 == 'A' || c1 == 'O' || c1 == 'E' || c1 == 'I' || c1 == 'U' ) {
            count++;
        }

        c2 = *(s + i + length);
        if (c2 == 'a' || c2 == 'o' || c2 == 'e' || c2 == 'i' || c2 == 'u' || c2 == 'A' || c2 == 'O' || c2 == 'E' || c2 == 'I' || c2 == 'U' ) {
            count--;
        }
    }
    printf("%d", count);
    if (0 == count) {
        return true;
    } else {
        return false;
    }
}

int main () {
  char word1[] = "bookoo";
  char word2[] = "MerryChristmas";
  char word[] = "AbCdEfGh";
  bool ret;

  debug("Output = %d", atclib_halvesAreAlike(word));

 return 0;
}

/***
    Complexity Analysis
    Let N be the length of s.
    Time Complexity: O(N), since we need to iterate
    substring a and b.
    Space Complexity: O(1), since we do not need extra space.
    Here we do not take the input s into consideration.
*/

/*
  => ./a.out
  [atclib_halvesAreAlike] L=109 :len = 8 mid = 4 start = A mid = E
  [atclib_hashSetUp] L=93 :char = a val = 97
  [atclib_hashSetUp] L=93 :char = e val = 101
  [atclib_hashSetUp] L=93 :char = i val = 105
  [atclib_hashSetUp] L=93 :char = o val = 111
  [atclib_hashSetUp] L=93 :char = u val = 117
  [atclib_hashSetUp] L=93 :char = A val = 65
  [atclib_hashSetUp] L=93 :char = E val = 69
  [atclib_hashSetUp] L=93 :char = I val = 73
  [atclib_hashSetUp] L=93 :char = O val = 79
  [atclib_hashSetUp] L=93 :char = U val = 85
  [atclib_halvesAreAlike] L=115 :[0] start[i]=A s=A s=65 mid[i]=E m=E m=69
  [atclib_halvesAreAlike] L=115 :[1] start[i]=b s=� s=-1 mid[i]=f m=� m=-1
  [atclib_halvesAreAlike] L=115 :[2] start[i]=C s=� s=-1 mid[i]=G m=� m=-1
  [atclib_halvesAreAlike] L=115 :[3] start[i]=d s=� s=-1 mid[i]=h m=� m=-1
  [main] L=155 :Output = 1
*/
