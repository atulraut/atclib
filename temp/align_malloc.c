#include <stdio.h>
#include <stdlib.h>
/*
* Ref/Credit - http://www.careercup.com/question?id=2777 
*/

void *_aligned_malloc(size_t bytes, size_t alignment);
void _aligned_free(void *p );

void *_aligned_malloc(size_t bytes, size_t alignment)
{
void *p1 ,*p2; // basic pointer needed for computation.

if((p1 =(void *) malloc(bytes + alignment + sizeof(size_t)))==NULL)
    return NULL;

printf ("\n 1. p1 = %p \n", p1);
/*	Next step is to find aligned memory address multiples of alignment.
By using basic formule I am finding next address after p1 which is 
multiple of alignment.I am storing new address in p2.
*/
size_t addr=(size_t)p1+alignment+sizeof(size_t);

p2=(void *)(addr - (addr%alignment));

printf ("\n2. p2 = %p \n", p2);

/*	Final step, I am storing the address returned by malloc 'p1' just "size_t"
bytes above p2, which will be useful while calling aligned_free.
*/
 printf ("\n p2 = %p p2-1= %p p1 = %p \n", p2, p2-1, p1);
 
*((size_t *)p2-1)=(size_t)p1;

    return p2;
}

void _aligned_free(void *p )
{
/*	Find the address stored by aligned_malloc ,"size_t" bytes above the 
current pointer then free it using normal free routine provided by C.
*/
    free((void *)(*((size_t *) p-1)));
}

void main (int argc, char *argv[])
{

    int *p = _aligned_malloc (50, 128);

    printf ("p = %p\n", p);
    _aligned_free (p);
}
