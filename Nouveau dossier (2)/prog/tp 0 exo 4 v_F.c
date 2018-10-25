#include <stdio.h>
#include <stdlib.h>

int main()
{
    int taille;
    int i,j,h;

    printf("Definissez la taille de votre tableau\n");
    scanf("%d",&taille);

    char **tab = malloc(sizeof(char*)*taille);
    for(i=0;i<taille;i++){
        tab[i]=malloc(sizeof(char)*taille);
    }



    for(i=0; i<taille;i++)
    {for(j=0;j<taille;j++)
        for(j=0;j<taille;j++)
        {
        printf("Definissez la valeur \n");
        scanf(" %c",&tab[i][j]); // espace devant pour enlever le entré
        }
    }

    for(i=0; i<taille;i++)
    {
        for(j=0;j<taille;j++)
        {
        printf("%c ",tab[i][j]);
        }
        printf("\n");
    }



    for(i=0;i<taille;i++)
    {
        for(j=(taille-1); j>=0;j--)
        {
        printf("%c ",tab[j][i]);
        }


        printf("\n");
    }










    return 0;
}
