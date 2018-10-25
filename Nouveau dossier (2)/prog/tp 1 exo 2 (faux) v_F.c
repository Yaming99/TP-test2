#include <stdio.h>
#include <stdlib.h>
#define TAILLE 100


typedef struct Livre{
    char* Nom;
    char* Auteur;
    int date;
    float prix;

}Livre;

int main()
{
    int i,nb;
    Livre* t;
    t=malloc(sizeof(Livre));
    t->Nom ="Test";


    Livre** Plivre;
    printf("Nombre de livre");
    scanf("%d",&nb);
    Plivre=malloc(sizeof(Livre*)*nb);


    for(i=0;i<nb;i++){
        Plivre[i]=malloc(sizeof(Livre));

        printf("Nom du Livre \n");
        scanf("%s",Plivre[i]->Nom);
        printf("Nom de l'auteur \n");
        scanf("%s",Plivre[i]->Auteur);
        printf("Date de parution \n");
        scanf("%d",&Plivre[i]->date);
        printf("Prix du livre \n");
        scanf("%f",&Plivre[i]->prix);
    }

    for(i=0;i<nb;i++){
        printf("%s\n",Plivre[i]->Nom);
        printf("%s\n",Plivre[i]->Auteur);
        printf("%d\n",Plivre[i]->date);
        printf("%.2f\n",Plivre[i]->prix);
    }




    return 0;
}
