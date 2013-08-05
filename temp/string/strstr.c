/*
* Aim : Write C code to implement the strstr() 
* (search for a substring) function.
* Date : 3-07-2013
* Author ;  Atul Ramesh Raut
***/

#include <stdio.h>
#include <stdlib.h>

char *at_strstr (const char *, const char *);

int main () {
  
  char s1 [] = "My House is small";
  char s2 [] = "My Car is green";

  printf ("Returned String 1: %s\n", at_strstr (s1, "House"));
  printf ("Returned String 2: %s\n", at_strstr (s2, "Car"));
  
  return 0;
}

/*
* Description:
* The at_strstr function locates the first occurrence of the string string1 
* in the string string2 and returns a pointer to the beginning 
* of the first occurrence.
***/
char *at_strstr (const char *string2, const char *string1) {
   while (*string1 != '\0') {
    if (*string2 == *string1) { 
      break;
    }
    string2++;
  }
  return string2;
}
