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
// Exo 1 retourne le max d'un arbre
// d'entiers positifs et retourne -1 si l'arbre est vide
/*
Max(a : arbre) : entier
Donnée : a, l'arbre examiné
Variables locales : max, entier, le max de a
début
	si a vide alors retourner -1
	max <- a->info
	max_sa <- Max(a->sag)
	si max_sa > max alors max <- max_sa
	max_sa <- Max(a->sad)
	si max_sa > max alors max <- max_sa
	retourner max
*/
int max(tree t) {
	if (!t) return -1;
	int max = t->info;
	int max_st = max(t->sag);
	if (max_st > max) max = max_st;
	max_st = max(t->sad);
	if (max_st > max) max = max_st;
	return max;	
}

/* Exo2 > algo itératif qui retourne sous forme de liste chaînée
les n premiers éléments d'un AB en suivant un parcours en largeur

ListeLargeur(a: AB, n : entier) : liste
Donnée : bla
Variables locales : bla
file f auxiliaire
h, q, deux références respectivement sur la tête et la queue de la liste à construire
début
	enfiler(f, a)
	h <- réserver Maillon
	h->info <- a->info
	q <- h
	tant que nonvide(f) et n > 0 faire
		a <- defiler(f)
		// faire un truc avec a
		q <- q->succ <- réserver Maillon
		q->info <- a->info
		si non vide a->sag alors enfiler(a->sag)
		si non vide a->sad alors enfiler(a->sad)
		n <- n - 1
	fin
	q->succ <- vide
	retourner h
fin 
*/
















