/* Helpers */

#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0

/* Déclarations */

/* structure de noeud d'AB */
typedef struct tree_node
{
    int info;                // champ de stockage d'information
    struct tree_node *left, *right;        // pointeur sur les fils (éventuels)
} node;

/* pointeur sur noeud = arbre en tant représenté par son noeud racine */
typedef node *tree;


void tree_reverse(tree t)
{
    int tmp;
    if (t->left && t->right)
    {
        tmp = t->left->info;
        t->left->info = t->right->info;
        t->right->info = tmp;
        tree_reverse(t->left);
        tree_reverse(t->right);
    }
}

/* creation et initialisation d'un simple noeud (= un arbre singleton) */
tree new_node(int e)
{
    if (DEBUG) printf("new_node(%d)\n", e);
    tree t = malloc(sizeof(node));
    t->info = e;
    t->left = t->right = NULL;
    return t;
}


void bst_add(tree* pt, int e)
{
    if (*pt == NULL)
    {
        *pt = new_node(e);
    }
    else if ((*pt)->info > e)
    {
        bst_add(&(*pt)->left, e);
    }
    else
    {
        bst_add(&(*pt)->right, e);
    }
}

/*

// retourne la somme des feuilles d’un AB t non vide, -1 si l'arbre est vide.
int tree_leaves_sum(tree t)
{

}

// qui affiche l'ensemble des valeurs d'un ABR t strictement supérieures à un élément e donné
void bst_sup(tree t, int e)
{
    if(!t)
    {
        return;
    }

}
*/


/* création d'un arbre parfait de hauteur n, de racine e */
tree new_perfect_tree(int n, int e)
{
    if (n <= 0) return NULL;
    tree t = new_node(e);
    t->left = new_perfect_tree(n - 1, 2 * e);
    t->right = new_perfect_tree(n - 1, 2 * e + 1);
    return t;
}

/* création d'un arbre équilibré partant d'un tableau de taille n
  a est le tableau complet, start et end les index de début et de fin du sous-tableau local */
tree new_balanced_tree_from_array(int *a, int start, int end)
{
    if (start > end) return NULL; // cas terminal
    int med = (start + end) / 2; // calcul de l'index médian qui devient racine
    node *t = new_node(a[med]);
    t->left = new_balanced_tree_from_array(a, start, med - 1);
    t->right = new_balanced_tree_from_array(a, med + 1, end);
    return t;
}

/* affiche n fois le caractère c */
void print_n(char c, int n)
{
    while (n--) putchar(c);
}

/* affiche un arbre */
void _print_tree(tree t, int p)
{
    print_n('.', 2 * p);
    if (!t) printf("x\n");
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
    if (label) printf("%s :\n", label);
    _print_tree(t, 0);
}


int main()
{
    printf("Hello world!\n");
    return 0;
}
