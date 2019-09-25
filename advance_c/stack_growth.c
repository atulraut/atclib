/*
* Aim : Check size of stack, its grows upward or downward.
* Sol : Determine the direction of stack growth is to compare 
* the address of a fun** ction parameter with the address of 
* a local variable in the function. Of course, * the main difficulty 
* here is to avoid compiler optimization, such as register variables, 
* function inlining.
* In UNIX,Stacks begin @ Higher address and start downwards as new things getting inside.
***/

#include <stdio.h>
#include <stdlib.h>

void stack_growth(int *p);

int main () {
        int *ptr = 10;
        printf ("ptr = %p, &ptr = %p\n", ptr, &ptr);
        stack_growth(ptr);
        stack_growth(ptr);
        stack_growth(ptr);
}

void stack_growth(int *p) {
        int local;
        printf ("p= %p, &p= %p, local = %p, &local = %p\n", p, &p, local, &local);
        if (!p)
                stack_growth(&local);
        else if (&local > p)
                printf("Stack grows upward\n");
        else
                printf("Stack grows downward\n");
}

/*
* Output
* => ./a.out
* ptr = 0xa, &ptr = 0x7fff14bb25d8
* p= 0xa, &p= 0x7fff14bb25a8, local = 0x7eff, &local = 0x7fff14bb25bc
* Stack grows upward
* p= 0xa, &p= 0x7fff14bb25a8, local = 0x7eff, &local = 0x7fff14bb25bc
* Stack grows upward
* p= 0xa, &p= 0x7fff14bb25a8, local = 0x7eff, &local = 0x7fff14bb25bc
* Stack grows upward
**/
