/*
  Write a simple piece of code to split a string at equal intervals.
*/
#include <stdio.h>
#include <string.h>

#define maxLineSize 20


void split(char *string) {
  int i, length;
  char dest[maxLineSize + 1];
  i =0;
  length = strlen(string);
  while((i+maxLineSize) <= length) {
    strncpy(dest, (string+i), maxLineSize);
    dest[maxLineSize - 1] = '\0';
    i = i + strlen(dest) - 1;
    printf("\nChunk : [%s]\n", dest);
  }
  strcpy(dest, (string + i));
  printf("\nChunk : [%s]\n", dest);
}

void s2_it (char *str) {
  int len, i = 0;
  char dest[maxLineSize];
  while (i+maxLineSize <= len) {
    strncpy(dest, (str+i), maxLineSize);
    dest[maxLineSize-1] = '\0';
    i = i + maxLineSize-1;
    printf ("\n chuck : [%s]\n", dest);
  }
  strcpy(dest, (str+i));
  printf ("\n chuck : [%s]\n", dest);
}

int main () {
  char *str = "This is Atul Ramesh Raut, 40, Vishwas Nagar, Arni Road, Yavatmal, MH-445001, INDIA";
  split(str);
  s2_it (str);
  printf ("\nDONE !\n");
}

/*
Chunk : [This is Atul Ramesh]

Chunk : [h Raut, 40, Vishwas]

Chunk : [s Nagar, Arni Road,]

Chunk : [, Yavatmal, MH-4450]

Chunk : [001, INDIA]

 chuck : [This is Atul Ramesh]

 chuck : [ Raut, 40, Vishwas ]

 chuck : [Nagar, Arni Road, Y]

 chuck : [avatmal, MH-445001,]

 chuck : [ INDIA]

DONE !
*/
