/*
* Implement the at_strstr() function in C.
* Date : 3-07-2013
* Author : Atul Ramesh Raut
***/
#include <stdio.h>
#include <stdlib.h>

char* at_strstr(const char *str, const char *substr);

int main () {

  char *ptr;
  char *gtr;
  ptr = strstr("This is Great", "Great");
  printf ("ptr = %s\n", ptr);
  gtr = at_strstr("This is Great", "Grea");
  printf ("gtr = %s\n", gtr);
  return 0;
}

/*
* Discription : Implement the at_strstr() function in C. 
***/
char * at_strstr (const char *str, const char *substr) {
  char *tempstr;
  char *tempsubstr = (char*)substr;
  
  for (; str != '\0'; str=str+1) {
    if (*str != *tempsubstr)
      continue;
    tempstr = str;
    while (1) {
      if (*tempsubstr == '\0')
        return str;
      if (*tempstr != *tempsubstr)
        break;
      tempstr++;
      tempsubstr++;
    }  
    tempsubstr = substr;
  } //end for
}
