
// Exos listes

// Exo 1 - Difficulté intermiédiaire

// codage de l'algorithme de Thomas


#include <stdio.h>
#include <stdlib.h>

#define BASE 10 // base de représentation des nombres (numération de position)

// représentation d'un nombre en tant que liste chaînée de digits
// NB > le bit de poids faible est en tête et celui de poids fort en queue
typedef struct digit {
	unsigned val; 		// un digit compris entre 0 et BASE - 1
	struct digit *succ;
} digit;

typedef digit *number;


/* crée un simple digit */
digit *new_digit(unsigned val) {
	digit *d = malloc(sizeof(digit));
	d->val = val;
	d->succ = NULL;
	return d;
}


/* créer un nombre en tant que liste chaînée à partir d'une valeur passée en tant que type primitif unsigned */
number new_number(unsigned n) {
	if (n == 0) return NULL;	// 0 est représenté par la liste vide !
	unsigned d = n % BASE;		// extraction du digit
	number _n = new_digit(d); 	// création
	n /= BASE;					// décalage vers la droite
	_n->succ = new_number(n);
	return _n;
}


void print_number(number _n) {
	if (!_n) printf("_\n");
	else {
		printf("%u", _n->val);
		print_number(_n->succ);
	}
}

// Algo de Thomas (nb : la base n'est pas passée en paramètre, c'est la constante symolique BASE)
number sum_rec(number _n1, number _n2) {
	if (!_n1 && !_n2) return NULL;
	number _n;
	number _m;
	unsigned r; // remainder
	if (!_n1) {
		_n = sum_rec(_n1, _n2->succ);
		r = _n2->val;
	} else if (!_n2) {
		_n = sum_rec(_n1->succ, _n2);
		r = _n1->val;
	} else {
		_n = sum_rec(_n1->succ, _n2->succ);
		r = _n1->val + _n2->val;
	}
	if (r >= BASE) {
		r -= BASE;
		_m = new_digit(1);
		_n = sum_rec(_n, _m);
	}
	_m = new_digit(r);
	_m->succ = _n;
	return _m;
}



int main() {

	// création d'un number à partir d'une valeur unsigned
	number _n1 = new_number(9999);
	// affichage 
	print_number(_n1);

	number _n2 = new_number(1111);
	// affichage 
	print_number(_n2);

	number _n3 = sum_rec(_n1, _n2);
	print_number(_n3);


}












