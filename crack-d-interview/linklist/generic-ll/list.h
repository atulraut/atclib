#ifndef ADD_H_LIST
#define ADD_H_LIST

typedef struct list_t {
    void *data;
    struct list_t *next;
} NODE;

int counter;
void m_Init (NODE *);
NODE* m_CreateNodeL (void*);
void m_Display();
void m_Addfirst(void*);
void m_Addlast(void*);
void m_Insert(int,int);
void m_Delfirst();
void m_Deletenode(int);
void m_Dellast();
void m_Printrev ();
void m_Freelist();

#endif
