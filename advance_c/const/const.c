/***
    http://c-faq.com/ansi/constasconst.html
 */
#include <limits.h>
#include <stdio.h>

void foo () {
  // const int n = 5; /* Error : Mention Below in comments */
  const int n = 5;
  int arr[n];// = {0};

  for (int i=0; i<n; i++)
    printf ("[%s] Enter val = %d L=%d \n", __func__, arr[i], __LINE__);
}

int main() {
  printf("\n\n Biggest int is %d \n", INT_MAX);
  printf ("-->sizeof Int %ld \n\n", sizeof(int));

  foo();
  return 0;
}

/***
    atul@Raigad:~/dev/c/practice
    => gcc main.c
    ./main.c: In function ‘foo’:
    main.c:6:3: error: variable-sized object may not be initialized
    int arr[n] = {0};
    ^
    main.c:6:17: warning: excess elements in array initializer
    int arr[n] = {0};
    ^
    main.c:6:17: note: (near initialization for ‘arr’)
    aatul@Raigad:~/dev/c/practice
*/
