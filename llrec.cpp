#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************



static void llpivotHelper(Node* current, int pivot, 
                          Node*& smallerHead, Node*& smallerTail, 
                          Node*& largerHead, Node*& largerTail) {
    if (!current) return;  
    
    Node* next = current->next; 
    current->next = NULL;       
    
    
    if (current->val <= pivot) {
        if (!smallerHead) {
            smallerHead = current;
            smallerTail = current;
        } else {
            smallerTail->next = current;
            smallerTail = current;
        }
    } else {
        if (!largerHead) {
            largerHead = current;
            largerTail = current;
        } else {
            largerTail->next = current;
            largerTail = current;
        }
    }
    
   
    llpivotHelper(next, pivot, smallerHead, smallerTail, largerHead, largerTail);
}

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
    
    smaller = NULL;
    larger = NULL;
    Node* smallerTail = NULL;
    Node* largerTail = NULL;
    
    llpivotHelper(head, pivot, smaller, smallerTail, larger, largerTail);
    
    head = NULL;
}
