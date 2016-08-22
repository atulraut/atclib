/*
Author - Atul Raut
Date - 24-7-2016
Place - San Diego, CA, USA  
Aim - Given a string, find its first non-repeating character
*/
#include<stdlib.h>
#include<stdio.h>
#define NO_OF_CHARS 256

int firstNonRepeatingString (char *);

int main() {
  char astr[] = "atulrameshraut";
  int index =  firstNonRepeatingString(astr);
  if (index == -1)
    printf("Either all characters are repeating or string is empty \n");
  else
    printf("First non-repeating character is %c \n", astr[index]);
  return 0;
}

int firstNonRepeatingString (char *mstr) {
  int i;
  int index = -1;
  int cntArr[NO_OF_CHARS] = {0};
  for (i=0; i<NO_OF_CHARS; i++) {
    cntArr[i] = 0;
  }
  for (i=0; i<mstr[i]; i++) {
    cntArr[mstr[i]]++;
    printf ("BANK -[%d]->[%c]->cntArr[%d] \n",i, mstr[i], cntArr[mstr[i]]);
  }
  for (i=0; i<mstr[i]; i++) {
    printf ("JTUL -[%d]->[%c]->cntArr[%d] \n",i, mstr[i], cntArr[mstr[i]]);
    if (cntArr[mstr[i]] == 1) {
	index = i;
	break;
    }
  }
  return index;
}
