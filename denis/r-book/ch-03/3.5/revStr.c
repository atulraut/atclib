/*
* Aim : Reverse String.
* Author : Atul Ramesh Raut
* Date   : March 30, 2012 08:47PM
*
***/

#include <stdio.h>
#include <stdlib.h>

void revStr (char *);

int main () {
  printf ("\nHello world .. !! \n");
  char arr[10] = "Atul";
  revStr (arr);
  return EXIT_SUCCESS; 
}

void revStr (char *s) {
        char *p = NULL;
        char temp;
        p = s;               
        while (*p != '\0')
                p++;
	p--;
        while (s < p) {
                temp = *s;
                *s = *p;
                *p = temp;                
                s++;      
		p--;
        }
	p--;
	printf ("\n Reverse String = %s\n", p);        
}
