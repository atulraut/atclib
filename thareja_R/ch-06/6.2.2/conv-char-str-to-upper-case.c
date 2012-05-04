/*
* Aim    : WAP converting character of a String into Upper Case.
* Date   : 30-04-2012
* Author : Atul Ramesh Raut
* ASCII Code for String : 
* a] A-Z ===> 65-91
* b] a-z ===> 97-123
***
*/

#include <stdio.h>
#include <stdlib.h>

void my_UpperStr (char []);

int main () {
  
  char str[5] = "atul";
  my_UpperStr (str);
  return 0;
}

void my_UpperStr (char str[]) {
  int i = 0;
  int j = 0;
  char uStr[5];
  while (str[i] != '\0') {
    if (str [i] >= 'a' && str[i] <= 'z') {
      uStr [i] = str[i] - 32;  // Converting to Upper Case
      printf ("\n ATUL = %c\n", uStr[i]);
    }
    else {
      uStr [i] = str [i];      
    }
    i++; j++;
  }
  uStr [i] = '\0';
  printf ("\n Output str = %s \n", uStr);
}
