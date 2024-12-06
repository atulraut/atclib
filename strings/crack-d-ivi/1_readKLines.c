/***
    Crack Coding Interview - Page 422 Hard Copy
    Write a method to print the last K lines of an input file using C++.
    Date : Fri 06 Dec 2024 03:04:53 PM PST
    Folsom CA
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

void printLastKLines(const char* filename) {
  const int K = 10;
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  char L[K][256]; // Assuming a maximum line length of 255 characters
  int lines = 0;
  int size = 0;

  while (fgets(L[size % K], sizeof(L[size % K]), file) != NULL) {
    debug("sz=%d K=%d -> [%d]",size, K, (size % K) );
    size++;
  }

  fclose(file);

  // if less than K lines were read, print them all
  int start, count;
  start = size > K ? (size % K) : 0;
  count = (size < K) ? size : K;

  for (int i = 0; i < count; ++i) {
    printf("%s", L[(start + i) % K]);
  }
}


int main () {

  printLastKLines("1_readKLines.txt");
  return 0;
}

/**
   [printLastKLines] L=33 :sz=0 K=10 -> [0]
   [printLastKLines] L=33 :sz=1 K=10 -> [1]
   [printLastKLines] L=33 :sz=2 K=10 -> [2]
   [printLastKLines] L=33 :sz=3 K=10 -> [3]
   [printLastKLines] L=33 :sz=4 K=10 -> [4]
   [printLastKLines] L=33 :sz=5 K=10 -> [5]
   [printLastKLines] L=33 :sz=6 K=10 -> [6]
   [printLastKLines] L=33 :sz=7 K=10 -> [7]
   [printLastKLines] L=33 :sz=8 K=10 -> [8]
   [printLastKLines] L=33 :sz=9 K=10 -> [9]
   [printLastKLines] L=33 :sz=10 K=10 -> [0]
   [printLastKLines] L=33 :sz=11 K=10 -> [1]
   [printLastKLines] L=33 :sz=12 K=10 -> [2]
   [printLastKLines] L=33 :sz=13 K=10 -> [3]
   [printLastKLines] L=33 :sz=14 K=10 -> [4]
   [printLastKLines] L=33 :sz=15 K=10 -> [5]
   [printLastKLines] L=33 :sz=16 K=10 -> [6]
   [printLastKLines] L=33 :sz=17 K=10 -> [7]
   [printLastKLines] L=33 :sz=18 K=10 -> [8]
   [printLastKLines] L=33 :sz=19 K=10 -> [9]
   [printLastKLines] L=33 :sz=20 K=10 -> [0]
   Round 11 : Binary Tree Right Side View
   Round 12 : Minimum Path Sum
   Round 13 : Add Two Numbers
   Round 14 : Generate Parentheses
   Round 15 : Flatten Binary Tree to Linked List
   Round 16 : String to Integer (atoi)
   Round 17 : Reverse Words in a String
   Round 18 : Daily Temperatures
   Round 19 : Interleaving String
   Round 20 : Merge k Sorted Lists
**/
