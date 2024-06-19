#include <stdio.h>
#include <stdlib.h>
#include "evaluation.h"


void lecturetest(char tab[LARGEUR][HAUTEUR]){
    char *texte = NULL;
    long longueur = 0;
    FILE *f=fopen("test", "r");
    if(!f){
        printf("impossible d'ouvrir le fichier");
        exit(1);
    }
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        if(getline(&texte, &longueur, f) == -1) {
            printf("il manque la ligne numéro %d\n", ligne);
            exit(1);
        }
        for(int colonne=0;colonne<LARGEUR;colonne++){
            char symbole = texte[colonne];
            switch(symbole) {
                case 'S':
                case 's':
                    tab[colonne][ligne] = 'S';
                    break;
                case 'F':
                case 'f':
                    tab[colonne][ligne] = 'F';
                    break;
                case 'O':
                case 'o':
                    tab[colonne][ligne] = 'O';
                    break;
                case 'P':
                case 'p':
                    tab[colonne][ligne] = 'P';
                    break;
                case 'M':
                case 'm':
                    tab[colonne][ligne] = 'M';
                    break;
                default:
                  printf("symbole inconnu ligne %d colonne %d : '%c'\n", ligne, colonne, symbole);
                  exit(1);
            }
        }
    }
    fclose(f);
}

void affichage(char tab[LARGEUR][HAUTEUR], combinaison *resultat){
    printf("résultat de l'évaluation :\n");
    if(resultat) {
        printf("%d points soleils\n", resultat->nb_soleils);
        printf("%d points fraises\n", resultat->nb_fraises);
        printf("%d points oignons\n", resultat->nb_oignons);
        printf("%d points pommes\n", resultat->nb_pommes);
        printf("%d points mandarine\n", resultat->nb_mandarine);
    } else {
        printf("aucune combinaison trouvée\n");
    }
    printf("\n");
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;colonne++){
            if(resultat && resultat->elimination[colonne][ligne]) {
                printf(".");
            } else {
                printf("%c",tab[colonne][ligne]);
            }
        }
        printf("\n");
    }
}


int main(void) {
    char tab[LARGEUR][HAUTEUR];
    combinaison *resultat;

    lecturetest(tab);
    resultat = evaluation(tab);
    affichage(tab, resultat);

    return 0;
}
