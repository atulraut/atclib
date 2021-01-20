/*
  A Program to check if strings are rotations of each other or not
  Given a string s1 and a string s2, write a snippet to say whether 
  s2 is a rotation of s1 using only one call to strstr routine?
  (eg given s1 = ABCD and s2 = CDAB, return true, given s1 = ABCD, 
  and s2 = ACBD , return false)
*/

// C program to check if two given strings are rotations of 
// each other
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
 
/* Function checks if passed strings (str1 and str2)
   are rotations of each other */
int areRotations(char *str1, char *str2)
{
  int sz1   = strlen(str1);
  int sz2   = strlen(str2);
  char *temp;
  void *ptr;
 
  /* Check if sizes of two strings are same */
  if (sz1 != sz2)
    return 0;
 
  /* Create a temp string with value str1.str1 */
  temp   = (char *)malloc(sizeof(char)*(sz1*2 + 1));
  temp[0] = '\0';
  strcat(temp, str1);
  strcat(temp, str1);
  printf ("[s1s1] -> %s\n",temp); 
  /* Now check if str2 is a substring of temp */
  ptr = strstr(temp, str2);
 
  free(temp); // Free dynamically allocated memory
 
  /* strstr returns NULL if the second string is NOT a
     substring of first string */
  if (ptr != NULL)
    return 1;
  else
    return 0;
}
 
/* Driver program to test areRotations */
int main() {
  char *str1 = "AACD"; 
  char *str2 = "ACDA";
 
  if (areRotations(str1, str2))
    printf("Strings are rotations of each other\n");
  else
    printf("Strings are not rotations of each other \n");
 
  getchar();
  return 0;
}

