/*
 * Prob : There are 5 stairs. you can take either 1 or 2 steps
 * How many combinations you can take to climb the stairs?
 * Ans is 8
 * Step 1: if don't use 2 steps .then only 1 way
 * Step 2: if we use single 2 steps ..then 4 ways
 * Step 3: if we use double 2 steps .then 3 ways
 * so total combintaion is 8
*/
#include <stdio.h>

int fab (int n);

int main() {
    int i=0, Res=0, lastRes=0;
    for (i=1; i<=5; i++) {
        lastRes = Res;
        Res =  fab(i);
        printf(" Res = %d \n", Res);
    }
    printf ("o/p = %d \n", lastRes+Res);
    return 0;
}

int fab (int n) {
    int Res;
    if (n==1 || n==2)
        return 1;
    Res = fab(n-1) + fab(n-2);
    return Res;
}
/*
Output
 Res = 1  Res = 1  Res = 2  Res = 3  Res = 5 
 o/p = 8 
*/
