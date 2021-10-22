/***
    https://leetcode.com/problems/sort-characters-by-frequency/
    Sort Characters By Frequency

    Given a string s, sort it in decreasing order based on the
    frequency of the characters. The frequency of a character
    is the number of times it appears in the string.

    Return the sorted string. If there are multiple answers,
    return any of them.

    Input: s = "tree"
    Output: "eert"
    Explanation: 'e' appears twice while 'r' and 't' both appear once.
    So 'e' must appear before both 'r' and 't'.
    Therefore "eetr" is also a valid answer.

    Input: s = "cccaaa"
    Output: "aaaccc"
    Explanation: Both 'c' and 'a' appear three times, so
    both "cccaaa" and "aaaccc" are valid answers.
    Note that "cacaca" is incorrect, as the same characters
    must be together.

    Input: s = "Aabb"
    Output: "bbAa"
    Explanation: "bbaA" is also a valid answer,
    but "Aabb" is incorrect.
    Note that 'A' and 'a' are treated as two different characters.

    Constraints:
    1 <= s.length <= 5 * 105
    s consists of uppercase and lowercase English letters and digits.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address frequencySort.c -lm

    Date: 22102021 Oct
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
#define atsizeof(object) (char *)(&object+1) - (char*)(&object)
#define max(a,b)				\
  ({ typeof (a) _a = (a);			\
    typeof (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ typeof (a) _a = (a);			\
    typeof (b) _b = (b);			\
    _a < _b ? _a : _b; })

char* frequencySort(char* s) {
  int map[126] = {0};
  int i,mem_size=0;

  for(i=0; s[i]; i++)
    map[s[i]-' ']++;

  for(i=0; i<126; i++)
    mem_size+=map[i];

  char *res = (char*)calloc(mem_size+1,sizeof(char));
  int index;
  int w=0;

  while(mem_size) {
    int max = 1;
    for(i=0; i<126; i++) {
      if(map[i]>=max)
	index=i,max=map[i];
    }

    map[index]=0;
    while(max)
      res[w] = index+' ',mem_size--,max--,w++;
  }
  return res;
}

//int cmpLetters(const void* a, const void* b);

int cmpLetters(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

unsigned int times[256];

char* frequencySort1(unsigned char* s) {
    unsigned char letters[256];
    unsigned int i, j, k, lnum;

    // Init occurrences as 0
    memset(times, 0, sizeof(times));

    for (i = lnum = 0; s[i] != '\0'; i++)
        if (times[s[i]]++ == 0)
            letters[lnum++] = s[i];

    // Sort letters by number of occurrences
    qsort(letters, lnum, sizeof(char), cmpLetters);

    char* new = malloc(sizeof(char) * (i + 1));

    for (j = k = 0; j < lnum; j++)
        for (i = 0; i < times[letters[j]]; i++)
            new[k++] = letters[j];
    new[k] = '\0';

    return new;
}
void sort_arr(char* arr, int sz) {
    int i = 1;
    int j;

    for (i=0; i<sz; ++i)
      debug ("arr[%d] = %d",i, arr[i]);

    for (i=1; i<sz; ++i) {
      int key = arr[i];
      j = i-1;
      while (j>=0 && key<arr[j]) {
	arr[j+1] = arr[j];
	--j;
      }
      arr[j+1] = key;
    }

    for (i=0; i<sz; ++i)
      debug ("arr[%d] = %d",i, arr[i]);
}

char* frequencySort2(char* s) {
  int len = strlen(s);
  sort_arr(s, len);
  return s;
}

int main (int argc, char **argv) {
  char* ret = 0;
  char s[] = "Aabb";

  ret = frequencySort(s);
  debug("Output = %s", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=124 :Output = bbaA
**/
