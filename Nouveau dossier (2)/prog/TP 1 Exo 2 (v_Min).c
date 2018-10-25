#include <stdio.h>
#include <stdlib.h>

typedef struct s_livre
{
    char titre[100];
    char auteur[100];
    int date;
    float prix;
}               T_livre;

void afficher(T_livre *tab, int nb);
void remplir(T_livre *tab, int nb);
void afficher_choix(T_livre *tab, int choix);
void menu(T_livre *tab, int nb);

int main()
{
    int nb;
    int choix;

    printf("combien de livre?: ");
    scanf("%d",&nb);

    T_livre *tab = NULL;

    tab = (T_livre*)malloc(nb*sizeof(T_livre**));

    remplir(tab, nb);
    afficher(tab, nb);

    printf("votre choix ?: ");
    scanf("%d",&choix);

    afficher_choix(tab, choix);

    while(choix <= nb)
    {
        menu(tab, nb);
        printf("votre choix ? : ");
        scanf("%d",&choix);
    }

    return (0);
}

void remplir(T_livre *tab, int nb)
{
    int i;

    i = 0;

    while(i<nb)
    {

        printf("titre %d ?: ",i+1);
        scanf("%s",tab[i].titre);

        printf("auteur %d ?: ",i+1);
        scanf("%s",tab[i].auteur);

        printf("date %d ?: ",i+1);
        scanf("%d",&tab[i].date);

        printf("prix %d ?: ",i+1);
        scanf("%f",&tab[i].prix);

        i++;
    }
}

void afficher(T_livre *tab, int nb)
{
    int i;
    i = 0;

    while(i<nb)
    {

        printf("\n[Livre %d]\n",i+1);
        printf("Titre : %s\n", tab[i].titre);
        printf("Auteur : %s\n", tab[i].auteur);
        printf("Date de parution : %d\n", tab[i].date);
        printf("Prix indicatif : %f\n\n", tab[i].prix);
        i++;
    }
}

void afficher_choix(T_livre *tab, int choix)
{
    printf("[Livre %d]\n",choix);
    printf("Titre : %s\n", tab[choix-1].titre);
    printf("Auteur : %s\n", tab[choix-1].auteur);
    printf("Date de parution : %d\n", tab[choix-1].date);
    printf("Prix indicatif : %f\n\n", tab[choix-1].prix);
}

void menu(T_livre *tab, int nb)
{
    int i;

    i = 0;

    printf("[Menu]\n");
    while (i<nb)
    {
        printf("Titre : %s\n", tab[i].titre);
        i++;
    }
    printf("%d')' pour Quitter\n",nb+1);

}
