#include <stdio.h>
#include <stdlib.h>
#define TAILLE 150

typedef struct Livre
{
    char Nom[TAILLE];
    char Prenom[TAILLE];
    char Auteur[TAILLE];
    int date;
    float prix;
} Livre;


int main()
{
    Livre Livres;
    printf("Nom du Livre\n");
    scanf("%[^\n]s",Livres.Nom); // Stylé faut connaitre ca garde jusqu'a faire entré

    //Livre.Prenom = malloc(sizeof(char)*taille) si on ne connait pas la taille

    printf("Nom de l'auteur\n");
    scanf("%s",Livres.Auteur);
    printf("La date de parution\n");
    scanf("%d",&Livres.date);
    printf("Le prix du livre\n");
    scanf("%f",&Livres.prix);

    printf("Nom du Livre %s\n",Livres.Nom);
    printf("Nom de l'auteur %s\n",Livres.Auteur);
    printf("Nom du Livre %d\n",Livres.date);
    printf("Prix du Livre %.2f\n",Livres.prix); // Apprendre .2f = 2 chiffre apres la virgule

    return 0;
}
