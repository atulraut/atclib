/***
    https://leetcode.com/problems/stream-of-characters/
    Hard: Stream of Characters

    Design an algorithm that accepts a stream of characters and checks
    if a suffix of these characters is a string of a given array of strings words.

    For example, if words = ["abc", "xyz"] and the stream added the four characters
    (one by one) 'a', 'x', 'y', and 'z', your algorithm should detect that the suffix
    "xyz" of the characters "axyz" matches "xyz" from words.

    Implement the StreamChecker class:

    StreamChecker(String[] words) Initializes the object with the strings array
    words.
    boolean query(char letter) Accepts a new character from the stream and
    returns true if any non-empty suffix from the stream forms a word that is in words.

    Input
    ["StreamChecker", "query", "query", "query", "query", "query", "query", "query", "query", "query", "query", "query", "query"]
    [[["cd", "f", "kl"]], ["a"], ["b"], ["c"], ["d"], ["e"], ["f"], ["g"], ["h"], ["i"], ["j"], ["k"], ["l"]]
    Output
    [null, false, false, false, true, false, true, false, false, false, false, false, true]

    Explanation
    StreamChecker streamChecker = new StreamChecker(["cd", "f", "kl"]);
    streamChecker.query("a"); // return False
    streamChecker.query("b"); // return False
    streamChecker.query("c"); // return False
    streamChecker.query("d"); // return True, because 'cd' is in the wordlist
    streamChecker.query("e"); // return False
    streamChecker.query("f"); // return True, because 'f' is in the wordlist
    streamChecker.query("g"); // return False
    streamChecker.query("h"); // return False
    streamChecker.query("i"); // return False
    streamChecker.query("j"); // return False
    streamChecker.query("k"); // return False
    streamChecker.query("l"); // return True, because 'kl' is in the wordlist

    Constraints:
    1 <= words.length <= 2000
    1 <= words[i].length <= 2000
    words[i] consists of lowercase English letters.
    letter is a lowercase English letter.
    At most 4 * 104 calls will be made to query.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 12/4/2021
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

#define MAX_SIZE 2000

typedef struct Node {
  struct Node *children[26];
  bool isWord;
} Node;

typedef struct {
  Node *root;
  char *str;
  int count;
} StreamChecker;

Node *createNode() {
  Node *node = malloc(sizeof(Node));
  node->isWord = false;
  for (int i = 0; i < 26; i++) {
    node->children[i] = NULL;
  }
  return node;
}

void addWord(Node *root, char *word) {
  Node *node = root;
  for (char *ptr = word; *ptr != '\0'; ptr++) {
    char c = *ptr;
    if (!node->children[c - 'a']) {
      node->children[c - 'a'] = createNode();
    }
    node = node->children[c - 'a'];
  }
  node->isWord = true;
}

bool findWord(Node *root, const char *word, int start) {
  Node *node = root;
  while (start >= 0) {
    char c = word[start];
    if (!node->children[c - 'a']) {
      return false;
    }
    node = node->children[c - 'a'];
    if (node->isWord) {
      return true;
    }
    start--;
  }
  return false;
}

void reverse(char *word) {
  int left = 0, right = strlen(word) - 1;
  while (left < right) {
    char tmp = word[left];
    word[left] = word[right];
    word[right] = tmp;
    left++;
    right--;
  }
  debug ("reached!");
}

char *createString() {
  char *str = malloc(sizeof(char) * (MAX_SIZE + 2));
  memset(str, 0, MAX_SIZE + 2);
  return str;
}

StreamChecker *streamCheckerCreate(char **words, int wordsSize) {
  StreamChecker *checker = malloc(sizeof(StreamChecker));
  checker->root = createNode();
  checker->str = createString();
  checker->count = 0;
  for (int i = 0; i < wordsSize; i++) {
    debug ("reached! = %s", words[i]);
    reverse(words[i]);
    debug ("reached!");
    addWord(checker->root, words[i]);
    debug ("reached!");
  }
  debug ("reached!");
  return checker;
}

bool streamCheckerQuery(StreamChecker *obj, char letter) {
  if (obj->count >= MAX_SIZE) {
    free(obj->str);
    obj->count = 0;
    obj->str = createString();
  }
  obj->str[obj->count++] = letter;
  int count = obj->count;
  return findWord(obj->root, obj->str, count - 1);
}

void freeTrie(Node *root) {
  if (root == NULL) {
    return;
  }
  for (int i = 0; i < 26; i++) {
    if (root->children[i]) {
      freeTrie(root->children[i]);
    }
  }
  free(root);
}

void streamCheckerFree(StreamChecker *obj) {
  freeTrie(obj->root);
  free(obj->str);
  free(obj);
}

int main (int argc, char **argv) {
  int ret = 0;
  char str1[] = "cd";
  char str2[] = "f";
  char str3[] = "kl";

  char* str[] = {str1, str2, str3};
  int len = 3;
  StreamChecker* streamChecker = streamCheckerCreate(str, len);
  ret = streamCheckerQuery(streamChecker, 'a'); // return False
  debug("Output = %d", ret);
  ret = streamCheckerQuery(streamChecker, 'b'); // return False
  debug("Output = %d", ret);
  ret = streamCheckerQuery(streamChecker, 'c'); // return False
  debug("Output = %d", ret);
  ret = streamCheckerQuery(streamChecker, 'd'); // return True, because 'cd' is in the wordlist
  debug("Output = %d", ret);
  ret = streamCheckerQuery(streamChecker, 'e'); // return False
  debug("Output = %d", ret);
  ret = streamCheckerQuery(streamChecker, 'f'); // return True, because 'f' is in the wordlist
  debug("Output = %d", ret);
  ret = streamCheckerQuery(streamChecker, 'g'); // return False
  debug("Output = %d", ret);
  ret = streamCheckerQuery(streamChecker, 'h'); // return False
  debug("Output = %d", ret);
  ret = streamCheckerQuery(streamChecker, 'i'); // return False
  debug("Output = %d", ret);
  ret = streamCheckerQuery(streamChecker, 'j'); // return False
  debug("Output = %d", ret);
  ret = streamCheckerQuery(streamChecker, 'k'); // return False
  debug("Output = %d", ret);
  ret = streamCheckerQuery(streamChecker, 'l'); // return True, because 'kl' is in the wordlist
  debug("Output = %d", ret);

  streamCheckerFree(streamChecker);
  return 0;
}

/**
   => ./a.out
   [streamCheckerCreate] L=153 :reached! = cd
   [reverse] L=138 :reached!
   [streamCheckerCreate] L=155 :reached!
   [streamCheckerCreate] L=157 :reached!
   [streamCheckerCreate] L=153 :reached! = f
   [reverse] L=138 :reached!
   [streamCheckerCreate] L=155 :reached!
   [streamCheckerCreate] L=157 :reached!
   [streamCheckerCreate] L=153 :reached! = kl
   [reverse] L=138 :reached!
   [streamCheckerCreate] L=155 :reached!
   [streamCheckerCreate] L=157 :reached!
   [streamCheckerCreate] L=159 :reached!
   [main] L=202 :Output = 0
   [main] L=204 :Output = 0
   [main] L=206 :Output = 0
   [main] L=208 :Output = 1
   [main] L=210 :Output = 0
   [main] L=212 :Output = 1
   [main] L=214 :Output = 0
   [main] L=216 :Output = 0
   [main] L=218 :Output = 0
   [main] L=220 :Output = 0
   [main] L=222 :Output = 0
   [main] L=224 :Output = 1
**/
