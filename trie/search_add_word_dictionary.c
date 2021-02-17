/***
    Leetcode: Add and Search Word - Data structure design
    https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/549/week-1-august-1st-august-7th/3413/
    https://www.youtube.com/watch?v=h-F2jRUzpBo
    https://www.geeksforgeeks.org/trie-insert-and-search/
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const int ALPHABET_SIZE = 26;

// trie node
typedef struct WordDictionary {
  struct WordDictionary *children[26];

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
} WordDictionary;

// Returns new trie node (initialized to NULLs)
//struct WordDictionary *getNode(void) {
WordDictionary* wordDictionaryCreate() {
    struct WordDictionary *pNode =  (WordDictionary*) malloc(sizeof(WordDictionary));

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
/** Adds a word into the data structure. */
void wordDictionaryAddWord(struct WordDictionary *root, char *word) {
    struct WordDictionary *trav = root;

    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!trav->children[index])
          trav->children[index] = wordDictionaryCreate();//getNode();

        trav = trav->children[index];
    }

    // mark last node as leaf
    trav->isEndOfWord = true;
}

// Returns true if key presents in trie, else
// false
/***
     Returns if the word is in the data structure. A word could contain the dot character '.'
     to represent any one letter.
*/
bool wordDictionarySearch(struct WordDictionary *root, char *word) {
    struct WordDictionary *trav = root;

    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
	printf ("[%s] index = %d L=%d \n", __func__, index, __LINE__);
        if (!trav->children[index])
            return false;

        trav = trav->children[index];
    }

    return (trav != NULL && trav->isEndOfWord);
}

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);

 * bool param_2 = wordDictionarySearch(obj, word);

 * wordDictionaryFree(obj);
*/
int main() {
  int i;
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
      printf ("o/p - > %d \n", wordDictionarySearch(root, searchKeys[i]));
    return 0;
}
