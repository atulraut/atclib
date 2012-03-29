#include <stdio.h>
#include <stdlib.h>
#include "list.h"

NODE *head = NULL;

void m_Init (NODE *list) {
    list->data = 0;
    list->next = NULL;
    counter = 0;
}

NODE* m_CreateNodeL (int data) {
    counter++;
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

void m_delfirst() {

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
