/***
    https://leetcode.com/problems/design-add-and-search-words-data-structure/
    Design Add and Search Words Data Structure

    Design a data structure that supports adding new words and
    finding if a string matches any previously added string.

    Implement the WordDictionary class:

    WordDictionary() Initializes the object.
    void addWord(word) Adds word to the data structure, it can be matched later.
    bool search(word) Returns true if there is any string in the data
    structure that matches word or false otherwise. word may
    contain dots '.' where dots can be matched with any letter.

    Input
    ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
    [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
    Output
    [null,null,null,null,false,true,true,true]

    Explanation
    WordDictionary wordDictionary = new WordDictionary();
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    wordDictionary.search("pad"); // return False
    wordDictionary.search("bad"); // return True
    wordDictionary.search(".ad"); // return True
    wordDictionary.search("b.."); // return True

    Constraints:

    1 <= word.length <= 500
    word in addWord consists lower-case English letters.
    word in search consist of  '.' or lower-case English letters.
    At most 50000 calls will be made to addWord and search.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 27 Jan 2022
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

typedef struct trie_node {
  struct trie_node *sub_chars[26];
  bool EOW;
} WordDictionary;

/** Initialize your data structure here. */

WordDictionary* wordDictionaryCreate() {
  WordDictionary *obj = (WordDictionary*)calloc(1,sizeof(WordDictionary));
  return obj;
}

/** Adds a word into the data structure. */
void wordDictionaryAddWord(WordDictionary* obj, char * word) {
  while((*word)) {
    if(obj->sub_chars[(*word)-'a']==NULL) {
      obj->sub_chars[(*word)-'a'] = (WordDictionary*)calloc(1,sizeof(WordDictionary));
    }
    obj = obj->sub_chars[(*word)-'a'];
    word++;
  }
  obj->EOW = true;
}

/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
bool wordDictionarySearch(WordDictionary* obj, char * word) {
  while(*word) {
    if( (*word) =='.') {
      for(int i =0;i<26;i++) {
	if(!obj->sub_chars[i]) continue;
	bool a = wordDictionarySearch(obj->sub_chars[i],word+1);
	if(a) return true;
      }
      return false;
    }
    else if(!obj->sub_chars[(*word)-'a']) return false;
    obj = obj->sub_chars[(*word)-'a'];
    word++;
  }
  if(obj->EOW)return true;
  else return false;
}

void wordDictionaryFree(WordDictionary* obj) {
  //recursivly free the memory
  for(int i=0;i<26;i++) {
    if(!obj->sub_chars[i]) continue;
    wordDictionaryFree(obj->sub_chars[i]);
  }
  free(obj);
}

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);

 * bool param_2 = wordDictionarySearch(obj, word);

 * wordDictionaryFree(obj);
 */

void test() {
  int i;
  int ret = 0;
  // Input keys (use only 'a' through 'z'
  // and lower case)
  char *insertKeys[] = {"the", "a", "there",
			"answer", "any", "by",
			"bye", "their" };
  char *searchKeys[] = {"bad", "dad", "mad", "pad", "bad", ".ad", "b.."};

  int n = sizeof(insertKeys)/sizeof(insertKeys[0]);
  int s = sizeof(searchKeys)/sizeof(searchKeys[0]);

  struct WordDictionary *root = wordDictionaryCreate();

  // Construct trie
  for (i = 0; i < n; i++)
    wordDictionaryAddWord(root, insertKeys[i]);

  // Search for different keys
  for (i = 0; i < s; i++)
    debug ("o/p - > %d", wordDictionarySearch(root, searchKeys[i]));
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   => ./a.out
   [test] L=154 :o/p - > 0
   [test] L=154 :o/p - > 0
   [test] L=154 :o/p - > 0
   [test] L=154 :o/p - > 0
   [test] L=154 :o/p - > 0
   [test] L=154 :o/p - > 0
   [test] L=154 :o/p - > 1
**/
