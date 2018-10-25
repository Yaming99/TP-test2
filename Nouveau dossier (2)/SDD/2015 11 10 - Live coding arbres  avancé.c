/**
 * (c) Platypus SAS 2015-2016
 *     Release version - v1
 *     Author - Franck Lepoivre
 *     Release date - 2015/11/10
 */

#include <stdlib.h>
#include <stdio.h>

#define DEBUG 0

typedef struct tree_node {
	int data;
	struct tree_node *left, *right;
} tree_node;

typedef tree_node *tree;

// crée et initialise un noeud d'AB (constructeur)
tree new_tree_node(int data) {
	tree t = malloc(sizeof(tree_node));
	t->data = data;
	t->left = t->right = NULL;
	return t;
}

// crée un arbre parfait de hauteur n dont les valeurs sont les index
// des noeuds suivant un parcours en largeur
tree new_perfect_tree(int n, int e) {
	tree t = new_tree_node(e);
	if (n > 1) {
		t->left = new_perfect_tree(n - 1, 2 * e);
		t->right = new_perfect_tree(n - 1, 2 * e + 1);
	}
	return t;
}

// affiche le contenu d'un arbre sous forme d'une expression parenthésée (ordre infixe) :
// (parent_data, l : left_child_expression, r : right_child_expression)
void print_tree(tree t) {
	if (!t) printf(".");
	else {
		if (!(t->left || t->right)) printf("%d", t->data);
		else {
			printf("(%d, l:", t->data);
			print_tree(t->left);
			printf(", r:");
			print_tree(t->right);
			printf(")");
		}
	}
}

// affiche le contenu d'un arbre sous forme d'une arborescence de type explorateur (préordre)
void indent(int depth) {
	if (!depth) return;
	if (depth--) printf("!-");
	while (depth--) printf("--");
}
void print_tree_v2(tree t, int depth) {
	indent(depth); // ajoute autant de blanc préfixe que la profondeur du noeud concerné
	if (!t) printf(".\n");
	else {
		printf("%d\n", t->data);
		if (t->left || t->right) {		
			print_tree_v2(t->left, depth + 1);
			print_tree_v2(t->right, depth + 1);
		}
	}
}

// affichage précédent complété d'un label préfixe
void print_tree_with_label(char *label, tree t) {
	if (label) printf("%s : \n", label);
	print_tree_v2(t, 0);
	printf("\n");
}

// retourne le nombre d'éléments d'un AB
unsigned nr_elts(tree t) { return t ? 1 + nr_elts(t->left) + nr_elts(t->right) : 0; }

// retourne la hauteur d'un AB
unsigned height(tree t) {
	if (!t) return 0;
	unsigned hl = height(t->left), hr = height(t->right);
	return (hl > hr ? hl : hr) + 1;
}

// recherche un élément dans un ABR : version itérative
int bst_search(tree t, int e) {
	while (t) {
		if (t->data == e) return 1;
		t = e < t->data ? t->left : t->right;
	}
	return 0;
}

// recherche un élément dans un ABR : version récursive
int bst_search_v2(tree t, int e) {
	if (!t) return 0;
	if (t->data == e) return 1;
	return bst_search_v2(e < t->data ? t->left : t->right, e);
}

// ajoute un élément dans un ABR : version itérative
void bst_add(tree *pt, int e) {
	if (!*pt) *pt = new_tree_node(e);
	else {
		tree u = *pt, p;
		while (u) {
			p = u;
			u = e < u->data ? u->left : u->right;
		}
		u = new_tree_node(e);
		if (e < p->data) p->left = u;
 		else p->right = u;
	}
}

// ajoute un élément dans un ABR : version récursive
void bst_add_v2(tree *pt, int e) {
	if (!*pt) *pt = new_tree_node(e);
	else {
		tree t = *pt;
		if (e < t->data) bst_add_v2(&(t->left), e);
		else bst_add_v2(&(t->right), e);
	}
}

// point d'arret de la séance du 10/11 et de reprise de celle du 17/11

// ok 0) tester le bon fonctionnement des fonctions de la dernière fois

// 1) suppression dans un ABR

// a) retourne l'adresse du parent du max du SAG (d'un ABR) si le max n'est pas la racine, NULL sinon
/*tree max_of_bst(tree t) {
	if (!t) return NULL;
	while (t->right) t = t->right;
	return t;
}*/
tree parent_of_max(tree t) {
	if (!(t->right)) return NULL;
	while (t->right->right) t = t->right;
	return t;
}

// transpose les valeurs des noeuds a et b
void swap(tree a, tree b) {
	int c = a->data;
	a->data = b->data;
	b->data = c;
}

// supprime le noeud donné en référence et met à jour cette référence
void bst_suppr(tree *pt) {
	if (DEBUG) printf("bst_suppr(%d)\n", (*pt)->data);
	tree t = *pt;
	// 1. cas trivial où le noeud est une feuille
	if (!(t->left || t->right)) {
		// on libère le noeud et on réinitialise sa référence
		if (DEBUG) printf("leaf case !\n");
		free(t);
		*pt = NULL;
	}
	// 2. cas facile où le noeud n'a qu'un enfant
	else if (!(t->left && t->right)) {
		// on libère le noeud et on modifie sa référence pour celle de son enfant
		if (DEBUG) printf("single child case !\n");
		tree l = t->left ? t->left : t->right;
		free(t);
		*pt = l;
	}
	// 3. cas difficile où le noeud a deux enfants
	// rappelons que SAG et SAD son nécessairement non nuls
	else {
		if (DEBUG) printf("hard two children case !\n");
		// on récupère la référence du max du SAG du noeud (enfin, celle de son parent)..
		// notons que max est nécessairement le fils droit de son parent, sauf s'il est fils direct du noeud à supprimer
		tree max_parent = parent_of_max(t->left);
		tree max = max_parent ? max_parent->right : t->left;
		// on permute la valeur du max avec celle du noeud à supprimer (préservation de la propriété d'ABR)
		swap(max, t);
		// puis on supprime le noeud max et on met à jour la référence portée par son parent
		bst_suppr(max_parent ? &(max_parent->right) : &(t->left));
	}
}

// supprime l'élément de valeur e d'un BST si un tel élément existe
void bst_remove(tree *pt, int e) {
	// on recherche le noeud à supprimer (s'il existe)
	if (DEBUG) printf("bst_remove(%d, %d)\n", (*pt)->data, e);
	tree t = *pt, p = NULL; // p est le parent du noeud t courant
	while (t) {
		if (DEBUG) printf("traversing %d\n", t->data);
		if (t->data == e) {
			if (!p) bst_suppr(pt); // cas où on supprime la racine
			else bst_suppr(t == p->right ? &(p->right) : &(p->left)); // cas général
		}
		// itération dans l'arbre
		p = t;
		t = e < t->data ? t->left : t->right;
	}
}


// 2) AVL
//   a) structure de données

typedef struct AVL_tree_node {
	int data;
	struct AVL_tree_node *left, *right;
	int balance;
} AVL_tree_node;

typedef AVL_tree_node *AVL_tree;

AVL_tree new_AVL_tree_node(int data) {
	AVL_tree t = malloc(sizeof(AVL_tree_node));
	t->data = data;
	t->left = t->right = NULL;
	t->balance = 0;
	return t;
}

int AVL_height(AVL_tree t) {
	if (!t) return 0;
	int hl = AVL_height(t->left), hr = AVL_height(t->right);
	return (hl > hr ? hl : hr) + 1;
}

int _abs(int a) { return a < 0 ? -a : a; }
int AVL_add(AVL_tree *pt, int e) {
	if (!*pt) {
		*pt = new_AVL_tree_node(e);
		return 1;
	} else {
		AVL_tree t = *pt;
		// réévaluer les balances sur la branche parente du noeud ajouté
		// si la hauteur du sous arbre dans lequel s'est effectué l'ajout
		// a augmenté, on met à jour la balance et on propage cette augmentation
		// vers le parent, sauf si un rééquilibrage est effectué
		// on ne retourne donc que la variation de hauteur par rapport à l'état précédent
		// si la balance se rapproche de 0, c'est que la hauteur est stable
		// (le sous arbre le moins haut s'est allongé)
		// si elle s'en éloigne en revanche, c'est que la hauteur a augmenté de 1
		// (le sous arbre le plus haut s'est allongé)
		int old_balance = t->balance;
		t->balance += e < t->data ?  -AVL_add(&(t->left), e) : AVL_add(&(t->right), e);

		if (DEBUG) printf("balance of %d : %d => %d\n", t->data, old_balance, t->balance);

		if (_abs(t->balance) <= _abs(old_balance)) return 0;
		else if (_abs(t->balance) > 1) {
			printf("ROTATION on %d!!\n", t->data);
			// l'effet de la rotation est de réduire la hauteur de 1 et idem avec la balance
			// pour la suite (réalisation des 4 rotations), à vous de jouer !
			return 0;
		} else return 1;
		/*
		OLD IDIOT
		if (e < t->data) AVL_add(&(t->left), e);
		else AVL_add(&(t->right), e);
		t->balance = AVL_height(t->right) - AVL_height(t->left);
		if (t->balance < -1 || t->balance > 1) {
			printf("ROTATION on %d!!\n", t->data);
		}*/
	}
}

void print_AVL_tree(AVL_tree t, int depth) {
	indent(depth); // ajoute autant de blanc préfixe que la profondeur du noeud concerné
	if (!t) printf(".\n");
	else {
		printf("%d (%d)\n", t->data, t->balance);
		if (t->left || t->right) {		
			print_AVL_tree(t->left, depth + 1);
			print_AVL_tree(t->right, depth + 1);
		}
	}
}



void print_AVL_tree_with_label(char *label, AVL_tree t) {
	if (label) printf("%s :\n", label);
	print_AVL_tree(t, 0);
	printf("\n");
}


//   b) les 4 rotations
//   c) ajout et retrait ABR avec réévaluation des balances et déclenchement des rotations
//   d) tests : reproduire les cas du cours
// 3) ARN
//   a) structure de données
//   b) les 2 rotations
//   c) ajout et retrait ABR avec réévaluation des propriété ARN et déclenchement des rotations
// 4) Tas binomiaux et tas de Fibonacci

int main(int argc, char *argv[]) {
	int depth = argc > 1 ? atoi(argv[1]) : 5;
	tree t = new_perfect_tree(depth, 1);
	printf("perfect tree of height % d", depth);
	print_tree_with_label("", t);
	printf("nr_elts : %d\n", nr_elts(t));
	printf("height : %d\n", height(t));

	printf("\n>>> BST add sequence (with iterative version of add) :\n\n");

	tree u = NULL;
	print_tree_with_label("empty tree", u);
	// ajout de la séquence 8, 9, 10, 1, 2, 5, 0
	bst_add(&u, 8);
	print_tree_with_label("add 8", u);
	bst_add(&u, 9);
	print_tree_with_label("add 9", u);
	bst_add(&u, 10);
	print_tree_with_label("add 10", u);
	bst_add(&u, 1);
	print_tree_with_label("add 1", u);
	bst_add(&u, 2);
	print_tree_with_label("add 2", u);
	bst_add(&u, 5);
	print_tree_with_label("add 5", u);
	bst_add(&u, 0);
	print_tree_with_label("add 0", u);

	printf("\n>>> BST add sequence (with recursive version of add) :\n");
	tree v = NULL;
	print_tree_with_label("empty tree : ", v);
	// ajout de la séquence 8, 9, 10, 1, 2, 5, 0
	bst_add_v2(&v, 8);
	print_tree_with_label("add 8", v);
	bst_add_v2(&v, 9);
	print_tree_with_label("add 9", v);
	bst_add_v2(&v, 10);
	print_tree_with_label("add 10", v);
	bst_add_v2(&v, 1);
	print_tree_with_label("add 1", v);
	bst_add_v2(&v, 2);
	print_tree_with_label("add 2", v);
	bst_add_v2(&v, 5);
	print_tree_with_label("add 5", v);
	bst_add_v2(&v, 0);
	print_tree_with_label("add 0", v);

	bst_remove(&v, 5);
	print_tree_with_label("remove 5 (leaf : easy case)", v);
	bst_remove(&v, 9);
	print_tree_with_label("remove 9 (one child : middle case)", v);
	bst_remove(&v, 1);
	print_tree_with_label("remove 1 (two children : hard case)", v);
	bst_remove(&v, 8);
	print_tree_with_label("remove 1 (two children & root : finally not so hard case)", v);
	bst_remove(&v, 2);
	print_tree_with_label("finish it => remove 2", v);
	bst_remove(&v, 10);
	print_tree_with_label("finish it => remove 10", v);
	bst_remove(&v, 0);
	print_tree_with_label("finish it => remove 0", v);

	printf("\n>>> AVL add sequence (with iterative version of add) :\n\n");
	AVL_tree w = NULL;
	print_AVL_tree_with_label("empty tree : ", w);
	// ajout de la séquence 8, 9, 10, 1, 2, 5, 0
	AVL_add(&w, 8);
	print_AVL_tree_with_label("add 8", w);
	AVL_add(&w, 9);
	print_AVL_tree_with_label("add 9", w);
	AVL_add(&w, 10);
	print_AVL_tree_with_label("add 10", w);
	AVL_add(&w, 1);
	print_AVL_tree_with_label("add 1", w);
	AVL_add(&w, 2);
	print_AVL_tree_with_label("add 2", w);
	AVL_add(&w, 5);
	print_AVL_tree_with_label("add 5", w);
	AVL_add(&w, 0);
	print_AVL_tree_with_label("add 0", w);
	AVL_add(&w, 6);
	print_AVL_tree_with_label("add 6", w);

	return 0;
}






