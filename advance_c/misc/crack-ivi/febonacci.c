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
#include <string.h>

int memoize(int N) {
  int* cache = (int *)malloc(sizeof(int) * (N + 1));

  cache[1] = 1;

  for (int i = 2; i <= N; i++) {
    cache[i] = cache[i-1] + cache[i-2];
  }

  return cache[N];
}

/* IVI : */
int fib(int N) {
  if (N <= 1) {
    return N;
  }
  return memoize(N);
}


int fab1 (int n) {
    int Res;
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

  int n = fib(10);
  printf ("n = %d \n", n);
  return 0;
}

/*
Output
 Res = 1  Res = 1  Res = 2  Res = 3  Res = 5
 o/p = 8
 n = 55
*/
