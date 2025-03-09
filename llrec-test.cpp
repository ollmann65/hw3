#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------


struct RemoveOdd {
    bool operator()(int value) {
        return (value % 2) != 0;
    }
};
Node* cloneList(Node* head) {
    if (!head) return NULL;
    Node* newHead = new Node(head->val, NULL);
    Node* currentNew = newHead;
    Node* currentOld = head->next;
    while (currentOld) {
        currentNew->next = new Node(currentOld->val, NULL);
        currentNew = currentNew->next;
        currentOld = currentOld->next;
    }
    return newHead;
}

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    Node* smaller = NULL;
    Node* larger = NULL;
    
    Node* listForPivot = cloneList(head);

    llpivot(listForPivot, smaller, larger, 5);
    
    cout << "After llpivot with pivot 5:" << endl;
    cout << "Smaller (<=5): ";
    print(smaller);
    cout << "Larger (>5): ";
    print(larger);

    dealloc(smaller);
    dealloc(larger);
    
    Node* listForFilter = readList(argv[1]);
    cout << "List before llfilter (remove odds): ";
    print(listForFilter);
    
    Node* filtered = llfilter(listForFilter, RemoveOdd());
    cout << "List after llfilter (only evens remain): ";
    print(filtered);
    
    dealloc(filtered);
    
    dealloc(head);
    
    return 0;

}
