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
void  otherWay();
void rev(char *l,char *r);
void reverseRecursive(char str1[], int index, int size);

int main () {
  printf ("\nHello world .. !! \n");
  char arr[10] = "Atul";
  revStr (arr);
  otherWay();
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
}
    
void revStr (char *str) {
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

void reverseRecursive(char str1[], int index, int size) {
    char temp;
    temp = str1[index];
    str1[index] = str1[size - index];
    str1[size - index] = temp;
    if (index == size / 2) {
        return;
    }
    reverseRecursive(str1, index + 1, size);
}

void rev(char *l,char *r) {
  char t;
  while(l<r) {
    t = *l;
    *l++ = *r;
    *r-- = t;
  }
}

void otherWay () {
  char buf[] = "Atul R Raut";
  char *end, *x, *y;
  for(end=buf; *end; end++); // reach enf of string first.
  rev(buf,end-1);
  printf("ANTU buf = %p, buf = %s end = %s \n",buf, buf, end);
  // Now swap each word within sentence...
  x = buf-1;
  y = buf;
  while(x++ < end) {
    if(*x == '\0' || *x == ' ') {
      rev(y,x-1);
      y = x+1;
    }
  } 
  printf("Output = %s\n",buf);
  reverseRecursive(buf, 0, (strlen(buf)-1));
  printf("Output = %s\n",buf);
}
