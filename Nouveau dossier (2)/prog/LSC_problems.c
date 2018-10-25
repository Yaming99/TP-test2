#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct  Element
{
    int data;
    struct Element* next;
} Element;


// Return the number of Elements in a list (while-loop version)
int Length(Element* head)
{
    int count = 0;
    Element* current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return (count);
}

// Given a reference (pointer to pointer) to the head
// of a list and an int, push a new Element on the front of the list.
// Creates a new Element with the int, links the list off the .next of the
// new Element, and finally changes the head to point to the new Element.
void Push(Element** headRef, int newData)
{
    Element* newElement = malloc(sizeof(Element)); // allocate Element
    newElement->data = newData; // put in the data
    newElement->next = (*headRef); // link the old list off the new Element
    (*headRef) = newElement; // move the head to point to the new Element
}


void DeleteList(Element** headRef)
{
    Element* current = *headRef; // deref headRef to get the real head
    Element* next;
    while (current != NULL)
    {
        next = current->next; // note the next pointer
        free(current); // delete the node
        current = next; // advance to the next node
    }
    *headRef = NULL; // Again, deref headRef to affect the real head back
// in the caller.
}


// Change the passed in head pointer to be NULL
// Uses a reference pointer to access the caller's memory
void ChangeToNull(Element** headRef) // Takes a pointer to the value of interest
{
    *headRef = NULL; // use '*' to access the value of interest
}

void ChangeCaller()
{
    Element* head1;
    Element* head2;
    ChangeToNull(&head1); // use '&' to compute and pass a pointer to
    ChangeToNull(&head2); // the value of interest
    // head1 and head2 are NULL at this point
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

int GetNth(Element* head, int index)
{
    Element* current = head;
    int count = 0; // the index of the Element we're currently looking at
    while (current != NULL)
    {
        if (count == index) return(current->data);
        count++;
        current = current->next;
    }
    assert(0); // if we get to this line, the caller was asking
    // for a non-existent element so we assert fail.
}


void Delete_List(Element** headRef)
{
    Element* current = *headRef; // deref headRef to get the real head
    Element* next;
    while (current != NULL)
    {
        next = current->next; // note the next pointer
        free(current);       // delete the Element
        current = next;     // advance to the next Element
    }
    *headRef = NULL; // Again, deref headRef to affect the real head back in the caller.
}

int Pop(Element** headRef)
{
    Element* head;
    int result;
    head = *headRef;
    assert(head != NULL);
    result = head->data;   // pull out the data before the Element is deleted
    *headRef = head->next; // unlink the head Element for the caller
    // Note the * -- uses a reference-pointer
    // just like Push() and DeleteList().
    free(head); // free the head Element
    return(result); // don't forget to return the data from the link
}

void Append(Element** aRef, Element** bRef)
{
    Element* current;
    if (*aRef == NULL)   // Special case if a is empty
    {
        *aRef = *bRef;
    }
    else   // Otherwise, find the end of a, and append b there
    {
        current = *aRef;
        while (current->next != NULL)   // find the last Element
        {
            current = current->next;
        }
        current->next = *bRef; // hang the b list off the last Element
    }
    *bRef=NULL; // NULL the original b, since it has been appended above
}

void MoveElement(Element** destRef, Element** sourceRef)
{
    Element* newElement = *sourceRef; // the front source Element
    assert(newElement != NULL);
    *sourceRef = newElement->next; // Advance the source pointer
    newElement->next = *destRef; // Link the old dest off the new Element
    *destRef = newElement; // Move dest to point to the new Element
}

/*
 Iterative list reverse.
 Iterate through the list left-right.
33
 Move/insert each Element to the front of the result list --
 like a Push of the Element.
*/
void Reverse(Element** headRef)
{
    Element* result = NULL;
    Element* current = *headRef;
    Element* next;
    while (current != NULL)
    {
        next = current->next; // tricky: note the next Element
        current->next = result; // move the Element onto the result
        result = current;
        current = next;
    }
    *headRef = result;
}

void RecursiveReverse(Element** headRef)
{
    Element* first;
    Element* rest;
    if (*headRef == NULL) return; // empty list base case
    first = *headRef; // suppose first = {1, 2, 3}
    rest = first->next; // rest = {2, 3}
    if (rest == NULL) return; // empty rest base case
    RecursiveReverse(&rest); // Recursively reverse the smaller {2, 3} case
    // after: rest = {3, 2}
    first->next->next = first; // put the first elem on the end of the list
    first->next = NULL; // (tricky step -- make a drawing)
    *headRef = rest; // fix the head pointer
}




int main()
{
    return 0;
}
