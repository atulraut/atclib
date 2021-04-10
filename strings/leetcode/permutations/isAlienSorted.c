/***
    https://leetcode.com/problems/verifying-an-alien-dictionary/submissions/
    953. Verifying an Alien Dictionary - Easy
    In an alien language, surprisingly they also use english lowercase letters,
    but possibly in a different order. The order of the alphabet is some
    permutation of lowercase letters.

    Given a sequence of words written in the alien language, and the order of
    the alphabet, return true if and only if the given words are sorted
    lexicographicaly in this alien language.

    Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
    Output: true
    Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.

    Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
    Output: false
    Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1],
    hence the sequence is unsorted.

    Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
    Output: false
    Explanation: The first three characters "app" match, and the second string is
    shorter (in size.) According to lexicographical rules "apple" > "app",
    because 'l' > '∅', where '∅' is defined as the blank character which is less
    than any other character (More info).

 Constraints:
    1 <= words.length <= 100
    1 <= words[i].length <= 20
    order.length == 26
    All characters in words[i] and order are English lowercase letters.

    Date: 4/9/21 April
    San Diego, CA
*/

/*
  Step1 - Create a map between ASCII and the provided order.
  Step2 - Write a custom strcmp that uses the map to compare strings.
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

int map[26];
#define INDEX(c) (('\0' == c)?-1:map[c-'a'])

int mystrcmp (const char *p1, const char *p2) {
    const  char *s1 = p1;
    const  char *s2 = p2;

    while (*s1 && *s2 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return INDEX(*s1) - INDEX(*s2);
}

void makeMap(char *dict) {
    for(int i = 0 ; i < 26 ; i++) {
        map[dict[i]-'a'] = i;
    }
}

bool isAlienSorted(char **words, int wordsSize, char *order) {
    makeMap(order);

    if (wordsSize < 2) {
        return true;
    }
    for (int i = 1; i < wordsSize; i++) {
        if (mystrcmp(words[i-1], words[i]) > 0)
            return false;
    }
    return true;
}


int main () {
  int wordsSize;
  char *words[2] = {"hello","leetcode"};
  char *order = "hlabcdefgijkmnopqrstuvwxyz";

  wordsSize = sizeof(words)/sizeof(words[0]);

  int ret = isAlienSorted(words, wordsSize, order);

  debug ("Oputput = %d", ret);

  return 0;
}

/*
  => ./a.out
  [main] L=98 :Oputput = 1
*/
