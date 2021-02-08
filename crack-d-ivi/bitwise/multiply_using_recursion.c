#include <stdio.h>

/* Addition using bitwise operator */
unsigned int add2numbers( unsigned int n1, unsigned int n2) {

  do{
    n1=n1^n2;      /*sum*/
    n2=(n1^n2)&n2; /*carry*/
    n2=n2<<1;
  } while(n2);
  return(n1);
}

/* METHOD1 : multiplication table using recursive addition */
void print_table(unsigned int n){
  unsigned int ans = n;
  int i;
  printf("%u x 1 = %u\n",n,ans);
  for (i=2; i<=10; i++){
    ans = add2numbers(ans,n);
    printf("%u x %d = %u\n",n,i,ans);
  }
}

int main(){
  unsigned int num;
  printf("Enter the number whose table to be printed");
  scanf(" %u",&num);
  print_table(num);
}
