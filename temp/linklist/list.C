/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 * list.C -
 *     Implements a generic sorted list.
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include  <stdlib.h>
#include  <stdio.h>
#include  <assert.h>
#include  <memory.h>

#include  "list.h"

/*--- Types ---*/

typedef  struct _list_cell_t {
    void  * data;
    struct  _list_cell_t  * next;
}  list_cell_t;

/*--- Start of Code ---*/
void   list_init( list_t  * p_list, ptr_compare_func  p_cmp_func )
{
    assert( ( p_list != NULL )  &&  ( p_cmp_func != NULL ) );

    memset( p_list, 0, sizeof( list_t ) );

    p_list->p_cmp_func = p_cmp_func;
    p_list->head = NULL;  // not necessary here    
}

void   list_term( list_t  * p_list )
{
    list_cell_ptr  p_cell, p_next;

    p_cell = p_list->head;
    while ( p_cell != NULL ) {
        p_next = p_cell->next;
        memset( p_cell, 0, sizeof( list_cell_t ) );
        free( p_cell );
        p_cell = p_next;
    }

    memset( p_list, 0, sizeof( list_t ) );
}

void   list_insert( list_t  * p_list, void  * data )
{
    list_cell_ptr  * p_curr_ptr, p_tmp;
    ptr_compare_func  p_cmp_func;

    assert( p_list != NULL );

    p_cmp_func = p_list->p_cmp_func;
 
    p_tmp = (list_cell_ptr)malloc( sizeof( list_cell_t ) );
    assert( p_tmp != NULL );
    memset( p_tmp, 0, sizeof( list_cell_t ) );
    p_tmp->data = data;

    p_curr_ptr = &(p_list->head);
    while  ( *p_curr_ptr != NULL ) {
        if  ( (*p_cmp_func)( (*p_curr_ptr)->data, data ) >= 0 ) {
            p_tmp->next = *p_curr_ptr;
            *p_curr_ptr = p_tmp;
            return;
        }
        p_curr_ptr = &((*p_curr_ptr)->next);
    }

    *p_curr_ptr = p_tmp; 
    p_tmp->next = NULL;  // not necessary - we know it is null...
}

bool   list_delete( list_t  * p_list, void  * data )
{
    list_cell_ptr  * p_curr_ptr, p_tmp;
    ptr_compare_func  p_cmp_func;

    assert( p_list != NULL );

    p_cmp_func = p_list->p_cmp_func;
 
    p_curr_ptr = &(p_list->head);
    while  ( *p_curr_ptr != NULL ) {
        if  ( (*p_cmp_func)( (*p_curr_ptr)->data, data ) == 0 ) {
            p_tmp = *p_curr_ptr;
            *p_curr_ptr = ((*p_curr_ptr)->next);
            free( p_tmp );
            return  true;
        }
        p_curr_ptr = &((*p_curr_ptr)->next);
    }

    return  false;
}

void  list_iterator_init( list_iterator  * p_iter, list_t  * lst )
{
    assert( ( p_iter != NULL )  &&  ( lst != NULL ) );
    
    *p_iter = lst->head;
}

void  list_iterator_next( list_iterator  * p_iter )
{
    *p_iter = (*p_iter)->next;
}

bool  list_iterator_is_done( list_iterator  iter )
{
    return( iter == NULL );
}

void  * list_iterator_get_data( list_iterator  iter )
{
    assert( iter != NULL );
    return  iter->data;
}

/* list.C - End of File ------------------------------------------*/
