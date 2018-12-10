#include <stdio.h>
#include <stdlib.h>

typedef struct  tree_node {

	int     info;
	struct  tree_node *left;
	struct  tree_node *right;

}			    node;

node *create(node *t)
{
    t = malloc(sizeof(node));
    t->left = t->right = NULL;
    return t;
}

void print_n(char c, int n){ while(n--) putchar(c); }

void _print_tree(node *tree, int n)
{
    print_n('.',(2*n));
    if (!tree) printf("x\n");
    else
        printf("%d\n", tree->info);
        if (tree->left || tree->right)
        {
            _print_tree(tree->left, n+1);
            _print_tree(tree->right, n+1);
        }
}

void print(char *title, node *t)
{
    if(title) printf("%s: \n", title);
    _print_tree(t,0);
}

node *prefect_tree( int n,int var)
{
    if (n<=0) return NULL;
    else{
            node *a = malloc(sizeof(node));
            a->info = var;
            a->left = prefect_tree(n-1,(2*var));
            a->right = prefect_tree(n-1,(2*var+1));
    }
}

int len_feuille(node *t)
{
    if(!t) return 0;
    if (!(t->left || t->right)) return 1;;
    return (len_feuille(t->left)+len_feuille(t->right));
}

int len_pdouble(node *t)
{
    if(!t) return 0;
    if (t->left && t->right) return (1 + len_pdouble(t->left)+len_pdouble(t->right));
    return (len_pdouble(t->left)+len_pdouble(t->right));
}

int len_mono(node *t)
{
    if(!t) return 0;
    if ((t->left && !t->right) || (!t->left && t->right))return (1 + len_mono(t->left)+len_mono(t->right));
    return (len_mono(t->left)+len_mono(t->right));
}

/*void sym(node *t)
{
    int tmp;
    if(!(t->left && t->right)) return;
    t->left->info
}*/




int main(){
    node *t = prefect_tree(3,1);
    print("arbre a",t);
    printf("%d\n",len_feuille(t));
    printf("%d\n",len_pdouble(t));
    printf("%d\n",len_mono(t));
    return (0);
}
