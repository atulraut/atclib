/***
    https://leetcode.com/problems/implement-trie-prefix-tree/
    Implement Trie (Prefix Tree)

    A trie (pronounced as "try") or prefix tree is a tree
    data structure used to efficiently store and retrieve
    keys in a dataset of strings. There are various
    applications of this data structure, such as autocomplete
    and spellchecker.

    Implement the Trie class:

    Trie() Initializes the trie object.
    void insert(String word) Inserts the string word into
    the trie.
    boolean search(String word) Returns true if the string
    word is in the trie (i.e., was inserted before), and
    false otherwise.
    boolean startsWith(String prefix) Returns true if there
    is a previously inserted string word that has the prefix
    prefix, and false otherwise.

    Input
    ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
    [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
    Output
    [null, null, true, false, true, null, true]

    Explanation
    Trie trie = new Trie();
    trie.insert("apple");
    trie.search("apple");   // return True
    trie.search("app");     // return False
    trie.startsWith("app"); // return True
    trie.insert("app");
    trie.search("app");     // return True

    Constraints:
    1 <= word.length, prefix.length <= 2000
    word and prefix consist only of lowercase English letters.
    At most 3 * 104 calls in total will be made to insert, search,
    and startsWith.

    Date: 10/8/2021 - 108 Hindu Magic Number
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

typedef struct trie {
    struct trie *next;
    char hasResult;
    char *remaining;
} Trie;

/** Initialize your data structure here. */

Trie* trieCreate() {
    Trie *t = calloc(1, sizeof *t);
    return t;
}

/** Inserts a word into the trie.

apple
a

obj->remaining == NULL
obj->remaining == apple

app

a
strcmp(remaining, app) == 0
obj->next == NULL
obj->next = malloc(26)
obj->next[a] with pple

obj->remaining == NULL
obj->remaining = pple

obj->next[a] wit pp

*/
void trieInsert(Trie* obj, char * word) {
 //   printf("TrieInsert: %p, %s\n", obj, word);
    for(;;) {
        if (*word == '\0') {
            obj->hasResult = 1;
            return;
        }
        if (obj->remaining == NULL) {
            obj->remaining = word;
            return;
        }
        if (obj->next == NULL) {
   //         printf("Here comparing '%.20s' with '%.20s' and getting '%d'\n", obj->remaining, word, strcmp(obj->remaining, word));
            if (strcmp(obj->remaining, word) == 0) return;
            obj->next = calloc(26, sizeof *obj);
            trieInsert(obj->next + obj->remaining[0] - 'a', obj->remaining + 1);
        }
        obj = obj->next + word[0] - 'a';
        word++;
    }
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char * word) {
//    printf("TrieSearch: %p, %s\n", obj, word);
    for (;;) {
        if (*word == '\0') {
            return obj->hasResult;
        }
        if (obj->remaining == NULL) return 0;
        if (obj->next == NULL) {
//            printf("Here comparing '%s' with '%s'\n", word, obj->remaining);
           return strcmp(word, obj->remaining) == 0;
        }
        obj = obj->next + word[0] - 'a';
        word++;
    }
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char * prefix) {
 //   printf("TrieStartsWith: %p, %s\n", obj, prefix);
    for (;;) {
        if (*prefix == '\0') return obj->remaining != NULL || obj->hasResult;
        if (obj->remaining && obj->next == NULL) {
            char *r = obj->remaining;
            while (*prefix != '\0' && *r != '\0' && *prefix == *r) {prefix++; r++;}
            return *prefix == '\0';
        }
        if (obj->next == NULL) return 0;
        obj = obj->next + prefix[0] - 'a';
        prefix++;
    }
}

void _trieFree(Trie* obj) {
    if (obj->next == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        _trieFree(obj->next + i);
    }
    free(obj->next);
}


void trieFree(Trie* obj) {
 //   _trieFree(obj);
    // Only the root node is directly alloc'ed
 //   free(obj);
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);

 * bool param_2 = trieSearch(obj, word);

 * bool param_3 = trieStartsWith(obj, prefix);

 * trieFree(obj);
*/

int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
