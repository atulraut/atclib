/***
    Basic Hash Map

    https://chatgpt.com/c/6ae8ed63-1868-83e8-a94b-60db143a1c62

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Wed Nov 18 22:46:18 PST 2026
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

#define debug(str,args...) printf("L=[%d][%s]->[%s] :| "str"\n",__LINE__,__FILE__, __func__, ##args)

#define SIZE 10

typedef struct Node {
  int key;
  int value;
  struct Node *next;
} Node;

/* Hash table: array of linked lists */
Node *hashTable[SIZE] = {NULL};

/* Calculate bucket index */
int hash(int key) {
  int index = key % SIZE;
  return index < 0 ? index + SIZE : index;
}

/* Insert or update a key */
bool insert(int key, int value) {
  int index = hash(key);

  Node *curr = hashTable[index];

  // Check whether key already exists
  while (curr != NULL) {
    if (curr->key == key) {
      curr->value = value; // Update value
      return true;
    }
    curr = curr->next;
  }

  // Key not found, create a new node
  Node *newNode = malloc(sizeof(Node));

  if (newNode == NULL)
    return false;

  newNode->key = key;
  newNode->value = value;

  // Insert at beginning of linked list
  newNode->next = hashTable[index];
  hashTable[index] = newNode;

  return true;
}

/* Find value by key */
bool find(int key, int *value) {
  int index = hash(key);

  Node *curr = hashTable[index];

  while (curr != NULL) {
    if (curr->key == key) {
      *value = curr->value;
      return true;
    }
    curr = curr->next;
  }

  return false;
}

/* Delete node by key */
bool deleteKey(int key) {
  int index = hash(key);

  Node *curr = hashTable[index];
  Node *prev = NULL;

  while (curr != NULL) {
    if (curr->key == key) {

      if (prev == NULL)
	hashTable[index] = curr->next;
      else
	prev->next = curr->next;

      free(curr);
      return true;
    }

    prev = curr;
    curr = curr->next;
  }

  return false;
}

/* Print find result */
void printFind(int key) {
  int value;

  if (find(key, &value))
    printf("Find(%d) = %d\n", key, value);
  else
    printf("Find(%d) = Not Found\n", key);
}

/* Release allocated memory */
void cleanup(void) {
  for (int i = 0; i < SIZE; i++) {
    Node *curr = hashTable[i];

    while (curr != NULL) {
      Node *next = curr->next;
      free(curr);
      curr = next;
    }

    hashTable[i] = NULL;
  }
}

int test(void) {
  insert(10, 10);
  insert(1, 12);
  insert(100, 20);

  printFind(10);

  insert(10, 20);  // Update existing key

  printFind(20);

  deleteKey(10);

  printFind(10);
  printFind(30);

  cleanup();
  return 0;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**
   Find(10) = 10
   Find(20) = Not Found
   Find(10) = Not Found
   Find(30) = Not Found
**/
