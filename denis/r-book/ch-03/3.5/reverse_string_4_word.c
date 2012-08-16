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
char* new_RevStr_Word (char *);

int main () {

  //  char arr[] = "Raut Dattratray Ramesh Atul";
  char arr[] = "Raut Dattatray Ramesh Atul";
  char *ret;
  printf ("\nI/P : %s\n", arr);
  //ret = revStr_Word (arr);
  ret = new_RevStr_Word(arr);
  printf ("\nO/P : %s\n", ret);
}

/* revStr_Word : *(name[i]+j) : To access j'th character in i'th name */
char *new_RevStr_Word (char *str) {

  int i, j, k, wordCounter;
  i = 0;
  wordCounter = 0;

  char *arr[wordCounter];
  char tmp[0];
  char *newStr;

  while (str[i] != '\0') {
    //    printf ("str[%d]=%c", i, str[i]);
    if (str[i] == ' ' || str[i] == '\0') {
      wordCounter++;
     }
    i++;
    if(str[i] == '\0')
      wordCounter++;
  } // While Ends
  wordCounter++;

  //Initialize the arrays
  for (i = 0; i < wordCounter; i++) { 
    arr[i] = (char*)malloc(sizeof(char));
  }
  i = 0;
  k = 0;
  j = 0;
  while (str[i] != '\0') {
    printf ("\nstr[%d]=%c", i, str[i]);
    if (str[i] == ' ' || str[i] == '\0') {
      newStr[j] = '\0';
      arr[k] = newStr;
      newStr = NULL;
      j = 0;
      k++;
    } else { // Collect individual word in array
      printf ("\nstr[%d]=%c, j=%d .... ", i, str[i], j);
      newStr[j] = str[i];
      printf ("\nnewStr[%d]=%c ..\n", j, newStr[i]);
    }
    i++;
    j++;
    if (str[i] == '\0') {
      newStr[j] = '\0';
      arr[k] = newStr;
      j = 0;
    }
  } 
  printf ("\naTUL \n");  
  printf ("\n wordCounter =%d =%s \n", wordCounter, *arr[1]);
  return str;
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

