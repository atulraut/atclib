/*
* Author : Atul R. Raut
* Date   : 26 Sept 2015
* Place  : San Diego
* Do Check : http://www.geeksforgeeks.org/remove-characters-from-the-first-string-which-are-present-in-the-second-string/
* Question: Delete characters from string 1 which are present in string 2.
*/
#include <stdio.h>
#include <stdlib.h>

char* remove_duplicate_string (char *iStr, char *iMask);

int main() {
  //char *iStr = "geeksforgeeks";
  char *iStr = "test string";
  char *iMask= "mask";
  char *ret  = remove_duplicate_string (iStr, iMask);
  printf ("\narr = %s\n", ret);
  return 0;
}

char* remove_duplicate_string (char *iStr, char *iMask) {
  int i = 0, m = 0, j = 0;
  int flag = 0;
  char *arr = (char *) malloc (strlen(iStr)+1);

  while (iStr[i] != '\0') {
    while (iMask[m] != '\0') {
      if (iStr[i] == iMask[m]) {
          flag = 0;
          break;
      } else
      flag = 1;
      m++;
    }
    if (flag) {
      arr[j] =  iStr[i];
      j++;
    }
    i++;
    flag = 0; // reset flag
    m = 0; // reset iMask
  } // main while end
  //printf ("len = %d m = %d, o=%d\n", i, m, o);
  arr[j] = '\0';
  //printf ("arr = %s\n", arr);
  return arr;
}

