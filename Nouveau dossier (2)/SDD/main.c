#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
    int data;
    struct Element* next;
}Element;

Element* createelement (int newdata)
{
    Element* newelement;
    newelement = malloc(sizeof(Element));
    newelement->next = NULL;
    newelement->data = newdata;
    return newelement;
}

void addEltEnd(Element** myList, Element* elt)
{
    if(*myList == NULL)
    {
        *myList = elt;
    }
    else
    {
        Element* tmp;
        tmp = *myList;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = elt;
    }
}

void display(Element* myList)
{
    if (myList == NULL)
    {
        printf("X\n");
    }
    else
    {
        printf("%d ",myList->data);
        display(myList->next);
    }
}

int main()
{
    Element* test=NULL;
    for (int i = 0; i < 999; i++)
    {
        addEltEnd(&test,createelement(i));
    }
    display(test);
    return 0;
}

