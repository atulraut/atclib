#include <stdio.h>

//pointer to a const
void f1()
{
    int i = 100;
    int j = 200;
    const int* pi = &i;
    //*pi = 200; <- won't compile : error: assignment of read-only location ‘*pi’
    pi = &j;
    printf ("[%s] pi = %d \n", __func__, *pi);
    pi++;
}

//const pointer
void f2()
{
    int i = 100;
    int j = 200;
    int* const pi = &i;
    *pi = 200;
    //pi++; <- won't compile : error: increment of read-only variable ‘pi’
    //pi = &j; <- error: assignment of read-only variable ‘pi’
    printf ("[%s] pi = %d \n", __func__, *pi);
}

//const pointer to a const
void f3()
{
    int i = 100;
    const int* const pi = &i;
    //*pi = 200; <- won't compile
    //pi++; <- won't compile
    printf ("[%s] pi = %d \n", __func__, *pi);
}

int main()
{
   printf("Enter! \n");  // 24
    f1();
    f2();
    f3();
   printf("End! \n"); ///16
     return 0;
}
