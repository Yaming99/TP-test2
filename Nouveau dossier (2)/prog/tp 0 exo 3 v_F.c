#include <stdio.h>
#include <stdlib.h>



int rand_a_b(int a, int b)
{
    return rand()%(b-a)+a;
}


int main()
{

    int nbTicket;
    int Lots =3;
    int i,j;
    int a = 0;
    int b = 100;
    int Ticket[Lots];
    int n=0;


    printf("Combien de ticket voulez vous ?\n");
    scanf("%d",&nbTicket);

    if(nbTicket<=Lots){
    printf("Augmenter votre nombre de ticket svp\n");
    scanf("%d",&nbTicket);
    }
    int *tab = malloc(sizeof(int) * nbTicket);



    for(i=0 ; i<nbTicket ; i++)
    {
        tab[i]=rand_a_b(a,b);
        printf("%d \t",tab[i]);
    }
tab[0]=5;
    for(i=0 ; i<Lots ; i++)
    {
        Ticket[i]=rand_a_b(a,b);
        printf("Ticket gagnant du Lot %d est le %d \n",i,Ticket[i]);
    }



    for(i=0 ; i<nbTicket ; i++){
        for(j=0;j<Lots;j++)
        {
            tab[0]=5;
            if(tab[i]==Ticket[j])
            {
                    printf("Vous avez gagné le lot %d",j);
                    n++;
            }
        }
    }
    if(n==0)printf("Looser");
    return 0;
}
