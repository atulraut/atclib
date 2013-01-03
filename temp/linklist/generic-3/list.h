/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 * list.h -
 *     This is the interface to the generic sorted list. A
 * generic data structure is a structure that can handle various
 * types by using pointers to voids, and pointers to functions
 * to resolve decisions about objects (i.e. ordering of objects).
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#ifndef  __LIST__H
#define  __LIST__H

/* _list_cell_t is the type of a cell in a list. We do NOT give the
   details here what it contains. Therefore, the user of this
   package can NOT access the list directly... Which guarentees that
   we can change the implementation without causing any damage to
   other parts of our "project", because they use the list through our
   functions.

   This idea of hiding implementation details is one of the
   fandamental ideas behind object oriented programming and ADT
   (abstract data-types).
  */
struct _list_cell_t;
typedef struct _list_cell_t  * list_cell_ptr;

typedef  int    (*ptr_compare_func)( void  * a, void  * b );

typedef  struct {
    int  size;
    list_cell_ptr  head;
    ptr_compare_func  p_cmp_func;
}  list_t;


void   list_init( list_t  * p_list, ptr_compare_func  p_cmp_func );
void   list_term( list_t  * p_list );

void   list_insert( list_t  * p_list, void  * data );
bool   list_delete( list_t  * p_list, void  * data );

/* If we really want to work in an abstract way, we should use iterators */
typedef  struct _list_cell_t  * list_iterator;

void  list_iterator_init( list_iterator  * p_iter, list_t  * lst );
void  list_iterator_next( list_iterator  * p_iter );
bool  list_iterator_is_done( list_iterator  iter );
void  * list_iterator_get_data( list_iterator  iter );


#else   /* __LIST__H */
#error  Header file list.h included twice
#endif  /* __LIST__H */

/* list.h - End of File ------------------------------------------*/
