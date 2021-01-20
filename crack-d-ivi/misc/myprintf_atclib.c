/* Example using va_start : Remember LSAE - Leela-Shakuntala-Atul-End
   va_list : It is a Data Type for accessing data from variable argument list.
   va_start: It is a micro that initialize the variable arg. list to the 1st argument.
   va_arg  : Fetching 'int' Data Type that's why here int, if ur data type change mention here
   va_end  : End variable arg list.
 **/

#include <stdio.h>
#include <stdarg.h>

int add(int n, ...) {
    /* va_list: It is a Data Type for accessing data from
     * variable argument list
     **/
    va_list arglist;
    int total = 0, i;

   /* va_start: It is a micro that initialize the
    * variable arg. list to the 1st argument.
    **/
    /* Set where the variable length part of the argument list ends */
    va_start(arglist, n);

    /* Loop through each argument adding the int values */
    for (i=0; i < n; i++)
        total = total + va_arg(arglist, int); /* Fetching 'int' Data Type that's why here int, if ur data type change mention here*/

    /* Clean up */
    va_end(arglist);

    /* Return the calculated total */
    return total;
}

int main(int argc, const char * argv[]) {
    int value1, value2, value3;
    int result;

    value1 = 3;
    value2 = 4;
    value3 = 5;

    result = add(3, value1, value2, value3);

    printf("The sum of %d, %d and %d is %d\n", value1, value2, value3, result);

    return 0;
}
