#include <stdio.h>

/*
* Name as an Array of 3 Pointers
char *Name[3] = {
    "Australia",
    "Afganistan",
    "India"
}
(*Name)[3] : Declares Name as a pointer to an array of 3 elements.
*
***/

char* revStr_Word (char *);

int main () {

  //  char arr[] = "Raut Dattratray Ramesh Atul";
  char arr[] = "Raut Atul";
  char *ret;
  printf ("\nI/P : %s\n", arr);
  ret = revStr_Word (arr);
  printf ("\nO/P : %s\n", ret);
}

/* revStr_Word : *(name[i]+j) : To access j'th character in i'th name */
char *revStr_Word (char *str) {
  char *newStr [2];
  char arr [10];
  char arr2[10];
  int i, j, k, a;
  i = 0; j = 0; k = 0;

  while (str[i] != '\0') {
    if (k == 0)
	arr[j] = str[i];
    if (k == 1)
	arr2[j] = str[i];
    i++; j++;
    if (str[i] == ' ' || str[i] == '\0') {
      if (k == 0) {
	arr[j] = '\0';
	newStr[k] = &arr;
      }
      printf ("\n k =%d \n", k);
      if (k == 1) {
	arr2[j] = '\0';
	newStr[k] = &arr2;
      }
      j = 0;
      k++;
      printf ("\n k =%d \n", k);
    } // if end's
  } // While Ends
  printf ("\n My_Version = %s", newStr[0]);
  printf ("\n My_Version = %s\n\n", newStr[1]);

  for (a=1; a>=0; a--) {
    printf (" %s ", newStr[a]);
  }

  return newStr;
}


