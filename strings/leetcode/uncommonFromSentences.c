/***
    https://leetcode.com/problems/uncommon-words-from-two-sentences/
    Uncommon Words from Two Sentences

    A sentence is a string of single-space separated words where
    each word consists only of lowercase letters.

    A word is uncommon if it appears exactly once in one of the
    sentences, and does not appear in the other sentence.

    Given two sentences s1 and s2, return a list of all the uncommon
    words. You may return the answer in any order.

    Input: s1 = "this apple is sweet", s2 = "this apple is sour"
    Output: ["sweet","sour"]

    Input: s1 = "apple apple", s2 = "banana"
    Output: ["banana"]

    Constraints:
    1 <= s1.length, s2.length <= 200
    s1 and s2 consist of lowercase English letters and spaces.
    s1 and s2 do not have leading or trailing spaces.
    All the words in s1 and s2 are separated by a single space.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address uncommonFromSentences.c -lm

    Date: 27 Oct 2021
    Fair Oaks, CA.
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
// Hash Map

#define SIZE 229

typedef struct Node
{
  char *key;
  int val;
  struct Node *next;
} Node;

typedef struct HTable
{
  struct Node **arr;
} HTable;

HTable *create()
{
  HTable *ht = calloc(1, sizeof(HTable));
  ht->arr = calloc(SIZE, sizeof(Node *));

  return ht;
}

unsigned long hash(unsigned char *str)
{
  unsigned long hash = 5381;
  int c;

  while (c = *str++)
    hash = ((hash << 5) + hash) + c;

  return hash % SIZE;
}

void insert(HTable *ht, char *key, int val)
{
  int index = hash(key);
  Node *temp = ht->arr[index];

  if (temp == NULL)
    {
      temp = calloc(1, sizeof(Node));
      temp->key = calloc(strlen(key) + 1, sizeof(char));
      strcpy(temp->key, key);
      temp->val = 1;
      ht->arr[index] = temp;
      return;
    }

  while (temp != NULL)
    {
      if (!strcmp(temp->key, key))
        {
	  temp->val++;
	  return;
        }

      temp = temp->next;
    }

  Node *newNode = calloc(1,sizeof(Node));
  newNode->key = calloc(strlen(key) + 1, sizeof(char));
  strcpy(newNode->key, key);
  newNode->val = 1;
  newNode->next = ht->arr[index];
  ht->arr[index] = newNode;
}

char **uncommonFromSentences(char *A, char *B, int *returnSize)
{
  *returnSize = 0;
  char **res = NULL;

  HTable *ht = create();

  char *str = malloc(sizeof(char) * (strlen(A) + strlen(B) + 2));
  strcpy(str, A);
  strcat(str, " ");
  strcat(str, B);

  char *token = strtok(str, " ");
  while (token)
    {
      insert(ht, token, 1);
      token = strtok(NULL, " ");
    }

  for (int i = 0; i < SIZE; i++)
    {
      Node *temp = ht->arr[i];

      if (temp == NULL)
	continue;

      while (temp)
        {
	  if (temp->val == 1)
            {
	      (*returnSize)++;
	      res = realloc(res, sizeof(char *) * (*returnSize));
	      res[*returnSize - 1] = calloc(strlen(temp->key) + 1, sizeof(char));
	      strcpy(res[*returnSize - 1], temp->key);
            }

	  temp = temp->next;
        }
    }

  return res;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** uncommonFromSentences_Optimal(char * s1, char * s2, int* returnSize){
  int id = 0;
  int uncommon[500];
  memset(uncommon, 1, sizeof(int) * 500);
  char** output = (char**)malloc(sizeof(char*) * 500);
  while(*s1){
    while(*s1 && *s1 == ' ')
      s1 ++;
    output[id] = (char*)malloc(50);
    memset(output[id], '\0', 50);
    while(*s1 && isalpha(*s1)){
      strncat(output[id], s1, 1);
      s1 ++;
    }
    int flag = 1;
    for(int i=0; i<id; i++){
      int res = strcmp(output[id], output[i]);
      if(!res){
	flag = 0;
	free(output[id]);
	uncommon[i] = 0;
	break;
      }
    }
    if(flag)
      id ++;
    continue;
  }
  while(*s2){
    while(*s2 && *s2 == ' ')
      s2 ++;
    output[id] = (char*)malloc(50);
    memset(output[id], '\0', 50);
    while(*s2 && isalpha(*s2)){
      strncat(output[id], s2, 1);
      s2 ++;
    }
    int flag = 1;
    for(int i=0; i<id; i++){
      int res = strcmp(output[id], output[i]);
      if(!res){
	flag = 0;
	free(output[id]);
	uncommon[i] = 0;
	break;
      }
    }
    if(flag)
      id ++;
    continue;
  }
  char** res = (char**)malloc(sizeof(char*) * 500);
  int cnt = 0;
  for(int i=0; i<id; i++){
    if(uncommon[i]){
      res[cnt++] = output[i];
    }
  }
  *returnSize = cnt;
  return res;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** uncommonFromSentences_AR(char* s1, char* s2, int* returnSize) {
  int i=-1, j=-1, m=0, n=0;
  int startIndex = -1;
  char* this_s1 = (char*)malloc(sizeof(char) * strlen(s1+1));
  char* this_s2 = (char*)malloc(sizeof(char) * strlen(s1+1));
  int cnt1=0, cnt2 = 0;

  char* buf1 = s1;
  char* buf2 = s2;
  char* end1 = buf1;
  char* end2 = buf2;
  char* x1 = buf1;
  char* y1 = buf1;
  char* x2 = buf2;
  char* y2 = buf2;

  for(end1=buf1; *end1; end1++)
    ;
  for(end2=buf2; *end2; end2++)
    ;
  x1 = buf1-1;
  y1 = buf1;
  x2 = buf2-1;
  y2 = buf2;

  while (x1++ < end1 || x2++ < end2) {

    if (*x1 != ' ' || *x1 == '\0') {
      cnt1++;
      debug ("y1=%s", y1+cnt1);
      y1 = x1 + 1; // skip space

    }
    if (*x2 != ' ' || *x2 == '\0') {
      cnt2++;
      debug ("y2=%s", y2+cnt2);
      y2 = x2 + 1; // skip space
    }

    debug("strncmp = %d", strncmp(y1, y2, cnt1));
  }
  debug ("Reached!");
}

int main (int argc, char **argv) {
  char** ret;
  char s1[] = "this apple is swee";//"apple apple";
  char s2[] = "this apple is sour";//"banana";
  int returnSize;

  ret =  uncommonFromSentences(s1, s2, &returnSize);
  //  debug("Output = %d", ret);
  return 0;
}

/**

 **/
