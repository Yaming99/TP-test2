#include <stdio.h>
#include <stdlib.h>

typedef struct Element{

	int             data;
	struct Element  *next;

}              Element;

Element *createlist(int nbElement)
{
    Element *list = NULL;
    Element *prec = NULL;

    while (nbElement > 0){

        list = malloc(sizeof(Element));
        list->data = nbElement;
        list->next = prec;
        prec = list;
        nbElement--;
    }
    return (list);
}

Element *createListRecursif(int nbElement)
{
    Element *list;
    if (nbElement == 0) return NULL;
    else {
        list = malloc (sizeof(Element));
        list->data = nbElement;
        list->next = createListRecursif(nbElement - 1);
        return (list);
    }
}

Element *lsd_fibo(int nbElement)
{
    Element *list;
    Element *prec = NULL;
    int first = 0;
    int second = 1;
    int temp;
    int i;
    for (i=0; i<nbElement; i++){
        list = malloc(sizeof(Element));
        if (i == 0 || i == 1){
            list->data = i;
            list->next = prec;
            prec = list;
        }
        else {
            temp = first + second;
            first = second;
            second = temp;
            list->data = temp;
            list->next = prec;
            prec = list;
        }
    }
    return (list);
}

Element *lsd_fibo_recursif(int nb){
    Element *list;
    if (nb == 0) return NULL;
    else {
        list = malloc (sizeof(Element));
        list->data = nb;
        list->next = lsd_fibo_recursif(nb - 1);
        return (list);
    }
}

int main(){

    return 0;
}

