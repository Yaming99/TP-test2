/**
 * (c) Pepper Labs 2016-17
 * Séance live coding amphi EFREI 2A SDD du 19/10/2016
 */



#include <stdlib.h> // pour le malloc, srand, rand
#include <stdio.h> // pour printf et scanf
#include <time.h> // pour time

#define DEBUG 0

// 1. définir la structure de liste
typedef struct node {
	int info;
	struct node *succ;
} node;

typedef node *list;

// structure pour une liste doublement chaînée
typedef struct d_node {
	int info;
	struct d_node *prec, *succ;
} d_node;

typedef d_node *d_list;



// 2. se donner une fonction d'affichage
/*
Afficher(l : liste)
Donnée : la liste l à afficher
début
	tant que l =/= vide faire
		afficher '->(' + l->info + ')' 
		l <- l->succ
	fin
	afficher '->x'
fin
*/
void print_list(char *label, list l) {
	if (label) printf("%s : ", label);
	while (l != NULL) {
		printf("->(%d)", l->info);
		l = l->succ;
	}
	printf("->x");
} 
// la même pour une doublement chaînée
void print_d_list(char *label, d_list l) {
	if (label) printf("%s : ", label);
	while (l != NULL) {
		printf("<->(%d)", l->info);
		l = l->succ;
	}
	printf("<->x");
} 



void print_list_rec(list l) {
	if (!l) printf("->x");
	else {
		printf("->(%d)", l->info);
		print_list_rec(l->succ);
	}
}


// 3. se donner une fonction de création de liste de test
/*
Creation_1_n(n : entier) : liste
Donnée : n, le nombre d'éléments de la liste à créer
Variables locales : l, la référence de la tête de la liste à créer
                    q, la référence de la queue de liste
                    i, compteur de boucle
Retourne : la liste créée
début
	si n = 0 alors retourner vide
	l <- réserver Maillon
	l->info <- 1
	q <- l
	i <- 1
	tant que i < n faire
		i <- i + 1
		q <- q->succ <- réserver Maillon
		q->info <- i
	fin
	q->succ <- vide
	retourner l
fin
*/

list create_1_n(int n) {
	if (!n) return NULL;
	list l = malloc(sizeof(node));
	l->info = 1;
	list q = l;
	int i = 1;
	while (i < n) {
		i++;
		q = q->succ = malloc(sizeof(node));
		q->info = i;
	}
	q->succ = NULL;
	return l;
}

// création de la liste décroissante à n éléments en récursif
list create_n_1(int n) {
	if (n == 0) return NULL;
	list l = malloc(sizeof(node));
	l->info = n;
	l->succ = create_n_1(n - 1);
	return l;
}

// retourner la sommes des éléments de la liste m
int sum_iter(list l) {
	int s = 0;
	while (l) {
		s += l->info;
		l = l->succ;
	}
	return s;
}

int sum_rec(list l) {
	if (!l) return 0;
	return l->info + sum_rec(l->succ);
}

int sum_rec_v2(list l) { return l ? l->info + sum_rec(l->succ) : 0; }

// retourne la référence (adresse) de la queue de l ou vide si l est vide
list tail_iter(list l) {
	if (!l) return NULL;
	while (l->succ) l = l->succ;
	return l;
}

list tail_rec(list l) {
	if (!l) return NULL;
	if (!(l->succ)) return l;
	return tail_rec(l->succ);
}

// supression de liste
/*
Suppr_iteratif(l : liste)
Donnée modifiée : l, la liste à supprimer
Variable locale : kill, le prochain maillon à supprimer
début
	tant que l non vide faire
		kill <- l
		l <- l->succ
		libérer kill
	fin
	// superflu : l <- vide
fin
*/

void suppr_iter(list *pl) {
	list kill;
	while (*pl) {
		kill = *pl;
		*pl = (*pl)->succ;
		free (kill);
	}
	// superflu : *pl = NULL;
}

/*
Suppr_récursif(l : liste)
Donnée modifiée : l, la liste à supprimer
début
	si l non vide alors
		Suppr_récursif(l->succ)
		liberer l
		l <- vide // ici ce n'est pas surperflu et même indispensable !
	fin(si)
fin
*/

// FIXED !
void suppr_rec(list *pl) {
	if (*pl) {
		//if (DEBUG) printf("suppr (%d) with succ = %p \n", (*pl)->info, (*pl)->succ);
		suppr_rec(&((*pl)->succ));
		free (*pl);
		*pl = NULL; // LE BUG était l'oubli essentiel de remise à NULL du pointeur *pl
		// => Le segfault n'était donc pas ici mais sur l'appel suivant
		// dans le main, à la fonction d'affichage, qui tentait
		// d'afficher le contenu d'une liste vide, mais dont le pointeur n'était pas null
	} // else if (DEBUG) printf("Last call with *pl = NULL\n");
}

/*

Exercice 1 - Dernière position d’un élément
int last_pos_of(list l, int x)​, itérative, qui retourne la position
de la dernière occurrence de​ la valeur ​x​ dans la liste (LSC) ​l,
​ou 0 si ​x n'est pas élément de ​l.

Exercice 2 - Suppression récursive d’occurrences
void suppr_occs(list *pl, int x)​ qui supprime toutes les occurrences
de l’élément x dans la liste ​*pl.

*/

/*
Exo 1 Derniere_Position(l : liste, x : T)
Données : l, la liste, et x, l'élément dont on cherche la dernière position
Variables locales : p, position courante, pos de la dernière occurrence de x
début
	p <- pos <- 0
	tant que l non vide faire
		p <- p + 1
		si l->info = x alors pos <- p
		l <- l->succ
	fin
	retourner pos
fin
*/

int last_pos_of(list l, int x) {
	int p = 0, pos = 0;
	while (l) {
		p++;
		if (l->info == x) pos = p;
		l = l->succ;
	}
	return pos;
} 

void suppr_occs(list *pl, int x) {
	if (!*pl) return;
	suppr_occs(&((*pl)->succ), x);
	if ((*pl)->info == x) {
		list succ = (*pl)->succ;
		free (*pl);
		*pl = succ;
	}
}

// pour tester les deux fonctions précédentes, on s'offre en bonus
// une fonction qui créée une liste de taille n à valeurs aléatoires
// comprises entre 1 et m fixé (> 1)
list creat_alea_list(int n, int m) {
	list l, nouv;
	if (n == 0) return NULL;
	nouv = l = malloc(sizeof(node));
	l->info = 1 + (rand() % m);
	while (n-- > 1) {
		nouv = nouv->succ = malloc(sizeof(node));
		nouv->info = 1 + (rand() % m);
	}
	nouv->succ = NULL;
	return l;
}

// la même en version doublement chaînée
d_list creat_alea_d_list(int n, int m) {
	if (DEBUG) printf("creat_alea_d_list(%d, %d)\n", n, m);
	d_list l, nouv;
	if (n == 0) return NULL;
	nouv = l = malloc(sizeof(d_node));
	l->info = 1 + (rand() % m);
	l->prec = NULL; // le prédécesseur de la tête est null
	while (n-- > 1) {
		nouv->succ = malloc(sizeof(d_node));
		nouv->succ->info = 1 + (rand() % m);
		nouv->succ->prec = nouv; // on opère le 'cablage arrière' avant d'itérer
		nouv = nouv->succ;
	}
	nouv->succ = NULL;
	return l;
}

// Corrigé 2.5
/*
Symetrique(l : LDC) : booléen
Donnée : la la liste à examiner
Variable locale : q, pointeur que l'on positionne sur la queue de liste avant
de faire la vérification
				n, compteur pour mesurer la taille de la liste
début
	si l vide alors retourner vrai
	q <- l
	n <- 1
	ttq q->succ non vide faire
		q <- q->succ
		n <- n + 1
	fin
	n <- n / 2
	ttq n > 0 faire
		si l->info =/= q->info alors retourner faux
		l <- l->succ
		q <- q->prec
		n <- n - 1
	fin
	retourner vrai
fin
*/
int sym(d_list l) {
	if (DEBUG) printf("sym(%p)\n", l);
	d_list q;
	int n;
	if (!l) return 1;
	q = l;
	n = 1;
	while (q->succ) {
		q = q->succ;
		n++;
	}
	n /= 2;
	while (n) {
		if (l->info != q->info) return 0;
		l = l->succ;
		q = q->prec;
		n--;
	}
	return 1;
}

// 3.2
/*
EstCirculaire(l : liste) : booléen
début
	si l = vide alors retour faux
	h <- l
	tant que vrai faire
		l <- l->succ
		si l est vide alors retourner faux
		si l = h alors retourner vrai
	fin
fin
*/


// Fusion(l1, l2 : listes) : liste
/*
Variables locales : l (liste à retourner), q : le dernier maillon de l1 ou l2, raccordé à l
début
	si l1 vide alors retourner l2
	si l2 vide alors retourner l1
	si l1->info < l2->info alors
		q <- l <- l1
		l1 <- l1->succ
	sinon
		q <- l <- l2
		l2 <- l2->succ
	fin
	ttq l1 non vide et l2 non vide faire
		si l1->info < l2->info alors
			q <- q->succ <- l1
			l1 <- l1->succ
		sinon
			q <- q->succ <- l2
			l2 <- l2->succ
		fin
	fin
	si l1 non vide alors q->succ <- l1
	si l2 non vide alors q->succ <- l2
	retourner l
fin
// RECURSIVE
début
	si l1 vide alors retourner l2
	si l2 vide alors retourner l1
	si l1->info < l2->info alors
		l <- l1
		l1 <- l1->succ
	sinon
		l <- l2
		l2 <- l2->succ
	fin
	l->succ <- Fusion(l1, l2)
fin
*/




// 7. l'inversion récursive de liste


int main() {
	// création d'une liste de taille n fixé par l'utilisateur
	srand(time(NULL));

	int n;
	list l_1_n, l_n_1;
	printf("Saisir la taille de la liste > ");
	scanf("%d", &n);
	print_list("l 1 ... n", l_1_n = create_1_n(n));
	printf("\n");
	print_list_rec(l_n_1 = create_n_1(n));
	printf("\n");
	printf("somme liste 1 ... n : %d\n", sum_iter(l_1_n));
	printf("somme liste n ... 1 : %d\n", sum_rec(l_n_1));
	printf("queue de la liste 1 ... n : %d\n", tail_iter(l_1_n)->info);
	printf("queue de la liste 1 ... n : %d\n", tail_rec(l_n_1)->info);
	suppr_iter(&l_1_n);
	print_list("l 1 ... n apres suppr_iter", l_1_n);
	suppr_rec(&l_n_1); // => à corriger, bug sur la finalisation
	print_list("l n ... 1 apres suppr_rec", l_n_1);


	// creation d'une liste aléatoire de taille n à valeurs comprises entre 1 et m
	list alea = creat_alea_list(10, 5);
	print_list("alea list : ", alea);

	printf("\nderniere position de 1 dans alea : %d\n", last_pos_of(alea, 1));
	printf("\nderniere position de 2 dans alea : %d\n", last_pos_of(alea, 2));
	printf("\nderniere position de 3 dans alea : %d\n", last_pos_of(alea, 3));
	printf("\nderniere position de 4 dans alea : %d\n", last_pos_of(alea, 4));
	printf("\nderniere position de 5 dans alea : %d\n", last_pos_of(alea, 5));

	suppr_occs(&alea, 1);
	print_list("alea list apres suppr occs 1 : ", alea);
	suppr_occs(&alea, 2);
	print_list("alea list apres suppr occs 2 : ", alea);
	suppr_occs(&alea, 3);
	print_list("alea list apres suppr occs 3 : ", alea);
	suppr_occs(&alea, 4);
	print_list("alea list apres suppr occs 4 : ", alea);
	suppr_occs(&alea, 5);
	print_list("alea list apres suppr occs 5 : ", alea);

	// on crée des LDC de taille n comportant des 1, 2, 3, 4 et 5
	// jusqu'à en trouver une de symétrique
	d_list ldc;
	int k = 1;
	do {
		ldc = creat_alea_d_list(n, 5);
		printf("%d) ", k++);
		print_d_list("la liste ", ldc);
		printf(" %s symetrique\n", sym(ldc) ? "est" : "n'est pas");
	} while (!sym(ldc));

	return 0;
}






