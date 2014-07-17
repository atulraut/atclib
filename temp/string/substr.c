/*
* Implement the at_strstr() function in C.
* Date : 3-07-2013
* Author : Atul Ramesh Raut
***/
#include <stdio.h>
#include <stdlib.h>

char* at_strstr(const char *str, const char *substr);

/* strstr example */
#include <stdio.h>
#include <string.h>

char* my_strstr (const char *src, const char *loc);

int main ()
{
  //char str[] ="This is a simple string";
  char str[] = "Atul is string";
  char *pch, *kch;
  pch = strstr (str,"string");
  printf ("o/p pch -> %s \n", pch);
  kch = my_strstr(str, "string");
  printf ("o/p kch -> %s \n", kch);

  return 0;
}

char* my_strstr (const char *string, const char *substring){
  char *a = NULL;
  char *b = (char*)substring;
  if (*string == 0)     // if string is null return
         return (char *)string;
  for (; *string != '\0'; string = string+1) {
        if (*string != *b) 
          continue;
        a = ((char *)string);
        while(1) {
          if (*b == '\0') 
            return ((char *)string);
          if (*a != *b)
            break;
          a++;
          b++;
        } // end while
        b = (char *)substring;
  } // end for
  return (char *) 0;
}