#include <stdio.h>

int main() {
  char string1[20];
  char string2[20];

  strcpy(string1, "Hello");
  strcpy(string2, "Hellooo");

  printf("Returned String : %s\n", strncat( string1, string2, 4 ));
  printf("Concatenated String : %s\n", string1 );

  return 0;
}

/*
It will proiduce following result:

Returned String : HelloHell
Concatenated String : HelloHell
*/
