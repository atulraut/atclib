/*
* Aim 	 : Singaly Circular Link List.
* Author : Atul Ramesh Raut
* Date   : Wednesday April 11, 2012. 02:30PM
* File   : circular-singly.c
***/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

NODE *head = NULL;

void m_Init (NODE *list) {
    list->data = 0;
    list->next = NULL;
}

NODE* m_CreateNodeL (int data) {
    NODE *nn = (NODE *)NULL;
    nn = (NODE *)malloc(sizeof(NODE));
    if (nn == NULL) {
        return;
    } else {
            nn->data = data;
            nn->next = NULL;
            return nn;
        }
}

void m_Addfirst(int data) {
    NODE *nn = NULL;
    nn = m_CreateNodeL (data);
    if (head == NULL) {
        head = nn;
    } else {
            nn->next = head;
            if (head->next == NULL)
                head->next = nn;
            else {
                    NODE *trav = NULL;
                    trav = head->next;
                    while (head != trav->next) {
                        trav = trav->next;
                    }
                    trav->next = nn;
            }
            head = nn;
        }
}

void m_Addlast(int data) {
    NODE *nn = NULL;
    nn = m_CreateNodeL (data);
    if (head == NULL) {
        head = nn;
    }
    else {
            NODE *trav = NULL;
            if (head->next == NULL) {
                head->next = nn;
                nn->next = head;
            }
            else {
                    trav = head->next;
                    while (trav->next != head) {
                        trav = trav->next;
                    }
                    trav->next = nn;
                    nn->next = head;
                }
        }
}

void m_Insert(int data, int pos) {
    printf ("\nI am LUTA LUTARATU\n");
    NODE *trav = NULL;
    int i;
    if (head == NULL || pos == 1) {
        m_Addfirst (data);
    }
    else {
            NODE *nn   = NULL;
            nn = m_CreateNodeL (data);
            if (head->next == NULL) {
                head->next = nn;
                nn->next = head;
            }
            else {
                    NODE *trav = NULL;
                    trav = head->next;
                    for (i=1; i<pos-1; i++)
                        trav = trav->next;
                    nn->next = trav->next;
                    trav->next == nn;
                }
    }
}

void m_Delfirst() {

}

void m_Deletenode(int data) {

}

void m_Dellast() {

}

void m_Freelist() {

}

void m_Display() {
    NODE *trav = NULL;
    trav = head->next;
    if (head != NULL)
        printf ("->[%d]", head->data);
    if (trav != NULL) {
        while (trav != head) {
            printf ("->[%d]", trav->data);
            trav = trav->next;
        }
    }
}
/*< Check linklist is Circular or not >*/
int m_FindCircular()
{
   Node *slower, * faster;
   slower = head;
   faster = head->next; //start faster one node ahead
   while(true) {
     // if the faster pointer encounters a NULL element
     if( !faster || !faster->next)
       return false;
    //if faster pointer ever equals slower or faster's next
    //pointer is ever equal to slow then it's a circular list
     else if (faster == slower || faster->next == slower)
        return true;
     else{
       // advance the pointers
        slower = slower->next;
        faster = faster->next->next;
      }
   }
}
