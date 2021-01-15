#ifndef ADD_H_LIST
#define ADD_H_LIST

struct list_t {
    int data;
    struct list_t *next;
} node;

int counter;
void m_Init (struct list_t *node);
struct list_t* m_CreateNodeL (int);
void m_Display();
void m_Addfirst(int);
void m_Addlast(int);
void m_Insert(int,int);
void m_Delfirst();
void m_Deletenode(int);
void m_Dellast();
void m_Printrev ();
struct list_t* m_plusOne(); /* LeetCode */
void m_Freelist();

#endif
