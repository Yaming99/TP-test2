#include <stdlib.h>
#include <stdio.h>

// Déclarations de base

typedef struct list_node
{
    int info; // données
    struct list_node *succ; // pointeur vers le maillon suivant
} list_node;

typedef list_node *list;


// création d'un noeud solitaire initialisé avec la valeur info
list new_list_node(int info)
{
    list l = malloc(sizeof(list_node));
    l->info = info;
    l->succ = NULL;
    return l;
}

// affichage la liste l
void print_list(list l)
{
    if (!l) printf("->x\n");
    else
    {
        printf("->(%d)", l->info);
        print_list(l->succ);
    }
}


// retourne la suite de Syracuse de terme initial s
list new_syrac_list(unsigned s)
{
    if (!s) return NULL;
    list l = malloc(sizeof(list_node));
    l->info = s;
    if (s == 1) l->succ = NULL;
    else l->succ = new_syrac_list(s % 2 ? 3 * s + 1 : s / 2);
    return l;
}

void free_list(list *pl)
{
    if (!*pl) return;
    free_list(&((*pl)->succ));
    free(*pl);
}

int liste_prod(list l)
{
    if(!l)
    {
        return 1;
    }
    else
    {
        return (l->info) * liste_prod(l->succ);
    }
}

int main()
{
    unsigned s = 0;
    unsigned s2 = 2;
    unsigned s3 = 3;

    list l = new_syrac_list(s);
    print_list(l);
    printf("la multiplication des maillons a pour resultat: %d\n",liste_prod(l));
    free_list(&l);


    list l2 = new_syrac_list(s2);
    print_list(l2);
    printf("la multiplication des maillons a pour resultat: %d\n",liste_prod(l2));
    free_list(&l2);


    list l3 = new_syrac_list(s3);
    print_list(l3);
    printf("la multiplication des maillons a pour resultat: %d\n",liste_prod(l3));
    free_list(&l3);

    return 0;
}
