#ifndef ADD_H_LIST
#define ADD_H_LIST

typedef struct list_t {
    int data;
    struct list_t *next;
} NODE;

void m_Init (NODE *);
NODE* m_CreateNodeL (int);
void m_Display();
void m_Addfirst(int);
void m_Addlast(int);
void m_Insert(int,int);
void m_Delfirst();
void m_Deletenode(int);
void m_Dellast();
void m_Freelist();
int m_FindCircular();
#endif
