/***
    Decimal to any base :
    Write a C progam to convert from decimal to any base (binary, hex, oct etc...) ?
*/

#include <stdio.h>

#define debug(str,args...) printf("[%s] L=%d :"str"\n", __func__, __LINE__, ##args)

int decimal_to_anybase(int n, int base) {
  int i, m, digits[1000], flag;
  i=0;

  debug("[%d] converted to base [%d] : ", n, base);

  while(n) {
    m=n%base; digits[i]="0123456789abcdefghijklmnopqrstuvwxyz"[m];
    n=n/base; i++;
  } //Eliminate any leading zeroes

  for(i--;i>=0;i--) {
    if(!flag && digits[i]!='0')
      flag=1;
    if(flag)
      printf("%c",digits[i]);
  }
  printf ("\n");
}

int main() {
  decimal_to_anybase(10, 2);
  decimal_to_anybase(255, 16);
}

/***
    => ./a.out
    [decimal_to_anybase] L=14 :[10] converted to base [2] :
    1010
    [decimal_to_anybase] L=14 :[255] converted to base [16] :
    ff
*/
