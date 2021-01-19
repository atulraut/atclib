/***
    Given two strings A and B, how would you find out if the characters
    in B were a subset of the characters in A?
*/
#include <stdio.h>
#include <string.h>

int isSubset(char *a, char *b) {
  int i = 0;
  int isPresent[256] = {0};
  for (i=0; a[i] != '\0'; i++) {
    isPresent[a[i]]++;
  }

  for (i=0; b[i] != '\0'; i++) {
    if(!isPresent[b[i]]++)
      return 0;
  }
  return 1;
}

int main () {
  int ret;
  char str1[] = "ABCD";
  char str2[] = "DCAB";

  if (isSubset(str1, str2))
    printf("The two strings are anagram of each other \n");
  else
    printf("The two strings are not anagram of each other \n");

}

/***
    => ./a.out
    The two strings are anagram of each other
*/
