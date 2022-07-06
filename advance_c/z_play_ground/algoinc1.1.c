/***
    Quick-find solution to connectivity Problem

    #algoinc

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: Fri Jul  1 09:36:33 AM PDT 2022
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

#define N 10
int id[N];
/**
    Progam 1.3
    Weighted version fo Quick Union
*/
void test2() {
  int ret = 0;
  int i=0, j=0, p=0, q=0, t=0;
  int sz[N] = {0};

  for (i=0; i<N; i++) {
    id[i] = i;
    sz[i] = 1;
  }

  while (scanf("%d %d \n", &p, &q) == 2) {
    for (i=p; i != id[i]; i=id[i])
      ;
    for (j=q; j != id[j]; j=id[j])
      ;
    if (i == j)
      continue;
    if (sz[i] < sz[j]) {
      id[i] = j;
      sz[j] += sz[i];
    } else {
      id[j] = i;
      sz[i] += sz[j];
    }
    debug ("--> %d %d  \n", p, q);
  }
}

/* Program 1.1 */
void test() {
  int ret = 0;
  int i, p, q, t, id[N];

  for (i=0; i<N; ++i) {
    id[i] = i;
  }

  while (scanf("%d %d \n", &p, &q) == 2) {
    if (id[p] == id[q])
        continue;
    for (t= id[p]; i=0, i<N; ++i) {
      if (id[i] == t)
	id[i] = id[q];
      printf ("%d %d \n", p, q);
    }
  }
  debug("Output = %d", ret);
}

void QuickFindU() {
  id[N] = {0, 1, 2, 3, 8, 0, 5, 7 ,3, 8};
}

int connected (int p, int q) {
  return (id[p] == id[q]);
}

void union (int p, int q) {
  int pid = id[p];
  int qid = id[q];

  // Change all Entries with id[p] to id[q] (at most 2N+2 array accesses)
  for (int i=0; i<N; ++i)
    if (id[i] == pid)
      id[i] = qid;
}

int main (int argc, char **argv) {
  test();
  return 0;
}

/**

 **/
