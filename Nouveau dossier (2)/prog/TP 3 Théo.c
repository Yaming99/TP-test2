#include <stdio.h>
#include <stdlib.h>
//#include <C:\Users\ASUS\Desktop\pthreads\pthread.h>
#include <threads.h>

typedef struct Maillon
{
    //int state;
    char data;
    struct Maillon *next;
}Maillon;

typedef struct Tampon_dyn
{
    struct Maillon *lecture;
    struct Maillon *ecriture;
}Tampon_dyn;

/*typedef struct Box
{
    int state;
    char data;
}Box;*/

typedef struct Tampon_stat
{
    char *tab;
    int lecture,ecriture;
}Tampon_stat;

void init_tampon_stat(Tampon_stat *tampon,int taille);
void init_tampon_dyn(Tampon_dyn *tampon);
int ecrire_stat(Tampon_stat *tampon, char c, int taille);
int lire_stat(Tampon_stat *tampon, int taille);
int ecrire_dyn(Tampon_dyn *tampon,char c);
int lire_dyn(Tampon_dyn *tampon);
void augmenter_stat(Tampon_stat *tampon, int taille, int augmentation);

int main()
{
    int i;
    /*Tampon_dyn *tamp = (Tampon_dyn*)malloc(sizeof(Tampon_dyn));
    init_tampon_dyn(tamp);
    ecrire_dyn(tamp,'x');
    lire_dyn(tamp); */

    Tampon_stat *tampon = (Tampon_stat*)malloc(sizeof(Tampon_stat));
    init_tampon_stat(tampon, 10);
    ecrire_stat(tampon, 'x', 10);
    lire_stat(tampon,10);
    lire_stat(tampon,10);
    ecrire_stat(tampon, 'x', 10);
    augmenter_stat(tampon, 10, 2);

    for (i=0; i<10; ++i)
    {
        printf("%d\n",tampon->tab[i]);
    }
    return 0;
}

void init_tampon_dyn(Tampon_dyn *tampon)
{
    tampon->ecriture = tampon->lecture = (Maillon*) malloc(sizeof(Maillon));
    //tampon->ecriture->state = 0;
}

void init_tampon_stat(Tampon_stat *tampon,int taille)
{
    int i;
    tampon->tab = malloc(10);
    for (i=0; i<taille; ++i)
    {
        tampon->tab[i] = '\0';
    }
    tampon->ecriture = tampon->lecture = 0;

}

int ecrire_dyn(Tampon_dyn *tampon,char c)
{
    if(tampon == NULL || tampon->lecture == NULL) return 0;
    else
    {
        tampon->ecriture->data = c;
        tampon->ecriture->next = (Maillon*) malloc(sizeof(Maillon));
        tampon->ecriture = tampon->ecriture->next;
        tampon->ecriture->next = NULL;
        return 1;
    }
}

int lire_dyn(Tampon_dyn *tampon)
{
    if(tampon == NULL || tampon->lecture == tampon->ecriture || tampon->lecture->next == NULL) return 0;
    else
    {
        Maillon *temp;
        printf("%c",tampon->lecture->data);
        temp = tampon->lecture;
        tampon->lecture = tampon->lecture->next;
        free(temp);
        return 1;
    }
}


int ecrire_stat(Tampon_stat *tampon, char c, int taille)
{
    if(tampon == NULL ||tampon->ecriture == tampon->lecture - 1) return 0;
    else
    {
        tampon->tab[tampon->ecriture] = c;
        tampon->ecriture = (tampon->ecriture+1)%taille;
        return 1;
    }
}


int lire_stat(Tampon_stat *tampon, int taille)
{
    if(tampon == NULL || tampon->lecture == tampon->ecriture) return 0;
    else
    {
        printf("%c\n",tampon->tab[tampon->lecture]);
        tampon->lecture = (tampon->lecture+1)%taille;
        return 1;
    }
}

void augmenter_stat(Tampon_stat *tampon, int taille, int augmentation)
{
    char new_tab[taille+augmentation];
    int i;
    for (i=0; i< tampon->ecriture; ++i)
    {
        new_tab[i] = tampon->tab[(tampon->lecture+i)%taille];
    }
    tampon->lecture = 0;
    tampon->ecriture = i;
    tampon->tab = new_tab;
}

