/***
    Given two strings A and B, how would you find out if the characters
    in B were a subset of the characters in A?

    Core Logic :
    isPresent initialize all Elements to Zero.
    isPresent started updating index as per string
    index e.g. A==65, hence isPresent's 65 Index
    increases to 1 post line 19 below.
*/
#include <stdio.h>
#include <string.h>
#include "../../at_lib.h"

int isSubset(char *a, char *b) {
  int i = 0;
  int isPresent[256] = {0};
  for (i=0; a[i] != '\0'; i++) {
    debug("i=%d, a[%d], isPresent[%d]", i, a[i], isPresent[a[i]]);
    isPresent[a[i]]++;
    debug("i=%d, a[%d], isPresent[%d]", i, a[i], isPresent[a[i]]);
  }

  for (i=0; b[i] != '\0'; i++) {
    debug("i=%d, b[%d], isPresent[%d]", i, b[i], isPresent[b[i]]);
    if(!isPresent[b[i]]++)
      return 0;
  }
  return 1;
}

int main () {
  int ret;
  char str1[] = "AABCD";
  char str2[] = "DCAB";

  if (isSubset(str1, str2))
    printf("The two strings are anagram of each other \n");
  else
    printf("The two strings are not anagram of each other \n");

}

/***
    => ./a.out
    [isSubset] L=13 :i=0, a[65], isPresent[0]
    [isSubset] L=15 :i=0, a[65], isPresent[1]
    [isSubset] L=13 :i=1, a[65], isPresent[1]
    [isSubset] L=15 :i=1, a[65], isPresent[2]
    [isSubset] L=13 :i=2, a[66], isPresent[0]
    [isSubset] L=15 :i=2, a[66], isPresent[1]
    [isSubset] L=13 :i=3, a[67], isPresent[0]
    [isSubset] L=15 :i=3, a[67], isPresent[1]
    [isSubset] L=13 :i=4, a[68], isPresent[0]
    [isSubset] L=15 :i=4, a[68], isPresent[1]

    [isSubset] L=19 :i=0, b[68], isPresent[1]
    [isSubset] L=19 :i=1, b[67], isPresent[1]
    [isSubset] L=19 :i=2, b[65], isPresent[2]
    [isSubset] L=19 :i=3, b[66], isPresent[1]
    The two strings are anagram of each other
*/
