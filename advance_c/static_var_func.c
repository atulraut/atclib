/*
* Aim : C Static Variables and Static Functions Explained with Examples
* Reference : http://www.thegeekstuff.com/2012/08/c-static-variables-functions/
* Date : 17-07-2014
***/

#include<stdio.h>

char** func1_Str();
char** func2_Str();

int main(void)
{
    char **ptr1 = NULL;
    char **ptr2 = NULL;

    ptr1 = func1_Str();
    printf("\n [%s] :: func1_Str() address = [%p], its returned address is [%p]\n",*ptr1,(void*)func1_Str,(void*)ptr1);

    ptr2 = func2_Str();
    printf("\n [%s] :: func2_Str()address = [%p], its returned address is [%p]\n",*ptr2,(void*)func2_Str,(void*)ptr2);

    printf("\n [%s] [%p]\n",*ptr1,(void*)ptr1);

    return 0;
}

char** func1_Str()
{
    static char *p = "Linux";
    return &p;
}

char** func2_Str()
{
    static char *p = "Windows";
    return &p;
}

/*
*$ ./static 
* $[Linux] :: func1_Str() address = [0x4005d5], its returned address is [0x601028]
* $[Windows] :: func2_Str()address = [0x4005e0], its returned address is [0x601020]
* $[Linux] [0x601028]
* Reason : The above output makes it clear that once the lifetime of the local 
* variable of the function ‘func1_Str()’ gets over then same memory address is 
* being used for the local pointer variable of the function ‘func2_Str()’ and 
* hence the third print is ‘Windows’ and not ‘Linux’. 
***/