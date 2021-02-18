/*
   Swap two integers in a one step
*/

#include<stdio.h>

int main() {
    int a,b;
    printf("Enter two numbers\n");
    scanf("%d%d",&a,&b);
    printf("a=%d, b=%d\n",a,b);
    b = a + b - (a = b);
    printf("\n After swap a=%d b=%d \n",a,b);
    return 0;
}
