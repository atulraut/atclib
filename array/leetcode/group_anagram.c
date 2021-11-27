/***
    Medium: Group Anagrams

    Given an array of strings strs, group the anagrams together. You can
    return the answer in any order.

    An Anagram is a word or phrase formed by rearranging the letters of a differen
    word or phrase, typically using all the original letters exactly once.

    Input: strs = ["eat","tea","tan","ate","nat","bat"]
    Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

    Input: strs = [""]
    Output: [[""]]

    Input: strs = ["a"]
    Output: [["a"]]

    Constraints:

    1 <= strs.length <= 104
    0 <= strs[i].length <= 100
    strs[i] consists of lower-case English letters.

    https://leetcode.com/problems/group-anagrams/
    Date: 27 April 2021
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
#include <uthash.h> /* UT_hash_handle */

#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
struct StringHash {
  long hashvalue;
  int col;
  char** list;
  UT_hash_handle hh;
};

long GetHash(char* str) {

  if(str == NULL)
    return INT_MIN;
  unsigned long hash = 5381;
  int c;
  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

int cmpfunc(void* a, void* b) {
  char* aa= (char*)a;
  char* bb = (char*)b;

  return ((*aa)-(*bb));

}

int cstring_cmp(const void *a, const void *b) {
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return strcmp(*ia, *ib);
  /* strcmp functions works exactly as expected from
     comparison function */


char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
  if(strs == NULL || strsSize == 0) {
    *returnSize =0;
    return NULL;
  }

  char*** str = NULL;
  if(strsSize ==1 && strcmp(strs[0], "") ==0) {
    *returnSize =1;
    *returnColumnSizes = (int*)calloc(1, sizeof(int));
    returnColumnSizes[0][0] = 1;
    str = (char***)calloc(1, sizeof(char**));
    *str = &strs[0];
    return (char***)str;
  }


  //qsort(strs, strsSize, sizeof(char*), cstring_cmp);
  long hashval =0;

  struct StringHash* set = NULL;
  struct StringHash* element;


  *returnSize =0;

  for(int i =0; i < strsSize; i++) {
    int len =strlen(strs[i]);
    char* tmpstr = calloc(len+1, sizeof(char));
    if(tmpstr == NULL)
      return NULL;

    strcpy(tmpstr, strs[i]);
    qsort(tmpstr, len, sizeof(char), cmpfunc);

    hashval= GetHash(tmpstr);
    // printf("Hash %ld", hashval);
    free(tmpstr);

    HASH_FIND_INT(set, &hashval, element);

    if(element) {

      element->list = realloc(element->list, (++element->col) * sizeof(char **));
      element->list[element->col - 1] = strs[i];
    } else {
      //Add hash to hashmap
      element = (struct StringHash *) calloc(1, sizeof(struct StringHash));
      element->hashvalue = hashval;

      element->col = 1;

      element->list = calloc(1, sizeof(char **));
      element->list[element->col-1] = strs[i];
      HASH_ADD_INT(set, hashvalue, element);
    }
  }

  *returnSize = HASH_COUNT(set);

  str = calloc(*returnSize,  sizeof(char **));
  *returnColumnSizes = calloc(*returnSize,  sizeof(int));

  int mapIndx =0;
  /* Destroy the hashset */
  struct StringHash* curr;
  struct StringHash* tmp;
  HASH_ITER(hh, set, curr, tmp)
    {
      (*returnColumnSizes)[mapIndx] = curr->col;
      str[mapIndx++] = curr->list;

      HASH_DEL(set, curr);
      free(curr);
    }
  return str;
}

int main() {
  char *arr[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
  int sz = 5;
  int retsz;
  int *retCsz;
  char ***op;
  op = groupAnagrams(arr, sz, &retsz, &retCsz);
  for(int i=0; i<retsz; i++) {
    printf ("--> %s \n", op[i]);
  }
  printf("Hello World");
  return 0;
}
