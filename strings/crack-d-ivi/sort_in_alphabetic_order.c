/***
    Ref : http://venkateshabbarapu.blogspot.com/
    Date : 3/3/2021
    San Diego, CA
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

void sort_string(char *s) {
  int c, d = 0, length;
  char *pointer, *result, ch;

  length = strlen(s);

  result = (char*)malloc(length+1);
  pointer = s;

  for ( ch = 'a' ; ch <= 'z' ; ch++ ) {
    for ( c = 0 ; c < length ; c++ ) {
      if ( *pointer == ch ) {
	*(result+d) = *pointer;
	d++;
      }
      pointer++;
    }
    pointer = s;
  }

  *(result+d) = '\0';

  strcpy(s, result);
  free(result);
}

int main() {
  char string[100];

  printf("Enter some text\n");

  fgets (string, sizeof(string), stdin);

  debug("Input String--> %s ", string);
  sort_string(string);
  debug("Sorted String--> %s ", string);

  return 0;
}

/**
   => ./a.out
   Enter some text
   atul
   [main] L=40 :Input String--> atul

   [main] L=42 :Sorted String--> altu
**/
