/*
* Aim    : Write a func for Acromatic string.
*        : I/P : "Goverment of India" O/P : "GoI";
* Author : Atul Ramesh Raut
* Date   : March 30, 2012 08:47PM
*
***/

#include <stdio.h>
#include <stdlib.h>

void strAcromatic (char *);
void org_strAcromatic (char *);

int main () {
  char arr[30] = "Goverment of India";
  strAcromatic (arr);
}

void strAcromatic (char *s) {
  char *t;
  while (*s != '\0') {    
    *t = *s;
    printf ("\n t = %s t = %p\n", t, t);
    while (*s != ' ') { // Moved til end of space      
      s++;
    }  // 2nd while endohookkkfa   
      s++;
      t++;
  } // 1st while   
  *t = '\0';
  printf ("\nO/P = %s\n", t);
}

void org_strAcromatic (char *s) {
  char *t;
  int flag  = 0;
  t = (char*)malloc(sizeof (5));
  while (*s != '\0') {
    *t = *s;          // collect first character in pointer
    printf ("\n t = %s t = %p\n", t, t);
    while (*s != ' ') { // Moved til end of space
      flag = 1;
      s++;
    }  // 2nd while endohookkkfa
    if (flag == 1) {    
      s++;
      t++;
    } else {
      flag = 0;
      *t = '\0';
      printf ("\n new t =%p\n", t);
    }    
  } // 1st while end 
  
  //  t++;
  //*t = '\0';
  printf ("\nO/P = %s\n", t);
}
