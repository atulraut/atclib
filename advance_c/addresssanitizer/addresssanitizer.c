/***
    https://embeddedbits.org/finding-memory-bugs-with-addresssanitizer/
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    char *msg = "Hello world!";
    char *ptr = NULL;

    ptr = malloc(strlen(msg));

    /* Fix */
    //    ptr = malloc(strlen(msg)+1);

    strcpy(ptr, msg);

    printf("%s\n", ptr);

    /* Fix */
    //    free(ptr);
    return 0;
}

/***
    Step I :
    $ gcc main.c -o main -Wall -Werror -g
    $ ./main
    Hello world!
    Step II :
    $ gcc main.c -o main -Wall -Werror -g -fsanitize=address
*/
