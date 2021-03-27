/***
    916. Word Subsets
    https://leetcode.com/problems/word-subsets/
    We are given two arrays A and B of words.  Each word is
    a string of lowercase letters.

    Now, say that word b is a subset of word a if every letter
    in b occurs in a, including multiplicity.  For example, "wrr"
    is a subset of "warrior", but is not a subset of "world".

    Now say a word a from A is universal if for every b in B,
    b is a subset of a.

    Return a list of all universal words in A.  You can return
    the words in any order.

    Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","o"]
    Output: ["facebook","google","leetcode"]

    Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["l","e"]
    Output: ["apple","google","leetcode"]

    Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","oo"]
    Output: ["facebook","google"]

    Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["lo","eo"]
    Output: ["google","leetcode"]

    Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["ec","oc","ceo"]
    Output: ["facebook","leetcode"]

    Note:
    1 <= A.length, B.length <= 10000
    1 <= A[i].length, B[i].length <= 10
    A[i] and B[i] consist only of lowercase letters.
    All words in A[i] are unique: there isn't i != j with A[i] == A[j].

    Date: 26 March 2021.
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

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** wordSubsets(char ** A, int ASize, char ** B, int BSize, int* returnSize) {
  int* map=(int*)calloc(26,sizeof(int));
  int* map1=(int*)calloc(26,sizeof(int));
  char** ret=(char**)malloc((ASize+BSize)*sizeof(char*));
  *returnSize=0;
  int count=0;

  for(int i=0; i<BSize; i++) {
    for(int j=0; B[i][j]!='\0'; j++) {
      map1[B[i][j]-'a']++;
    }
    for(int k=0;k<26;k++) {
      map[k]=map[k]>map1[k]?map[k]:map1[k];
      map1[k]=0;
    }
  }

  for(int k=0; k<26; k++) {
    if(map[k] != 0) {
      count++;
    }
  }

  for(int i=0; i<ASize; i++) {
    int tempCount=0;
    for(int k=0; k<26; k++) {
      map1[k]=map[k];
    }

    for(int j=0; A[i][j] != '\0'; j++) {
      if(map1[A[i][j]-'a'] != 0) {
	map1[A[i][j]-'a']--;

	if(map1[A[i][j]-'a'] == 0) {
	  tempCount++;
	}
      }

      if(tempCount == count) {
	ret[(*returnSize)++]=A[i];
	break;
      }
    }
  }
  return ret;
}

int main () {
  int returnSize;
  char *A[] = {"amazon","apple","facebook","google","leetcode"};
  char *B[] = {"e","o"};

  int ASize = sizeof(A)/sizeof(sizeof(A[0]));
  int BSize = sizeof(B)/sizeof(sizeof(B[0]));

  debug ("ASz = %d BSz = %d", ASize, BSize);

  char **arr =  wordSubsets(A, ASize, B, BSize, &returnSize);

  for (int i=0; i<returnSize; i++)
    debug ("ret = %s", arr[i]);

  return 0;
}

/**
   => ./a.out
   [main] L=112 :ASz = 5 BSz = 2
   [main] L=117 :ret = facebook
   [main] L=117 :ret = google
   [main] L=117 :ret = leetcode
**/
