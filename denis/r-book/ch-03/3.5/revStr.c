/*
* Aim : Reverse String.
* Author : Atul Ramesh Raut
* Date   : March 30, 2012 08:47PM
* Date   : Sept  17, 2016 12:00AM
*
***/

#include <stdio.h>
#include <stdlib.h>

void revStr (char *);
void reverseString(char s[]);

int main () {
  printf ("\nHello world .. !! \n");
  char arr[10] = "Atul";
  revStr (arr);
  return EXIT_SUCCESS; 
}

void reverseString(char s[]) {
    int length = strlen(s) ;
    int c, i, j;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
}
    
void revStr (char *s) {
    int j;
    char *end = str;
    j = strlen (str)-1;
    char temp;
    if (str)  { 
        while (*end != '\0')
            end++;
        --end;
        while (str < end) {
            temp = *str;
            *str++ = *end;
            *end-- = temp;
            j--;
        }
        do {
            --end;
            j--;
        } while (j != 0);
    }
    printf ("\n Reverse String = %s\n", end);        
}
