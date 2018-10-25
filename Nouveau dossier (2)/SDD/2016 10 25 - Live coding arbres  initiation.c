/* (c) Pepper Labs 2016-17 */

#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1

// structure de noeud d'arbre binaire
typedef struct node {
	int info;
	struct node *sag, *sad;
} node;

typedef node *tree;


/* retourne un arbre singleton initialisé avec la valeur info */
tree new_node(int info) {
	if (DEBUG) printf("new_node(%d)\n", info);
	tree t = malloc(sizeof(node));
	t->info = info;
	t->sag = t->sad = NULL;
	return t;
}

/* crée un arbre parfait de hauteur n, et dont le noeud racine comporte la valeur seed */
tree new_perfect_tree(unsigned n, unsigned seed) {
	if (!n) return NULL;
	tree t = new_node(seed);
	t->sag = new_perfect_tree(n - 1, seed * 2);
	t->sad = new_perfect_tree(n - 1, seed * 2 + 1);
	return t;
}

/* affiche un nombre de caractères blancs proportionnel à n*/
void indent(int n) { while (n--) putchar(' '); }

/* affiche t */
void print_tree(tree t, unsigned depth) {
	if (!t) return;
	indent(depth);
	printf("%d\n", t->info);
	print_tree(t->sag, depth + 1);
	print_tree(t->sad, depth + 1);
} 

/* retourne le nombre d'éléments de t */
unsigned nr_elts(tree t) { return t ? 1 + nr_elts(t->sag) + nr_elts(t->sad) : 0; }

unsigned max(unsigned a, unsigned b) { return a < b ? b : a; }

unsigned h(tree t) {
	if (!t) return 0;
	return 1 + max(h(t->sag), h(t->sad));
}

int main() {
	int n;
	printf("Saisir une profondeur > ");
	scanf("%d", &n);
	printf("l'arbre :\n");
	tree t;
	print_tree(t = new_perfect_tree(n, 1), 0);
	printf("comporte %u elements\n", nr_elts(t));
	printf("est de haiuteur %u\n", h(t));
	
	char c;
	printf("Continuer (o / n) ? > ");
	scanf(" %c", &c);
	if (c == 'o') main();

	return 0;
}












