#include <stdlib.h>
#include <stdio.h>

// 1. déclarer un maillon de lists chaînée
struct node {
	int info;
	struct node *succ;
};

// tips :
// 1. pour se débarraser des expressions struct node et les remplacer par de simples node
// => typedef struct node node;
// 2. pour se débarrasser des expressions node * (enfin, struct node *)
// typedef node * list;


 //3. affecter des valeurs à ses champs et les lire
 //4. assembler deux maillons entre eux pour former une liste élémentaire

/*
Affichage(l : liste)
début
	tantque l =/= VIDE faire
		afficher '->(' + l->info + ')'
		l <- l->succ
	fin (ttq)
	afficher '->x'
fin
*/

void pretty_print(struct node *l) {
	while (l != NULL) {
		printf("->(%d)", l->info);
		l = l->succ;
	}
	printf("->x\n");
}


// création récursive d'une liste contenant 1 à n

struct node *create(int n) {
	if (n <= 0) return NULL;
	struct node *head = malloc(sizeof(struct node));
	head->info = n;
	head->succ = create(n - 1);
	return head;
}

//typedef expression_longue_type nom_alias;
//typedef struct node node;


int main() {

	// 2. créer un maillon statiquement
 	struct node a, b;
 	struct node c;

 	a.info = 1;
 	b.info = 2;
 	c.info = 3;

 	a.succ = &b;
 	b.succ = &c;
 	c.succ = NULL;

	// 2. créer un maillon dynamiquement
 	struct node *pa	= malloc(sizeof(struct node));
	struct node *pb	= malloc(sizeof(struct node));
	struct node *pc	= malloc(sizeof(struct node));

	/*
	pa->info = 1;
	pb->info = 2;
	pc->info = 3;
	*/
	printf("saisir > ");
	scanf("%d", &(pa->info));
	printf("saisir > ");
	scanf("%d", &(pb->info));
	printf("saisir > ");
	scanf("%d", &(pc->info));


	// p->field veut dire exactement la même chose que (*p).field

 	pa->succ = pb;
 	pb->succ = pc;
 	pc->succ = NULL;

 	pretty_print(pa);

 	int n;
	printf("saisir taille liste > ");
	scanf("%d", &n);
	pretty_print(create(n));



	return 0;
}