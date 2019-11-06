#include <stdio.h>
#include <stdlib.h>

int multiply(int x, int y) {
        if (y == 0)
                return 0;

        if(y > 0) {
                return (x+multiply(x, y-1));
        }

        if(y < 0) {
                return -multiply(x, -y);
        }
}

int main () {
        printf ("multiplication --> %d\n\n", multiply(5, -11));
}
