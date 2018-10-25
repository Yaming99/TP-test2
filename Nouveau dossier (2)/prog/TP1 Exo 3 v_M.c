#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ecrireFichier();
int menu(int nbLivre);
int nbLivre();
void viderBuffer();
void lire(char *chaine);
void afficher(int choixDuLivre);

int main()
{

    int     nblivre, choix, qa;

    nblivre = nbLivre();

    do
    {
        nblivre = nbLivre();
        printf("[Menu]\n");
        qa = menu(nblivre);

        printf("\n\nvotre choix ? : ");
        scanf("%d", &choix);
        printf("\n");
        viderBuffer();
        //printf("choix:%d   qa: %d",choix, qa);
        if (choix == qa)
        {
            printf("[Livre %d]\n",qa);
            ecrireFichier();
        }
        if (choix <= qa-1) afficher(choix);

        printf("\n");

    }
    while(choix < (qa + 2));

    return (0);
}

int nbLivre()
{
    int     nblivre;
    char    c;
    FILE*   fichier;

    fichier = fopen("fichier.txt","r");
    nblivre = 0;
    c = fgetc(fichier);

    while (c != EOF)
    {
        c = fgetc(fichier);
        if (c == '\n') nblivre++;
    }
    return nblivre;
}

int menu(int nblivre)
{
    int     i;
    char    c;
    FILE*   fichier;

    i = -1;
    fichier = fopen("fichier.txt","r");
    c = fgetc(fichier);

    while(++i < nblivre)
    {
        printf("%d. ",i+1);
        while (c != EOF && c != '\n' && c != '\t')
        {
            printf("%c",c);
            c = fgetc(fichier);
        }

        while (c != '\n') c = fgetc(fichier);

        printf("\n");
        c = fgetc(fichier);
    }

    printf("%d. Ajouter un livre\n%d. Quitter", i+1, i+2);
    return i+1;
}

void ecrireFichier()
{
    char titre[200];
    char auteur[100];
    int annee;
    float prix;
    FILE*   fichier;

    fichier = fopen("fichier.txt","a+");
    if (fichier != NULL)
    {
        //fprintf(fichier,"1.")
        printf("titre ?: ");
        fgets(titre,200,stdin);
        lire(titre);
        fprintf(fichier,"%s\t",titre);

        printf("auteur ?: ");
        fgets(auteur,100,stdin);
        lire(auteur);
        fprintf(fichier, "%s\t", auteur);

        printf("date ?: ");
        scanf("%d",&annee);
        fprintf(fichier,"%d\t",annee);

        printf("prix ?: ");
        scanf("%f",&prix);
        fprintf(fichier,"%.2f\n",prix);

        fclose(fichier);
    }
    else printf("erreur");
}

void afficher(int choixDuLivre)
{
    FILE*   fichier;
    int n,compt;
    char c;

    n = 1;
    compt = 0;

    printf("Livre %d",choixDuLivre);
    fichier = fopen("fichier.txt","r");
    if (choixDuLivre > 1)
    {
        while(n != 0)
        {
            c = fgetc(fichier);
            if (c == '\n') compt ++;
            if ((compt+1) == choixDuLivre) n = 0;
        }
    }


    printf("\n");
    printf("titre: ");
    c = fgetc(fichier);
    while(c != EOF && c != '\n' && c != '\t')
    {
        printf("%c",c);
        c = fgetc(fichier);
    }

    printf("\n");
    printf("auteur: ");
    c = fgetc(fichier);
    while(c != EOF && c != '\n' && c != '\t')
    {
        printf("%c",c);
        c = fgetc(fichier);
    }

    printf("\n");
    printf("date: ");
    c = fgetc(fichier);
    while(c != EOF && c != '\n' && c != '\t')
    {
        printf("%c",c);
        c = fgetc(fichier);
    }

    printf("\n");
    printf("prix: ");
    c = fgetc(fichier);
    while(c != EOF && c != '\n' && c != '\t')
    {
        printf("%c",c);
        c = fgetc(fichier);
    }

    printf("\n");
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void lire(char *chaine)
{
    char *positionEntree = NULL;

    if (chaine != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL) *positionEntree = '\0';
    }

}
