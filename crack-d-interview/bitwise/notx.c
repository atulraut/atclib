/*
 Problem : Write a program to convert 3 binary variables (takes either 0 or 1 value), X, Y and Z
 and gives NOT(X), NOT(Y) and NOT(Z). Note that NOT(X) = 1 if X=0  and NOT(X) = 0 if X=1.
 Inside the program you can only use two NOT operations but can use any number of AND and OR operations.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _not {
	int a;
	int b;
	int c;
} not;

int setBitXor(int x, int y);
void getNot (not va);

int main () {
	not var;
	var.a = 1;
	var.b = 0;
        var.a = getIt (var.a);
	var.b = getIt (var.b);
	printf ("[IN]  a=%d, b=%d\n",  var.a, var.b);
//	getNot(var);
}

/*2! only to used*/
void getNot (not va) {
	printf ("[IN]  a=%d, b=%d, c=%d\n",  va.a, va.b);
//	if (va.a == 0)
//		va.a = setBitXor(va.a, 1);
//	else 
		va.a = setBitXor(va.a, 0);
//	if (va.b == 0)
		va.b = setBitXor(va.b, 1);
//	else 
//		va.b = setBitXor(va.b, 0);
	printf ("[OUT] a=%d, b=%d\n",  va.a, va.b);
}

int setBitXor(int x, int y) {
    printf ("[IN]  x=%d, y=%d\n", x,y);
    int a;
    if (y == 0)
        a = x & ~y;
    else
	a = x & y;
    printf ("a=[%d] ", a);
    int b = ~x & ~y;
    printf ("b=[%d]", b);
    int z = ~a & ~b;
    printf (" z=[%d]\n", z);
    return z;
}     

int getIt (int n) {
	return ~n;
}
