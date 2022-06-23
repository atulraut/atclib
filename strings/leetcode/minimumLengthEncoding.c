/***
    https://leetcode.com/problems/short-encoding-of-words/
    Short Encoding of Words

    A valid encoding of an array of words is any reference string
    s and array of indices indices such that:

    words.length == indices.length
    The reference string s ends with the '#' character.
    For each index indices[i], the substring of s starting from indices[i]
    and up to (but not including) the next '#' character is equal to words[i].

    Given an array of words, return the length of the shortest reference
    string s possible of any valid encoding of words.

    Input: words = ["time", "me", "bell"]
    Output: 10
    Explanation: A valid encoding would be s = "time#bell#" and indices = [0, 2, 5].
    words[0] = "time", the substring of s starting from indices[0] = 0 to the next '#' is underlined in "time#bell#"
    words[1] = "me", the substring of s starting from indices[1] = 2 to the next '#' is underlined in "time#bell#"
    words[2] = "bell", the substring of s starting from indices[2] = 5 to the next '#' is underlined in "time#bell#"

    Input: words = ["t"]
    Output: 2
    Explanation: A valid encoding would be s = "t#" and indices = [0].

    Constraints:
    1 <= words.length <= 2000
    1 <= words[i].length <= 7
    words[i] consists of only lowercase letters.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: June 20, 2022
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

typedef struct Node_ {
  struct Node_* next[26];
  int length;
} Node;

int findRes(Node* node) {
  int res = 0;
  for(int i = 0; i < 26; i++) {
    if(node->next[i] != NULL) {
      res += findRes(node->next[i]);
    }
  }
  return res == 0 ? node->length + 1 : res;
}

int minimumLengthEncoding(char** words, int wordsSize) {
  Node* node = malloc(sizeof(Node));
  Node* temp = node;

  for(int i = 0; i < 26; i++)
    node->next[i] = NULL;

  node->length = 0;
  for(int i = 0; i < wordsSize; i ++) {
    temp = node;
    for(int j = strlen(words[i]) - 1; j >= 0; j--) {
      if(temp->next[words[i][j] - 'a'] == NULL) {
	temp->next[words[i][j] - 'a'] = malloc(sizeof(Node));
	node->length = 0;
	for(int k = 0; k < 26; k++){
	  temp->next[words[i][j] - 'a']->next[k] = NULL;
	}
      }
      temp = temp->next[words[i][j] - 'a'];
    }
    temp->length = strlen(words[i]);
  }

  return findRes(node);
}

void test() {
  int ret = 0;
  char* words[3] = {"time", "me", "bell"};
  int wordsSize = 3;

  ret =  minimumLengthEncoding(words, wordsSize);
  debug("Output = %d", ret);
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=111 :Output = 10
**/
