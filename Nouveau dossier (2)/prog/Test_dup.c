#include <stdio.h>
#include <stdlib.h>


typedef struct Element
{
    int data;
    struct Element* next;
} Element;

typedef Element* list;

list dupl_list(list l)
{
    if (!l) return NULL;
    list temp = malloc(sizeof(Element));
    list prout = temp;
    while(l->next)
    {
        temp->data = l->data;
        temp->next = malloc(sizeof(Element));
        l = l->next;
        temp = temp->next;
    }
    temp->data = l->data;
    temp->next = NULL;
    return prout;
}

void delete_(Element** liste, int data)
{
    Element* temp = *liste;
    Element* prev = NULL;
    if(temp && temp->data == data) //si c'est le premier
    {
        *liste = temp->next;
        free(temp);
        return;
    }
    while(temp && temp->data != data) //on cherche le maillon avec data
    {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return; //si data est pas dans la liste
    prev->next = temp->next; //court-circuit
    free(temp);
}

void affiche(list l)
{
    while(l)
    {
        printf("%d\t", l->data);
        l = l->next;
    }
}

int main()
{
    list a = malloc(sizeof(Element));
    list b = malloc(sizeof(Element));
    a->data = 0;
    a->next = b;
    b->data = 1;
    b->next = NULL;
    list c = dupl_list(a);
    affiche(c);
    return 0;
}
