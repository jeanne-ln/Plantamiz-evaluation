#include <stdio.h>
#include <stdlib.h>
#include "evaluation.h"

char tab[LARGEUR][HAUTEUR];

void lecturetest(){
    FILE *f=fopen("test", "r");
    if(!f){
        printf("impossible d'ouvrir le fichier");
        exit(1);
    }
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;colonne++){
            fscanf(f,"%c",&tab[colonne][ligne]);
        }
    }
    fclose(f);
}

void affichage(){
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;colonne++){
            printf("%c",tab[colonne][ligne]);
        }
        //printf("\n");
    }
}


int main(void) {
    lecturetest();
    affichage();

    return 0;
}
