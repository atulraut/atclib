/*
Author - Atul Raut
Date - 24-7-2016
Place - San Diego, CA, USA
Aim - Given a string, find its first non-repeating character
*/
#include<stdlib.h>
#include<stdio.h>

#define debug(str,args...) printf("[%s] [%s()] L=%d :"str"\n",__FILE__, __func__, __LINE__, ##args)

#define NO_OF_CHARS 256

int firstNonRepeatingString (char *mstr) {
  int i;
  int index = -1;
  int cntArr[NO_OF_CHARS] = {0};
  for (i=0; i<NO_OF_CHARS; i++) {
    cntArr[i] = 0;
  }
  for (i=0; i<mstr[i]; i++) {
    cntArr[mstr[i]]++;
    debug ("[%d]->[%c]->cntArr[%d]",i, mstr[i], cntArr[mstr[i]]);
  }
  for (i=0; i<mstr[i]; i++) {
    debug ("[%d]->[%c]->cntArr[%d]",i, mstr[i], cntArr[mstr[i]]);
    if (cntArr[mstr[i]] == 1) {
	index = i;
	break;
    }
  }
  return index;
}

int main() {
  char astr[] = "atulrameshraut";
  int index =  firstNonRepeatingString(astr);
  if (index == -1)
    printf("Either all characters are repeating or string is empty \n");
  else
    printf("First non-repeating character is %c \n", astr[index]);
  return 0;
}

/***
    => ./a.out
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[0]->[a]->cntArr[1]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[1]->[t]->cntArr[1]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[2]->[u]->cntArr[1]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[3]->[l]->cntArr[1]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[4]->[r]->cntArr[1]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[5]->[a]->cntArr[2]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[6]->[m]->cntArr[1]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[7]->[e]->cntArr[1]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[8]->[s]->cntArr[1]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[9]->[h]->cntArr[1]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[10]->[r]->cntArr[2]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[11]->[a]->cntArr[3]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[12]->[u]->cntArr[2]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=23 :[13]->[t]->cntArr[2]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=26 :[0]->[a]->cntArr[3]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=26 :[1]->[t]->cntArr[2]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=26 :[2]->[u]->cntArr[2]
    [first_non-repeating_char.c] [firstNonRepeatingString()] L=26 :[3]->[l]->cntArr[1]
    First non-repeating character is l
*/
