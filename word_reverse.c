/******************************************************************************
Given a String of length N reverse the words in it. Words are separated by dots.
Input:
The first line contains T denoting the number of testcases. Then follows description of testcases. 
Each case contains a string containing spaces and characters.
Output:
For each test case, output a single line containing the reversed String.
Constraints:
1<=T<=20
1<=Lenght of String<=2000
input:i.like.this.program.very.much
Output:
much.very.program.this.like.i
*******************************************************************************/

#include<stdlib.h>
#include <stdio.h>
#include <string.h>

void reverse(char a[], int i,int j) {
  char temp;

  while(i<j) {
      temp=a[i];
      a[i]=a[j];
      a[j]=temp;
      i++;
      j--;
    }
}

int main() {
  char a[]="Atul Raut";
  int i=0;
  int j=strlen(a);

  reverse(a,i,j-1);
  printf("Reversed String is --> [%s]\n",a);

  j=0;
  while(a[i]!='\0') {
    if(a[j]==' ' || a[j]=='\0') {
      reverse(a,i,j-1);
      i=j+1;
      j=i;
    } else {
      j++;
    }
  }
  printf("Reversed String is -->  [%s]\n",a);
}
