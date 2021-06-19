/*
 * Prob : There are 5 stairs. you can take either 1 or 2 steps
 * How many combinations you can take to climb the stairs?
 * Ans is 8
 * Step 1: if don't use 2 steps .then only 1 way
 * Step 2: if we use single 2 steps ..then 4 ways
 * Step 3: if we use double 2 steps .then 3 ways
 * so total combintaion is 8
*/
#include <stdio.h>
#include <stdlib.h>
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

unsigned long long memoize(int N) {
  unsigned long long ret = 0;
  unsigned long long* cache = (unsigned long long *)malloc(sizeof(unsigned long long) * (N + 1));

  cache[1] = 1;
  debug("cache[0]=%llu", cache[0]);
  for (int i = 2; i <= N; i++) {
    cache[i] = cache[i-1] + cache[i-2];
  }

  ret = cache[N];
  free(cache);
  return ret;
}

/* IVI : */
unsigned long long fib(int N) {
  if (N <= 1) {
    return N;
  }
  return memoize(N);
}

static int cnt;
int fab1 (int n) {
    int Res;
    ++cnt;
    if (n==1 || n==2)
        return 1;
    Res = fab1(n-1) + fab1(n-2);
    return Res;
}

int main() {
  int i=0, Res=0, lastRes=0;
  for (i=1; i<=5; i++) {
    lastRes = Res;
    Res =  fab1(i);
    printf(" Res = %d \n", Res);
  }
  printf ("o/p = %d \n", lastRes+Res);

  debug("Testing 50, cnt = %d", cnt);
  unsigned long long n = fib(50);
  printf ("n = %llu \n", n);
  return 0;
}

/*
  => ./a.out
  Res = 1
  Res = 1
  Res = 2
  Res = 3
  Res = 5
  o/p = 8
  [main] L=65 :Testing 50!
  n = 12586269025
*/
