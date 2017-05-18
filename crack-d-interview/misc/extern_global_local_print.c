/*
code base query : Need the out put to be printed as 10.
int a=10; 
void main() {
        int a=20;
        printf("%d",a);
}
Solution : Use the extern specifier in a new compound statement.

*/

#include <stdio.h>      
int a = 10;

int main(void) {           
    int a = 20;             
    printf(" Inside a's main local a = : %d\n", a);

    {
        extern int a;
        printf("In a global a = %d\n", a);
    }

    return 0; 
}

/*
o/p :
Inside a's main local a = : 20
In a global a = 10
*/
