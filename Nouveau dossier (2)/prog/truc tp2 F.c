#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
    int data;
    struct Element* next;
}Element;

Element *FiboRecu(int Val)
{
    Element *list;
    int tmp;

    list=malloc(sizeof(Element));
    if(Val==0)return NULL;
    if(Val==1 || Val==2)
    {
        list->data=(Val-1);
        list->next=FiboRecu(Val-1);
    }
    else
    {
        tmp = FiboRecu(Val-1)->data + FiboRecu(Val-2)->data;
        list->data=tmp;
        list->next=FiboRecu(Val-1);
    }
    return (list);
}

void Afficher(Element *list)
{
    Element *tmp;
    tmp=list;
    while(tmp!=NULL)
    {
        printf("%d ",tmp->data);
        tmp=tmp->next;
    }
    return (list);
}

int main()
{
    printf("Hello world!\n");
    Afficher(FiboRecu(10));
    return 0;
}
