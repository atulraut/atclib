/***
    Hard: 745. Prefix and Suffix Search
    Design a special dictionary which has some words and allows you to search the
    words in it by a prefix and a suffix.

    Implement the WordFilter class:

    WordFilter(string[] words) Initializes the object with the words in the
    dictionary.
    f(string prefix, string suffix) Returns the index of the word in
    the dictionary which has the prefix prefix and the suffix suffix.
    If there is more than one valid index, return the largest of them.
    If there is no such word in the dictionary, return -1.

    Input
    ["WordFilter", "f"]
    [[["apple"]], ["a", "e"]]
    Output
    [null, 0]

    Explanation
    WordFilter wordFilter = new WordFilter(["apple"]);
    wordFilter.f("a", "e"); // return 0, because the word at index 0 has
    prefix = "a" and suffix = 'e".

    Constraints:
    1 <= words.length <= 15000
    1 <= words[i].length <= 10
    1 <= prefix.length, suffix.length <= 10
    words[i], prefix and suffix consist of lower-case English letters only.
    At most 15000 calls will be made to the function f.

    https://leetcode.com/problems/prefix-and-suffix-search/
    Date: 1 May 2021
    San Diego, CA.
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

typedef struct ___TrieNode {
  size_t length;
  size_t capacity;
  size_t * arr;
  struct ___TrieNode * children[26];
} TrieNode;

void vectorPush(TrieNode * node, size_t val) {
  if (node->capacity == 0) {
    node->arr = (size_t *)malloc(4 * sizeof(size_t));
    node->capacity = 4;
  }
  if (node->length == node->capacity) {
    node->arr = (size_t *)realloc(node->arr, 2 * node->capacity * sizeof(size_t));
    node->capacity *= 2;
  }
  node->arr[node->length] = val;
  node->length += 1;
}

char const * insertStrPrefix(TrieNode ** node, char const * str, size_t weight) {
  TrieNode * curr;

  curr = *node;
  if (curr == NULL) {
    curr = (TrieNode *)calloc(1, sizeof(TrieNode));
    *node = curr;
  }
  vectorPush(curr, weight);
  if (*str == 0) {
    return str;
  }
  return insertStrPrefix(&curr->children[*str - 'a'], str + 1, weight);
}

void insertStrSuffix(TrieNode ** node, char const * str, char const * end, size_t weight) {
  TrieNode * curr;

  curr = *node;
  if (curr == NULL) {
    curr = (TrieNode *)calloc(1, sizeof(TrieNode));
    *node = curr;
  }
  vectorPush(curr, weight);
  if (str == end) {
    return;
  }
  insertStrSuffix(&curr->children[*str - 'a'], str - 1, end, weight);
}

void freeNode(TrieNode * node) {
  int i = 0;

  for (i = 0; i < 26; ++i) {
    if (node->children[i]) {
      freeNode(node->children[i]);
    }
  }
  if (node->arr) {
    free(node->arr);
  }
  free(node);
}

TrieNode * prefixFind(TrieNode * node, char const * str) {
  TrieNode * curr;

  if (*str == 0) {
    return node;
  }
  curr = node->children[*str - 'a'];
  return curr == NULL ? NULL : prefixFind(curr, str + 1);
}

TrieNode * suffixFind(TrieNode * node, char const * str, char const * end) {
  TrieNode * curr;

  if(strcmp(str, end) == 0)
    return node;
  curr = node->children[*str - 'a'];
  return curr == NULL ? NULL : suffixFind(curr, str - 1, end);
}

size_t vectorMax(TrieNode * l, TrieNode * r, size_t weight) {
  TrieNode * search, * match;
  size_t i, j, val;

  if (l->length == 0 || r->length == 0) {
    return 0;
  }
  if (l->length <= r->length) {
    search = l;
    match = r;
  } else {
    search = r;
    match = l;
  }
  for (i = search->length - 1; i != ~0; i -= 1) {
    val = search->arr[i];
    for (j = match->length - 1; j != ~0; j -= 1) {
      if (val < match->arr[j]) {
	continue;
      }
      if (val > match->arr[j]) {
	break;
      }
      return val;
    }
  }
  return weight;
}

typedef struct {
  TrieNode * prefixRoot;
  TrieNode * suffixRoot;
} WordFilter;

WordFilter* wordFilterCreate(char const * const * words) {
  WordFilter * obj;
  TrieNode * prefixRoot = NULL, *suffixRoot = NULL;
  size_t i = 1;
  char * end;

  for (i = 1; *words != NULL; words += 1, i += 1) {
    for (end = *words; *end != 0; end += 1) {
      if (*end < 'a' - 1 || *end > 'z' + 1) {
	goto DONE;
      }
    }
    end = insertStrPrefix(&prefixRoot, *words, i) - 1;
    insertStrSuffix(&suffixRoot, end, *words - 1, i);
  }
  //for (string const & word : words) {
  //    end = insertStrPrefix(&prefixRoot, (char *)word.c_str(), i) - 1;
  //    insertStrSuffix(&suffixRoot, end, (char *)word.c_str() - 1, i);
  //    i += 1;
  //}
 DONE:

  obj = (WordFilter *)malloc(sizeof(WordFilter));
  obj->prefixRoot = prefixRoot;
  obj->suffixRoot = suffixRoot;
  return obj;
}

int wordFilterF(WordFilter * obj, char const * prefix, char const * suffix) {
  TrieNode * prefixNode, * suffixNode;
  char * end;

  for (end = prefix; *end != 0; end += 1) {
    if (*end < 'a' - 1 || *end > 'z' + 1) {
      return -1;
    }
  }
  for (end = suffix; *end != 0; end += 1) {
    if (*end < 'a' - 1 || *end > 'z' + 1) {
      return -1;
    }
  }
  prefixNode = prefixFind(obj->prefixRoot, prefix);
  suffixNode = suffixFind(obj->suffixRoot, suffix + strlen(suffix) - 1, suffix - 1);
  if (prefixNode == NULL || suffixNode == NULL) {
    return -1;
  }
  return ((int)vectorMax(prefixNode, suffixNode, 0)) - 1;
}

void wordFilterFree(WordFilter * obj) {
  freeNode(obj->prefixRoot);
  freeNode(obj->suffixRoot);
  free(obj);
  printf("AFTER RUN\n");
}

/**
 * Your WordFilter struct will be instantiated and called as such:
 * struct WordFilter* obj = wordFilterCreate(words);
 * int param_1 = wordFilterF(obj, prefix, suffix);
 * wordFilterFree(obj);
 */

int main () {
  int ret = 0;

  debug("Output = ");
  return 0;
}

/**

 **/
