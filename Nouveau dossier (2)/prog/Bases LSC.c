#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
    int data;
    struct Element* next;
} Element;

/*
 Build the list {1, 2, 3} in the heap and store
 its head pointer in a local stack variable.
 Returns the head pointer to the caller.
*/
Element* BuildOneTwoThree()
{
    Element* head = NULL;
    Element* second = NULL;
    Element* third = NULL;
    head = malloc(sizeof(Element)); // allocate 3 nodes in the heap
    second = malloc(sizeof(Element));
    third = malloc(sizeof(Element));
    head->data = 1; // setup first node
    head->next = second; // note: pointer assignment rule
    second->data = 2; // setup second node
    second->next = third;
    third->data = 3; // setup third link
    third->next = NULL;
// At this point, the linked list referenced by "head"
// matches the list in the drawing.
    return head;
}

/*
 Given a linked list head pointer, compute
 and return the number of nodes in the list.
*/
int Length(Element* head)
{
    Element* current = head;
    int count = 0;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

/*
 Takes a list and a data value.
 Creates a new link with the given data and pushes
 it onto the front of the list.
 The list is not passed in by its head pointer.
 Instead the list is passed in as a "reference" pointer
 to the head pointer -- this allows us
 to modify the caller's memory.
*/
void Push(Element** headRef, int data)
{
    Element* newNode = malloc(sizeof(Element));
    newNode->data = data;
    newNode->next = *headRef; // The '*' to dereferences back to the real head
    *headRef = newNode; // ditto
}

Element* AddAtHead()
{
    Element* head = NULL;
    int i;
    for (i=1; i<6; i++)
    {
        Push(&head, i);
    }
// head == {5, 4, 3, 2, 1};
    return(head);
}


Element* AppendNode(Element** headRef, int num)
{
    Element* current = *headRef;
    Element* newNode;
    newNode = malloc(sizeof(Element));
    newNode->data = num;
    newNode->next = NULL;
// special case for length 0
    if (current == NULL)
    {
        *headRef = newNode;
    }
    else
    {
// Locate the last node
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    return NULL;
}



struct Element* CopyList(Element* head)
{
    Element* current = head; // used to iterate over the original list
    Element* newElement = NULL; // head of the new list
    Element* tail = NULL; // kept pointing to the last node in the new list
    while (current != NULL)
    {
        if (newElement == NULL)   // special case for the first new node
        {
            newElement = malloc(sizeof(Element));
            newElement->data = current->data;
            newElement->next = NULL;
            tail = newElement;
        }
        else
        {
            tail->next = malloc(sizeof(Element));
            tail = tail->next;
            tail->data = current->data;
            tail->next = NULL;
        }
        current = current->next;
    }
    return(newElement);
}


// Variant of CopyList() that uses Push()
Element* CopyList2(Element* head)
{
    Element* current = head; // used to iterate over the original list
    Element* newList = NULL; // head of the new list
    Element* tail = NULL; // kept pointing to the last node in the new list
    while (current != NULL)
    {
        if (newList == NULL)   // special case for the first new node
        {
            Push(&newList, current->data);
            tail = newList;
        }
        else
        {
            Push(&(tail->next), current->data); // add each node at the tail
            tail = tail->next; // advance the tail to the new last node
        }
        current = current->next;
    }
    return(newList);
}

// Recursive variant
Element* CopyList_recursive(Element* head)
{
    Element* current = head;
    if (head == NULL) return NULL;
    else
    {
        Element* newList = malloc(sizeof(Element)); // make the one node
        newList->data = current->data;
        newList->next = CopyList_recursive(current->next); // recur for the rest
        return(newList);
    }
}

int main()
{





    return 0;
}
