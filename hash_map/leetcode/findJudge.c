/***
    https://leetcode.com/problems/find-the-town-judge/
    997. Find the Town Judge

    In a town, there are n people labeled from 1 to n. There is a
    rumor that one of these people is secretly the town judge.

    If the town judge exists, then:

    The town judge trusts nobody.
    Everybody (except for the town judge) trusts the town judge.
    There is exactly one person that satisfies properties 1 and 2.
    You are given an array trust where trust[i] = [ai, bi]
    representing that the person labeled ai trusts the person labeled bi.

    Return the label of the town judge if the town judge exists
    and can be identified, or return -1 otherwise.

    Input: n = 2, trust = [[1,2]]
    Output: 2

    Input: n = 3, trust = [[1,3],[2,3]]
    Output: 3

    Input: n = 3, trust = [[1,3],[2,3],[3,1]]
    Output: -1

    Constraints:
    1 <= n <= 1000
    0 <= trust.length <= 104
    trust[i].length == 2
    All the pairs of trust are unique.
    ai != bi
    1 <= ai, bi <= n

    gcc -g -o main -Wall -Wextra -pedantic -Wwrite-strings -fsanitize=address *.c -lm

    Date: 2 Jan 2022
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
#define max(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a > _b ? _a : _b; })
#define min(a,b)				\
  ({ __typeof__ (a) _a = (a);			\
    __typeof__ (b) _b = (b);			\
    _a < _b ? _a : _b; })
/*----------------------------------- Micro --------------------------------------*/

int findJudge(int n, int** trust, int trustSize, int* trustColSize) {
  int hash[1005]={0};
  int townJudge=-1;

  for( int i=0;i<trustSize;i++) {

    hash[trust[i][1]]++;
    hash[trust[i][0]]--;

  }
  for(int i=1;i<=n;i++) {
    if(hash[i]==n-1) {
      townJudge=i;
      break;
    }

  }
  return townJudge;

}

int findJudge__(int n, int** trust, int trustSize, int* trustColSize){
  int candidate = -1;

  // define a boolean array to find non-existent trust[i][0] and use it as a candidate for judge
  bool arr[n+1];

  for(int i=0; i<=n; i++)
    arr[i] = false;

  for(int i=0; i<trustSize; i++)
    arr[trust[i][0]] = true;

  for(int i=1; i<=n; i++) {
    if(!arr[i]) {
      candidate = i;
      break;
    }
  }

  if(candidate==-1)
    return -1;

  // reuse the array to check if there not exists trust[i][1] equal to candidate
  for(int i=1; i<=n; i++)
    arr[i] = false;

  for(int i=0; i<trustSize; i++)
    if(trust[i][1]==candidate) arr[trust[i][0]] = true;

  bool res = true;
  for(int i=1; i<=n; i++) {
    if(i==candidate)
      continue;
    res &= arr[i];
  }
  return res ? candidate : -1;
}

int** create_matrix(int rows, int cols) {
  int** max = (int**)malloc(sizeof(int) * rows);
  for (int i=0; i<rows; ++i) {
    max[i] = (int*)malloc(sizeof(int *) * cols);
  }
  return max;
}

int main (int argc, char **argv) {
  int ret = 0;
  //n = 3, trust = [[1,3],[2,3]]

  int n = 3;
  int trustSize = 2;
  int trustColSize = 2;

  int** trust = create_matrix(trustSize, trustColSize);
  *(*(trust + 0) + 0) = 1;
  *(*(trust + 0) + 1) = 3;

  *(*(trust + 1) + 0) = 2;
  *(*(trust + 1) + 1) = 3;

  ret = findJudge(n, trust, trustSize, &trustColSize);
  debug("Output = %d", ret);
  return 0;
}

/**
   => ./a.out
   [main] L=118 :Output = 3
**/
