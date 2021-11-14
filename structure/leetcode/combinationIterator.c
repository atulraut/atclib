/***
    https://leetcode.com/problems/iterator-for-combination/
    Iterator for Combination

    Design the CombinationIterator class:
    CombinationIterator(string characters, int combinationLength)
    Initializes the object with a string characters of sorted
    distinct lowercase English letters and a number combinationLength
    as arguments.
    next() Returns the next combination of length combinationLength
    in lexicographical order.
    hasNext() Returns true if and only if there exists a next combination.

    Input
    ["CombinationIterator", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
    [["abc", 2], [], [], [], [], [], []]
    Output
    [null, "ab", true, "ac", true, "bc", false]

    Explanation
    CombinationIterator itr = new CombinationIterator("abc", 2);
    itr.next();    // return "ab"
    itr.hasNext(); // return True
    itr.next();    // return "ac"
    itr.hasNext(); // return True
    itr.next();    // return "bc"
    itr.hasNext(); // return False

    Constraints:
    1 <= combinationLength <= characters.length <= 15
    All the characters of characters are unique.
    At most 104 calls will be made to next and hasNext.
    It's guaranteed that all calls of the function next are valid.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 14 Nov 2021
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
#define max(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a > _b ? _a : _b; })
#define min(a,b)		\
  ({ __typeof__ (a) _a = (a);	\
    __typeof__ (b) _b = (b);	\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

typedef struct {
  int indices[20];
  char ch[20];
  char comb[20];
  int l;
  int k;
  int finish;
} CombinationIterator;


CombinationIterator* combinationIteratorCreate(char* characters, int combinationLength) {
  int i;
  CombinationIterator* obj = calloc(1, sizeof(*obj));
  obj->l = strlen(characters);
  obj->k = combinationLength;
  for (i = 0; i < obj->k; i++) {
    obj->indices[i] = i;
  }
  strcpy(obj->ch, characters);
  return obj;
}

char* combinationIteratorNext(CombinationIterator* obj) {
  int i;
  for (i = 0; i < obj->k; i++)
    obj->comb[i] = obj->ch[obj->indices[i]];

  obj->comb[i] = 0;

  for (i = obj->k-1; i >= 0; i--)
    if (obj->indices[i] < obj->l - (obj->k-1-i) - 1)
      break;

  obj->finish = i==-1;

  if (!obj->finish) {
    obj->indices[i]++;

    for (i = i+1; i < obj->k; i++)
      obj->indices[i] = obj->indices[i-1]+1;
  }
  return obj->comb;
}

bool combinationIteratorHasNext(CombinationIterator* obj) {
  return !obj->finish;
}

void combinationIteratorFree(CombinationIterator* obj) {
  free(obj);
}

/**
 * Your CombinationIterator struct will be instantiated and called as such:
 * CombinationIterator* obj = combinationIteratorCreate(characters, combinationLength);
 * char * param_1 = combinationIteratorNext(obj);

 * bool param_2 = combinationIteratorHasNext(obj);

 * combinationIteratorFree(obj);
*/

int main (int argc, char **argv) {
  char* ans;
  bool ret;
  char arr[] = "abc";
  int combinationLength = 2;

  CombinationIterator* itr = combinationIteratorCreate(arr, combinationLength);
  ans = combinationIteratorNext(itr);    // return "ab"
  debug ("ans = %s", ans);
  ret = combinationIteratorHasNext(itr); // return True
  debug ("ret = %d", ret);
  ans = combinationIteratorNext(itr);    // return "ac"
  debug ("ans = %s", ans);
  ret = combinationIteratorHasNext(itr); // return True
  debug ("ret = %d", ret);
  ans = combinationIteratorNext(itr);    // return "bc"
  debug ("ans = %s", ans);
  ret = combinationIteratorHasNext(itr); // return False
  debug ("ret = %d", ret);
  combinationIteratorFree(itr);

  return 0;
}

/**
   => ./a.out
   [main] L=137 :ans = ab
   [main] L=139 :ret = 1
   [main] L=141 :ans = ac
   [main] L=143 :ret = 1
   [main] L=145 :ans = bc
   [main] L=147 :ret = 0
**/
