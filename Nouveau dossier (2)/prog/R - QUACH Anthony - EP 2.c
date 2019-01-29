#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0

// Anthony Quach L2-R 2022 EP2

/* Déclarations */

/* structure de noeud d'Arbre Binaire */
typedef struct tree_node
{
    int info;                // champ de stockage d'information
    struct tree_node *left, *right;        // pointeur sur les fils (éventuels)
} node;

/* synonyme de pointeur sur noeud = arbre en tant représenté par son noeud racine */
typedef node *tree;

/* creation et initialisation d'un simple noeud (= un arbre singleton) */
tree new_node(int e)
{
    if (DEBUG)
        printf("new_node(%d)\n", e);
    tree t = malloc(sizeof(node));
    t->info = e;
    t->left = t->right = NULL;
    return t;
}

/* création d'un arbre parfait de hauteur n, de racine e */
tree new_perfect_tree(int n, int e)
{
    if (n <= 0)
        return NULL;
    tree t = new_node(e);
    t->left = new_perfect_tree(n - 1, 2 * e);
    t->right = new_perfect_tree(n - 1, 2 * e + 1);
    return t;
}

/* création d'un arbre équilibré partant d'un tableau de taille n
  a est le tableau complet, start et end les index de début et de fin du sous-tableau local */
tree new_balanced_tree_from_array(int *a, int start, int end)
{
    if (start > end)
        return NULL; // cas terminal
    int med = (start + end) / 2; // calcul de l'index médian qui devient racine
    node *t = new_node(a[med]);
    t->left = new_balanced_tree_from_array(a, start, med - 1);
    t->right = new_balanced_tree_from_array(a, med + 1, end);
    return t;
}

/* affiche n fois le caractère c */
void print_n(char c, int n)
{
    while (n--)
        putchar(c);
}

/* affiche un arbre */
void _print_tree(tree t, int p)
{
    print_n('.', 2 * p);
    if (!t)
        printf("x\n");
    else
    {
        printf("%d\n", t->info);
        if (t->left || t->right)
        {
            _print_tree(t->left, p + 1);
            _print_tree(t->right, p + 1);
        }
    }
}
void print_tree(char *label, tree t)
{
    if (label)
        printf("%s :\n", label);
    _print_tree(t, 0);
}

// Fonction récursive qui retourne le minimum d’un AB t, -1 si l'arbre est vide.
int tree_min(tree t)
{
    if (!t) // cas où l'arbre est vide
    {
        return -1;
    }
    int a = t->info; // minimum qu'on teste
    int b = t->info; // minimum actuel
    if (t->left)
    {
        a = tree_min(t->left); // parcours vers la gauche
    }
    if (t->right)
    {
        b = tree_min(t->right); // parcours vers la droite
    }
    if (t->info <= a && t->info <= b) // on compare les deux variables avec l'info courante
    {
        return t->info;
    }
    if (t->info >= a && a <= b) // on compare le min a avec l'info courante puis b
    {
        return a;
    }
    if (t->info >= b && b <= a) // on compare le min b avec l'info courante puis a
    {
        return b;
    }
}

// Fonction récursive qui retourne le minimum d’un ABR t, -1 si l'arbre est vide.
int bst_min(tree t)
{
    if (t) // arbre non vide
    {
        int a; // min à renvoyer
        if (t->left)  // on sait que le minimum se situe à gauche de l'ABR, pas besoin de comparer, ici on reprend le même principe
        {
            a = bst_min(t->left);
        }
        else // pas de gauche on stocke l'info courante
        {
            a = t->info;
        }
        if (a < t->info) // on compare l'info courante avec le a
        {
            return a;
        }
        return (t->info);
    }
    return -1; //cas où l'arbre est vide
}


int main()
{
    printf("3 tests :\n\n");
    tree simple = new_node(8); // premier test simple
    print_tree("Affichage de l'arbre simple ", simple); // on affiche l'arbre
    printf("\nMinimum de l'arbre simple : %d", tree_min(simple)); // test min AB
    printf("\nMinimum de l'ABR : %d", bst_min(simple)); // test min ABR

    tree parfait = new_perfect_tree(5, 7); // deuxième test
    print_tree("\nAffichage de l'arbre parfait ", parfait); // on affiche l'arbre
    printf("\nMinimum de l'arbre parfait : %d", tree_min(parfait)); // test min AB
    printf("\nMinimum de l'ABR : %d", bst_min(parfait)); // test min ABR

    tree arbre = new_perfect_tree(1, 1); // troisième test
    print_tree("\n\nAffichage du second arbre parfait", arbre); // on affiche l'arbre
    printf("\nMinimum du second arbre parfait : %d", tree_min(arbre)); // test min AB
    printf("\nMinimum de l'ABR : %d", bst_min(arbre)); // test min ABR

    return 0;
}

