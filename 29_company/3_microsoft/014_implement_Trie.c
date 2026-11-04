/***
    Implement a CSV/log query engine

    https://chatgpt.com/c/6ae8cb5d-403c-83e8-9b68-f7b158dc0dee
    - inbox2137@gmail.com

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Mon Nov  2 09:36:41 PST 2026
    Folsom, CA.
 */

/*----------------------------------- Header --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> // va_arg
#include <ctype.h>
#include <limits.h>
#include <string.h>  /* malloc */
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdint.h> /* uint32_t */
#include <unistd.h> /* sleep */
#include <stdbool.h>

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

#define ALPHABET_SIZE 26

typedef struct TrieNode {
  struct TrieNode *children[ALPHABET_SIZE];
  bool is_word;
} TrieNode;

/* Allocate and initialize a Trie node */
static TrieNode *node_create(void) {
  return calloc(1, sizeof(TrieNode));
}

/* Accept lowercase a-z; empty strings are allowed */
static bool valid_key(const char *key) {
  if (!key)
    return false;

  for (const unsigned char *p = (const unsigned char *)key; *p; ++p) {
    if (*p < 'a' || *p > 'z')
      return false;
  }

  return true;
}

/* Recursively free an entire Trie */
void trie_destroy(TrieNode *node) {
  if (!node)
    return;

  for (int i = 0; i < ALPHABET_SIZE; i++)
    trie_destroy(node->children[i]);

  free(node);
}

/* Insert a word */
bool trie_insert(TrieNode *root, const char *word) {
  if (!root || !valid_key(word))
    return false;

  TrieNode *cur = root;
  TrieNode *first_new_parent = NULL;
  int first_new_index = 0;

  for (const char *p = word; *p; ++p) {
    int index = *p - 'a';

    /* Create node if character path is missing */
    if (cur->children[index] == NULL) {
      TrieNode *new_node = node_create();

      if (!new_node) {
	/* Roll back new branch on failure */
	if (first_new_parent) {
	  trie_destroy(first_new_parent->children[first_new_index]);
	  first_new_parent->children[first_new_index] = NULL;
	}
	return false;
      }

      cur->children[index] = new_node;

      if (!first_new_parent) {
	first_new_parent = cur;
	first_new_index = index;
      }
    } // 1st if ends

    cur = cur->children[index];
  } // for ends

  /* Mark complete word */
  cur->is_word = true;
  return true;
}

/* Find node corresponding to a string */
static const TrieNode *trie_find_node(const TrieNode *root, const char *key) {
  if (!root || !valid_key(key))
    return NULL;

  const TrieNode *cur = root;

  for (const char *p0 = key; *p; ++p) {
    int index = *p - 'a';

    cur = cur->children[index];

    if (!cur)
      return NULL;
  }

  return cur;
}

/* Search for an exact word */
bool trie_search(const TrieNode *root, const char *word) {
  const TrieNode *node = trie_find_node(root, word);

  return node != NULL && node->is_word;
}

/* Search for a prefix */
bool trie_starts_with(const TrieNode *root, const char *prefix) {
  return trie_find_node(root, prefix) != NULL;
}

/* Check whether node has any children */
static bool has_children(const TrieNode *node) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (node->children[i])
      return true;
  }
  return false;
}

/* Return true if caller can safely free this node */
static bool delete_recursive(TrieNode *node, const char *word, size_t depth, bool *removed) {
  if (word[depth] == '\0') {
    if (!node->is_word)
      return false;

    node->is_word = false;
    *removed = true;
  } else {
    int index = word[depth] - 'a';
    TrieNode *child = node->children[index];

    if (!child)
      return false;

    if (delete_recursive(child, word, depth + 1, removed)) {
      free(child);
      node->children[index] = NULL;
    }
  }

  return !node->is_word && !has_children(node);
}

/* Delete a word while preserving shared prefixes */
bool trie_delete(TrieNode *root, const char *word) {
  if (!root || !valid_key(word))
    return false;

  bool removed = false;

  /* Root remains allocated */
  (void)delete_recursive(root, word, 0, &removed);

  return removed;
}

int test(void) {
  TrieNode *trie = node_create();

  if (!trie)
    return EXIT_FAILURE;

  const char *words[] = {"cat", "car", "cart", "dog"
  };

  size_t count = sizeof(words) / sizeof(words[0]);

  for (size_t i = 0; i < count; i++) {
    if (!trie_insert(trie, words[i])) {
      fprintf(stderr, "Insert failed: %s\n", words[i]);
      trie_destroy(trie);
      return EXIT_FAILURE;
    }
  }

  printf("search(car)     = %d\n", trie_search(trie, "car"));

  printf("search(cap)     = %d\n", trie_search(trie, "cap"));

  printf("starts_with(ca) = %d\n", trie_starts_with(trie, "ca"));

  printf("delete(car)     = %d\n", trie_delete(trie, "car"));

  printf("search(car)     = %d\n", trie_search(trie, "car"));

  printf("search(cart)    = %d\n", trie_search(trie, "cart"));

  printf("search(cat)     = %d\n", trie_search(trie, "cat"));

  trie_destroy(trie);

  return EXIT_SUCCESS;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   search(car)     = 1
   search(cap)     = 0
   starts_with(ca) = 1
   delete(car)     = 1
   search(car)     = 0
   search(cart)    = 1
   search(cat)     = 1
 **/
