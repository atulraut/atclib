#include <stdio.h>  

main() {
        int a= 5;
        int *p= &a;
        *p++; 
        p--;
        printf("\n *p = %d, a = %d \n",*p,a); // O/p = *p = 5, a = 5 
       (*p)++;
        p--;
        printf("\n *p = %d, a = %d \n",*p,a); // O/p = *p = 0, a = 6                  
}
