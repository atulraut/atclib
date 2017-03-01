/*
* Aim : Reverse no, if i/p is 1234 o/p : 1000+200+30+4.
* Author : Atul Ramesh Raut
* Date   : March 30, 2012 08:47PM
*
***/

#include <stdio.h>
#include <stdlib.h>

void revNo ();

int main () {
  printf ("\nHello world .. !! \n");
  revNo ();
  return EXIT_SUCCESS; 
}

void revNo () { 
  char arr[10] = "Atul";   
  int temp = 1234;
  int a, b, c, d, n;
  n = temp;
  a = n / 1000; // a = 1;
  n = n%1000;   // n = 234;
  b = n / 100;  // b = 2;
  n = n%100;    // n = 34;
  c = n /10;    // c = 3;
  d = n%10;     // d = 4;
  printf ("I/P => %d, O/P => %d\n", temp, (d*1000)+(c*100)+(b*10)+ a);
}
