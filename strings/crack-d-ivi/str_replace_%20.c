/*
AIM  - Write a method to replace all spaces in a string with '%20'.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_str_with_20 (char str[], int len) {
  int spacecnt = 0, newlen, i = 0;
  for (i = 0; i < len; i++) {
    if (str[i] == ' ')
      spacecnt++;
  }

	/* spacecnt*3 is giving us required ammount of space for replacement,
	hence len-spacecnt is here.
	*/
  newlen = (len-spacecnt) + spacecnt * 3;
  
  str[newlen] = '\0';
  for(i = len-1; i >=0; i--) {
    if (str[i] == ' ') {
      str[newlen -1] = '0';
      str[newlen -2] = '2';
      str[newlen -3] = '%';
      newlen = newlen - 3;
    } else {
      str[newlen - 1] = str[i];
      newlen = newlen - 1;
    }
  }
}

int main () {
  char arr[] = "Atul Ramesh Raut";
  int len = strlen (arr);
  printf ("\ninput = %s\n", arr);
  replace_str_with_20 (arr, len);
  printf ("\noutput = %s\n", arr);
}
