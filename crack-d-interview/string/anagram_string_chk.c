/*
  Given two strings A and B, how would you find out if the characters
  in B were a subset of the characters in A?
*/
#include <stdio.h>
#include <string.h>

int verify_String (char *str1, char *str2);
int isSubset(char *a, char *b);

int main () {
  int ret;
  char str1[] = "ABCD";
  char str2[] = "DCAB";
  if( verify_String (str1, str2))
    printf("The two strings are anagram of each other \n");
  else
    printf("The two strings are not anagram of each other \n");
  
  if (isSubset(str1, str2)) 
    printf("The two strings are anagram of each other \n");
  else
    printf("The two strings are not anagram of each other \n");

}

int verify_String (char *s1, char *s2) {
  int i,l1,l2;
  int flag = 0;
  int ret = 0;
  int isPresent1[256] = {0};
  int isPresent2[256] = {0};
  l1 = strlen (s1);
  l2 = strlen (s2);
  if (l1 != l2)
    return ret;
  for (i=0; i<256; i++) {
    isPresent1[i] = 0;
    isPresent1[i] = 0;
  }

  for (i=0; s1[i] && s2[i]; i++) {
    isPresent1[s1[i]]++;
    isPresent2[s2[i]]++;
  }

  for (i=0; i<256; i++) 
    if (isPresent1[i] != isPresent2[i]) 
      return 0;
  
  return 1;
}

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
