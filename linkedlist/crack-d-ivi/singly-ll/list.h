#ifndef ADD_H_LIST
#define ADD_H_LIST

struct node {
    int data;
    struct node *next;
};

int counter;
void m_Init (struct node *);
struct node* m_CreateNodeL (int);
void m_Display();
void m_Addfirst(int);
void m_Addlast(int);
void m_Insert(int,int);
void m_Delfirst();
void m_Deletenode(int);
void m_Dellast();
void m_Printrev ();
void m_Freelist();

#endif
