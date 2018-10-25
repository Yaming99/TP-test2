#include <stdio.h>
#include <stdlib.h>


typedef struct Element
{
    int data;
    struct Element* next;
} Element;

//Partie 1

Element* create_list(int nbList)
{
    Element* list = NULL;
    Element* prec = NULL;
    while (nbList > 0)
    {
        list = malloc(sizeof(Element));
        list->data = nbList;
        list->next = prec;
        prec = list;
        nbList--;
    }
    return (list);
}

void affichage(Element* list) //pas demandé mais ça aide
{
    Element* temp = list;
    while(temp)
    {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
}

Element* create_recu(int nbList, int max)
{
    Element* list;
    if (max == nbList + 1) return NULL;
    else
    {
        list = malloc(sizeof(Element));
        list->data = max;
        list->next = create_recu(nbList, max+1);
        return (list);
    }
}


Element* Fibo(int nb)
{
    Element* list;
    Element* prec = NULL;
    int first = 0;
    int second = 1;
    int temp, i;
    for(i=0; i<nb; i++)
    {
        list = malloc(sizeof(Element));
        if(i == 0 || i == 1)
        {
            list->data = i;
            list->next = prec;
            prec = list;
        }
        else
        {
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

int create_fibo_recur(int n)
{
    if (n == 0 || n == 1) return n;
    else return (create_fibo_recur(n-1) + create_fibo_recur(n-2));
}

Element* Fibo_recu(int nb)
{
    Element* list;
    if(nb == 0) return NULL;
    else
    {
        list = malloc (sizeof(Element));
        list->data = create_fibo_recur(nb-1);
        list->next = Fibo_recu(nb - 1);
        return (list);
    }
}

//Partie 2

int longueur(Element* list)
{
    int count = 0;
    Element* temp = list;
    while(temp)
    {
        count++;
        temp = temp->next;
    }
    return (count);
}

int long_recu(Element* list)
{
    if (list == NULL) return 0;
    else
    {
        return 1 + long_recu(list->next);
    }
}

int position(Element* list, int truc)
{
    int pos = 1;
    while(list)
    {
        if (list->data == truc) return pos;
        pos++;
        list = list->next;
    }
    return 0;
}

int pos_recu(Element* list, int truc)
{
    int p;
    if (list == NULL) return 0;
    else if(list->data == truc) return 1;
    else
    {
        p = pos_recu(list->next, truc);
        if (p == 0) return 0;
        else return (p + 1);
    }
}


int ocu(Element* list, int truc)
{
    int count = 0;
    while(list)
    {
        if (list->data == truc) count++;
        list = list->next;
    }
    return (count);
}


int ocu_recu(Element* list, int truc)
{
    if (list == NULL) return 0;
    else if (list->data == truc) return (1 + ocu_recu(list->next, truc));
    else return (ocu_recu(list->next, truc));
}


void un_sur_deux(Element* list)
{
    Element* temp = list;
    if(temp == NULL)
        return ;
    else
    {
        printf("%d\t",temp->data);
        if (temp->next!=NULL)
        {
            un_sur_deux(temp->next->next);
        }
    }
}


void un_sur_deux_recu(Element* list)
{
    /*Element* temp = list;
    if (temp)
    {
        printf("%d\t",temp->data);
        if (temp->next == NULL) return NULL;
        else un_sur_deux_recu(temp->next->next);
    }*/
    if(list == NULL) return;
    else
    {
        printf("%d\t", list->data);
        if (list->next != NULL) un_sur_deux_recu(list->next->next);
    }
}


void check_croissance(Element* list)
{
    int i = 0;
    Element* temp = list;
    while ((temp) && (temp->next) && (i == 0))
    {
        if (temp->data >= temp->next->data)
        {
            printf("\nC'est pas croissant.\n");
            i++;
        }
        else temp = temp->next;
    }
    if (i == 0) printf("\nC'est bien croissant.\n");
}


int CroisRec(Element *list)
{

    if(list==NULL || list->next == NULL)return 0;
    else if(list->next->data < list->data)return 1;
    else return CroisRec(list->next);
}

void croissante(int i)
{
    if(i==0)printf("\nRecursif : La liste est croissante\n");
    else printf("\nRecursif : La liste est pas croissante\n");
}

int main()
{
    /*Element* list, *list_, *list__;
    list = malloc(sizeof(Element));
    list_ = malloc(sizeof(Element));
    list__= malloc(sizeof(Element));
    list->data = 1;
    list->next = list_;
    list_->data = 2;
    list_->next = list__;
    list__->data = 8;
    list__->next = NULL;
    Element* liste;
    liste = create_list(10);
    printf("Longueur de la liste : %d\n", longueur(liste));
    affichage(liste);
    printf("\nPosition du chiffre 7 dans la liste : %d\n", position(liste, 11));
    printf("Affichage un sur deux en iteratif :\n");
    un_sur_deux(liste);
    printf("\nAffichage un sur deux en recu :\n");
    un_sur_deux_recu(liste);
    check_croissance(liste);
    croissante(CroisRec(liste));*/ //juste des tests

    int n;
    printf("Donne un entier positif :\n>>");
    scanf("%d", &n);
    Element* my_list = create_list(n);
    Element* my_list2 = create_recu(n, 1);
    Element* list_fibo = Fibo(n);
    Element* list_fibo2 = Fibo_recu(n);


    printf("\nTout le bordel mais pour la liste normale en iteratif et recursif :\n\n");


    printf("Longueur de la liste : %d\n", longueur(my_list));
    printf("Longueur en recursif : %d\n", long_recu(my_list2));
    printf("Position du chiffre 9 dans la liste : %d\n", position(my_list, 9));
    printf("Position en recursif de 4 : %d\n", pos_recu(my_list2, 4));
    printf("Nombre d'ocurrence du chiffre 5 : %d\n", ocu(my_list, 5));
    printf("Occurrence en recursif du chiffre 2 : %d\n", ocu_recu(my_list2, 2));
    printf("Affichage un sur deux :\n");
    un_sur_deux(my_list);
    printf("\nAffichage un sur deux en recursif :\n");
    un_sur_deux_recu(my_list2);
    check_croissance(my_list);
    croissante(CroisRec(my_list2));
    printf("Affichage de la liste creee en iteratif :\n");
    affichage(my_list);
    printf("\nAffichage de la liste creee en recursif :\n");
    affichage(my_list2);


    printf("\n\nTout le bordel mais pour les listes fibo en iteratif puis recursif :\n\n");


    printf("Longueur de la liste : %d\n", longueur(list_fibo));
    printf("Longueur en recursif : %d\n", long_recu(list_fibo2));
    printf("Position du chiffre 9 dans la liste : %d\n", position(list_fibo, 9));
    printf("Position en recursif de 4 : %d\n", pos_recu(list_fibo2, 4));
    printf("Nombre d'ocurrence du chiffre 5 : %d\n", ocu(list_fibo, 5));
    printf("Occurrence en recursif du chiffre 2 : %d\n", ocu_recu(list_fibo2, 2));
    printf("Affichage un sur deux :\n");
    un_sur_deux(list_fibo);
    printf("\nAffichage un sur deux en recursif :\n");
    un_sur_deux_recu(list_fibo2);
    check_croissance(list_fibo);
    croissante(CroisRec(list_fibo2));
    printf("Affichage de la liste creee en iteratif :\n");
    affichage(list_fibo);
    printf("\nAffichage de la liste creee en recursif :\n");
    affichage(list_fibo2);

    //ça devient lent à partir de n >= 40




    return 0;
}
