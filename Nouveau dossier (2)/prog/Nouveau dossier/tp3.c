#include<stdio.h>
#include<stdlib.h>

typedef struct  tampon{
    int i;
    int j;
    char *chaine;
}               tampon;

int main(){
    int N;
    tampon *buffer;

    printf("taille?: ");
    scanf("%d",&N);

    buffer->chaine = malloc(N*sizeof(char));

    return (0);
}

void ecrire(tampon *buffer, char c){

    buffer->i = 0;
    while(i != j){
        write(1, &c, 1);
    }
}

}

void lire(tampon *buffer){

    buffer->j = 0;

}
