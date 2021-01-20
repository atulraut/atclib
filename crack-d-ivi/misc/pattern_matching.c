/*
Write a C program which does wildcard pattern matching algorithm
*/
#include<stdio.h>
#define TRUE 1
#define FALSE 0

/*
  char *string = "herohero";
  char *pattern = "*hero*";
*/
int wildcard(char *string, char *pattern) {
  while(*string) {
    printf ("string->[%c] pattern=[%c]\n",*string, *pattern);
    switch(*pattern) {
    case '*':
      do {
	printf ("->[%c]\n", *pattern);
	++pattern;
	printf ("->[%c]\n", *pattern);
      } while (*pattern == '*');

      if(!*pattern) {
	printf ("Returng ..\n");
	return(TRUE);
      }
      while(*string) {
	if(wildcard(pattern,string++)==TRUE) {
	  printf ("->[%c] Returning ..\n", *pattern);
	  return(TRUE);
	}
      }
      printf ("End case \n");
      return(FALSE);
    default : if(*string!=*pattern)
	return(FALSE);
      break;
    }
    ++pattern;
    ++string;
  }
  while (*pattern == '*')
    ++pattern;
  return !*pattern;
}

int main() {
  char *string = "hero";
  //  char *string = "baabab";
  char *pattern = "*hero*";
  if(wildcard(string, pattern)==TRUE) {
    printf("\nMatch Found!\n");
  } else {
    printf("\nMatch not found!\n");
  }
  return(0);
}

/***
    TestCase I:
    char *string = "baabab";
    char *pattern = "*hero*";
    => ./a.out
    string->[b] pattern=[*]
    ->[*]
    ->[h]
    string->[h] pattern=[b]
    string->[h] pattern=[a]
    string->[h] pattern=[a]
    string->[h] pattern=[b]
    string->[h] pattern=[a]
    string->[h] pattern=[b]
    End case

    Match not found!
    TestCase II:

*/
