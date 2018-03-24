/*
Check number is Palindrome or not.
*/
#include <stdio.h>

int isNumberPalindrome(int x) {
     if(x < 0)             
         return -1;         
    int n = 1;         
    while(x / n >= 10) {
        printf ("[A] = %d n=%d\t", (x/n), n);
        n *= 10;
        printf ("[B] n=%d\t", n);
    }
    printf ("\n"); 
    while(n > 1) {
        printf ("1 M = %d D = %d \n", (x % 10), (x / n));
         if( (x % 10) != (x / n) ) {
            printf (" 2 Returning -1\n"); 
                return -1;
         }
        x = (x % n) / 10;
        printf ("3 Mx = %d \n", (x%n));
        printf ("3 x = %d \n", x); 
        n /= 100;
        printf ("4 n = %d \n", n);
    }
    return 1;
}

int main()
{
    printf("Hello World L = %d ", isNumberPalindrome(101) );

    return 0;
}

/*
O/P - 

About • FAQ • Blog • Terms of Use • Contact Us • GDB Tutorial • Credits
2018 © GDB Online
Language

    main.c

    input

[A] = 101 n=1   [B] n=10        [A] = 10 n=10   [B] n=100                                             1 M = 1 D = 1                                                                                         3 Mx = 0
3 x = 0
4 n = 1
Hello World L = 1  
*/
