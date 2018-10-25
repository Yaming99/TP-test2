#include <stdio.h>
#include <stdlib.h>

typedef struct Element{

	int             data;
	struct Element  *next;

}              Element;

Element *createlist(int nbElement);
Element *createListRecursif(int nbElement);
Element *lsd_fibo_recursif(int nb);
Element *lsd_fibo(int nbElement);
int fibo_recursif(int n);
void afficher_unsurdeux_recursif(Element *list);
void afficher_unsurdeux(Element *list);

int main(){
    Element *list;

    list = lsd_fibo_recursif(7);
    printf("%d",position_recursif(list,5));

    afficher_unsurdeux(list);
    return 0;
}

/** PARTIE 2 **/
int croissante_recursif(Element *list)
{
    if (list == NULL || list->data >= list->next->data) return 0;
    else if (list->data < list->next->data) return 1;
    else croissante_recursif(list->next);
}

int croissante(Element *list)
{
    while((list != NULL) && (list->next != NULL)){
          if (list->next->data < list->data) return 0;
          else list = list->next;
    }
    return 1;
}

//d¨¦but erreur sur dernier
void afficher_unsurdeux_recursif(Element *list)
{
    if ((list != NULL) && (list->next->next != NULL) && (list->next != NULL)){
        printf("%d\t",list->data);
        afficher_unsurdeux_recursif(list->next->next);
    }
}

void afficher_unsurdeux(Element *list)
{
    while ((list != NULL)&&(list->next->next != NULL)){
        printf("%d\t",list->data);
        list = list->next->next;
    }
}
// fin

int nb_occurence_recursif(Element *list, int nb)
{
    if (list == NULL) return 0;
    else if(list->data != nb) return nb_occurence_recursif(list->next,nb);
    else return (nb_occurence_recursif(list->next,nb)+1);
}

int nb_occurence(Element *list, int nb)
{
   int compt;

   compt = 0;

   while (list != NULL){
        if (list->data == nb) compt ++;
        list = list->next;
   }
   return compt;
}
int position_recursif(Element *list, int nb)
{
    int p;

    if (list == NULL) return 0;
    else if (list->data == nb) return 1;
    p = position_recursif(list->next,nb);
    if (p == 0) return 0;
    else return (p+1);
}

int position(Element *list, int nb)
{
    int i;

    i = 1;
    while (list->data != nb){
        list = list->next;
        i++;
    }
    return i;
}

int tailleListe_recursif(Element *list)
{
    if (list == NULL) return 0;
    else return (1 + tailleListe_recursif(list->next));
}

int tailleListe(Element *list)
{
    int i;

    i = 0;

    while (list != NULL){
        list = list->next;
        i++;
    }
    return i;
}


/** PARTIE 1 **/
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

Element *lsd_fibo_recursif(int nb)
{
    Element *list;
    if (nb == 0) return 0;
    else {
        list = malloc (sizeof(Element));
        list->data = fibo_recursif(nb-1);
        list->next = lsd_fibo_recursif(nb - 1);
        return (list);
    }
}

int fibo_recursif(int n)
{
    if (n == 0 || n == 1) return n;
    else return (fibo_recursif(n-1)+fibo_recursif(n-2));
}

