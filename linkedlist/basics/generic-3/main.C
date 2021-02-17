/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 * main.C -
 *     Demonstrate the using of a generic sorted list. This
 * is done using pointers to functions (to compare the elements
 * of the lists). Note that the code here is completely
 * indepenedent of the way the list package is being
 * implemented.
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include  <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <assert.h>

#include  "list.h"

/*--- Start of Code ---*/

// Comparision function between two ints
static int  compare_int( void  * a_ptr, void  * b_ptr )
{
    int  a_num, b_num;

    a_num = (int)a_ptr;
    b_num = (int)b_ptr;

    return  a_num - b_num;
}


// Comparision function between two strings
static int  compare_str( void  * a_ptr, void  * b_ptr )
{
    char  * a_str, * b_str;

    a_str = (char *)a_ptr;
    b_str = (char *)b_ptr;

    return  strcmp( a_str, b_str );
}


// print a list of ints
static void   list_int_print( list_t  * p_list )
{
    list_iterator  iter;
    int  num;

    list_iterator_init( &iter, p_list );
    while  ( ! list_iterator_is_done( iter ) ) {
        num = (int)list_iterator_get_data( iter );
        printf( "%d ", num );

        list_iterator_next( &iter );
    }
    printf( "\n" );
}


// print a list of strings
static void   list_str_print( list_t  * p_list )
{
    list_iterator  iter;
    char  * str;

    list_iterator_init( &iter, p_list );
    while  ( ! list_iterator_is_done( iter ) ) {
        str = (char *)list_iterator_get_data( iter );
        printf( "[%s] ", str );

        list_iterator_next( &iter );
    }
    printf( "\n" );
}


static void   list_int_fill_random( list_t  * p_list, int  size )
{
    int  ind, num;

    for  ( ind = 0; ind < size; ind++ ) {
        num = rand() / 10000;
        list_insert( p_list, (void *)num );
    }
}

static void  list_str_fill( list_t  * p_list )
{
    list_insert( p_list, (void *)"Make" );
    list_insert( p_list, (void *)"Money" );
    list_insert( p_list, (void *)"Fast" );
    list_insert( p_list, (void *)" - " );
    list_insert( p_list, (void *)"Learn" );
    list_insert( p_list, (void *)"Programming" );
    list_insert( p_list, (void *)"In" );
    list_insert( p_list, (void *)"C" );
}


int  main()
{
    list_t  list_str, list_int;

    // Our code assumes that...
    assert( sizeof( int ) <= sizeof( void * ) );
    assert( sizeof( void * ) == sizeof( char * ) );
            // this is guarenteed by the standard...

    // Using the list for strings
    list_init( &list_str, compare_str );

    list_str_fill( &list_str );
    list_str_print(  &list_str );

    list_term( &list_str );

    // Using the list for ints
    list_init( &list_int, compare_int );

    list_int_fill_random( &list_int, 100 );
    list_int_print( &list_int );

    list_term( &list_int );

    return  0;
}

/* main.C - End of File ------------------------------------------*/
