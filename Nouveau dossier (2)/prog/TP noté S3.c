#include <stdio.h>
#include <stdlib.h>

// Anthony Quach L2-R 2022


// Déclarations de base
typedef struct list_node
{
    int info; //données
    struct list_node* succ; // pointeur vers le maillon suivant
} list_node;

typedef list_node* list; // synonyme de list_node*


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


// Suppression d'une liste
void free_list(list *pl)
{
    if (!*pl) return;
    free_list(&((*pl)->succ));
    free(*pl);
}

// on crée une liste avec des éléments allant de 1 à n pour faire un exemple différent
list create_liste(unsigned nb)
{
    list liste_cree;
    list temp = NULL; //pointera sur la tête de la liste
    while (nb > 0) // on commence la création par la queue de la liste
    {
        liste_cree = new_list_node(nb);
        liste_cree->succ = temp;
        temp = liste_cree;
        nb--;
    }
    return (temp);
}

// renvoie la somme des élément pairs, version itérative
int list_even_sum(list l)
{
    if (!l) return 0; // cas où la liste est vide
    list temp = l; // pointeur utilisé pour parcourir la liste
    int somme = 0;
    while (temp)
    {
        if (temp->info % 2 == 0) somme += temp->info;
        temp = temp->succ;
    }
    return somme;
}

//renvoie la somme des éléments pairs, version récursive
int list_even_sum_recu(list l)
{
    if (!l) return 0;
    list temp = l;
    if (temp->info % 2 == 0) return (temp->info + list_even_sum_recu(temp->succ));
    else return list_even_sum_recu(temp->succ);
}


int main()
{
    list liste_1 = new_syrac_list(2);
    list liste_2 = NULL;
    list liste_3 = create_liste(10); // on veut tester avec 10 éléments

    // on teste avec la suite de Syracuse de terme initial s = 2 en version récursive
    printf("Test avec la suite de Syracuse :\n");
    print_list(liste_1);
    printf("Somme des %cl%cments pairs : %d\n\n",130, 130, list_even_sum_recu(liste_1));
    free_list(&liste_1); // on libére l'espace alloué dans la mémoire et supprime la liste
    liste_1 = NULL; // on corrige le pointeur, il doit pointer sur NULL puisque la liste est supprimée, elle est vide

    // on teste la cas où la liste est vide
    printf("Test avec une liste vide :\n");
    print_list(liste_2);
    printf("Somme des %cl%cments pairs : %d\n\n",130, 130, list_even_sum(liste_2));
    // inutile de supprimer la liste, elle est déjà vide

    // on teste avec une liste qui a 10 éléments en version itérative
    printf("Test avec une liste allant de 1 %c 10 :\n", 133);
    print_list(liste_3);
    printf("Somme des %cl%cments pairs : %d\n", 130, 130, list_even_sum(liste_3));
    free_list(&liste_3); // on passe en argument un double pointeur pour modifier la valeur de référence du premier pointeur
    liste_3 = NULL;

    return 0;
}
