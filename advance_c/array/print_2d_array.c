/***
 * Print 2D array using, given just pointer of 1st element of array.
 * Interview Question, little tricky.
*/

#include <stdio.h>

int print_array (int *arr, int r, int c) {
    int i, j;
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            printf ("--> %d \t", (*(arr+i) +j) );
        }
        arr++;
        arr++;
        printf ("\n");
    }
}

int main() {
    int arr[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,8},
    };
    print_array (&arr[0][0], 3, 3);
    printf("Hello World");
    return 0;
}

/***
    => ./a.out
    --> 1 	--> 2 	--> 3
    --> 4 	--> 5 	--> 6
    --> 7 	--> 8 	--> 9
*/
