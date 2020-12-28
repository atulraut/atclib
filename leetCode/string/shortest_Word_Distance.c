/*
  https://leetcode.com/problems/shortest-word-distance/
  243. Shortest Word Distance
  Given a list of words and two words word1 and word2, return the shortest distance
  between these two words in the list.
  Example:
  Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
  Input: word1 = "coding", word2 = "practice"
  Output: 3
  Input: word1 = "makes", word2 = "coding"
  Output: 1
  Note:
  You may assume that word1 does not equal to word2, and word1 and word2 are both in the list.
  Date : 12/27/2020 Sunday. San Diego, CA.
***/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))

int shortestDistance(char ** words, int wordsSize, char * word1, char * word2){
  int i1 = -1, i2 = -1;
  int minDistance = wordsSize;
  for (int i = 0; i < wordsSize; i++) {
    if (!strncmp(words[i], (word1), strlen(word1) )) {
      i1 = i;
    } else if (!strncmp(words[i], (word2) , strlen(word2))) {
      i2 = i;
    }

    if (i1 != -1 && i2 != -1) {
      minDistance = min(minDistance, abs(i1 - i2));
    }
  }
  return minDistance;
}

int main() {
  char *words[5] = {"practice", "makes", "perfect", "coding", "makes"};
  char word1[] = "coding";
  char word2[] = "practice";
  int wordsSize = 5;
  printf ("[%s] Output = %d\n", __func__, shortestDistance(words, wordsSize, word1, word2));

  return 1;
}
