/***
    https://leetcode.com/problems/accounts-merge/
    Accounts Merge

    Given a list of accounts where each element accounts[i] is a list of strings,
    where the first element accounts[i][0] is a name, and the rest of the
    elements are emails representing emails of the account.

    Now, we would like to merge these accounts. Two accounts definitely belong to
    the same person if there is some common email to both accounts. Note that even if
    two accounts have the same name, they may belong to different people as people could
    have the same name. A person can have any number of accounts initially, but all of
    their accounts definitely have the same name.

    After merging the accounts, return the accounts in the following format: the first
    element of each account is the name, and the rest of the elements are emails in
    sorted order. The accounts themselves can be returned in any order.

    Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John",
    "johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
    Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
    Explanation:
    The first and second John's are the same person as they have the common email "johnsmith@mail.com".
    The third John and Mary are different people as none of their email addresses are used by other accounts.
    We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'],
    ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
    Example 2:

    Input: accounts = [["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],
    ["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
    Output: [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],
    ["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]

    Constraints:

    1 <= accounts.length <= 1000
    2 <= accounts[i].length <= 10
    1 <= accounts[i][j] <= 30
    accounts[i][0] consists of English letters.
    accounts[i][j] (for j > 0) is a valid email.

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Status: Pending

    Date: 12/5/2021
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
int cmp(const void* a, const void* b) {
  char* a1 = *(char**)a;
  char* b1 = *(char**)b;
  return strcmp(a1, b1);
}

int find(int* parent, int i) {
  return parent[i] == i
    ? i
    : (parent[i] = find(parent, parent[i]));
}

void _union(int* parent, int* rank, int i, int j) {
  i = find(parent, i);
  j = find(parent, j);
  if (i == j) {
    return;
  }

  if (rank[i] > rank[j]) {
    parent[j] = i;
  } else {
    parent[i] = j;
    if (rank[i] == rank[j]) {
      rank[j] ++;
    }
  }
}

int getIdx(const char* email, const char** emails, int emailsSize) {
  const char** value = bsearch(&email, emails, emailsSize, sizeof(char*), cmp);
  int idx = (int)(value - emails);
  return idx;
}

struct Result {
  char*** r;
  int* cols;
  int size;
  int cap;

  char** cur;
  int cur_size;
  int cur_cap;
};

void add(struct Result* r, char* value) {
  if (r->cur_cap <= r->cur_size) {
    r->cur_cap = (1+r->cur_cap)*2;
    r->cur = realloc(r->cur, r->cur_cap*sizeof(char*));
  }

  r->cur[r->cur_size++] = value;
}

void flush(struct Result* r) {
  if (r->cap <= r->size) {
    r->cap = (1+r->cap)*2;
    r->r = realloc(r->r, r->cap*sizeof(char**));
    r->cols = realloc(r->cols, r->cap*sizeof(int));
  }

  r->cols[r->size] = r->cur_size;
  r->r[r->size++] = r->cur;
  r->cur = NULL;
  r->cur_cap = r->cur_size = 0;
}

struct Pair {
  int index;
  int group;
};

int cmp2(const void* a, const void* b) {
  const struct Pair* p1 = a;
  const struct Pair* p2 = b;
  if (p1->group == p2->group) {
    return p1->index - p2->index;
  }
  return p1->group - p2->group;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char *** accountsMerge(char *** accounts, int accountsSize, int* accountsColSize, int* returnSize, int** returnColumnSizes){
  int emailsSize;
  int unionFindSize;
  int i, j, k;
  char** emails;
  int* parent;
  int* rank;
  struct Pair* pairs;
  struct Result r;
  memset(&r, 0, sizeof(r));

  for (emailsSize = 0, i = 0; i < accountsSize; i++) {
    for (j = 1; j < accountsColSize[i]; j++) {
      emailsSize ++;
    }
  }
  emails = malloc(emailsSize * sizeof(char*));
  for (k = 0, i = 0; i < accountsSize; i++) {
    for (j = 1; j < accountsColSize[i]; j++) {
      emails[k++] = accounts[i][j];
    }
  }
  qsort(emails, emailsSize, sizeof(char*), cmp);
  // dedup
  for (i = 0, j = 0; i < emailsSize; ++i) {
    if (j == 0 || strcmp(emails[j-1], emails[i]) != 0) {
      emails[j++] = emails[i];
    }
  }
  emailsSize = j;

  unionFindSize = accountsSize+emailsSize;
  parent = malloc(unionFindSize*sizeof(int));
  rank = malloc(unionFindSize*sizeof(int));

  pairs = malloc(unionFindSize*sizeof(struct Pair));

  for (i = 0; i < unionFindSize; i++) {
    parent[i] = i;
    rank[i] = 0;
  }
  for (i = 0; i < accountsSize; i++) {
    for (j = 1; j < accountsColSize[i]; j++) {
      int idx = accountsSize+getIdx(accounts[i][j], emails, emailsSize);
      _union(parent, rank, i, idx);
    }
  }
  for (i = 0; i < unionFindSize; i++) {
    struct Pair p = {i, find(parent, i)};
    pairs[i] = p;
  }
  qsort(pairs, unionFindSize, sizeof(struct Pair), cmp2);
  add(&r, accounts[pairs[0].index][0]);
  for (i = 1; i < unionFindSize; i++) {
    if (pairs[i].group != pairs[i-1].group) {
      flush(&r);
      add(&r, accounts[pairs[i].index][0]);
    } else {
      int idx = pairs[i].index - accountsSize;
      if (idx >= 0) {
	add(&r, emails[idx]);
      }
    }
  }
  flush(&r);
  *returnSize = r.size;
  *returnColumnSizes = r.cols;

  free(pairs);
  free(parent);
  free(rank);
  free(emails);

  return r.r;
}

int main (int argc, char **argv) {
  int ret = 0;

  debug("Output = %d", ret);
  return 0;
}

/**

 **/
