/*
* Write a function in library file that return a 32bit unique integer number every time the function get 
* called and function shouln't take any arguments?
* How above written library function to be take care in multi thread scenarios. 
*/

#include <stdio.h>
#include <stdlib.h>

int (irand) (void);
unsigned long _r  = 1;

int main() {
    int ret;
    ret = (irand) ();
    printf("\n Rand 1 =%d \n", ret);
    ret = (irand) ();
    printf("\n Rand 2 =%d \n", ret);
    ret = (irand) ();
    printf("\n Rand 3 =%d \n", ret);
    return 0;
}

int (irand) (void) {
    _r = _r * 1103515245 + 12345;
    return ((unsigned int) (_r >> 16) & RAND_MAX);
}
