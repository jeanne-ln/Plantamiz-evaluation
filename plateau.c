#include <stdlib.h>
#include <stdio.h>
#include "plateau.h"
#include "evaluation.h"



char nouvel_element(){
    int hasard=rand()%5;
    switch(hasard){
        case 0: return 'S';
        case 1: return 'F';
        case 2: return 'M';
        case 3: return 'O';
        case 4: return 'P';
    }
}

plateau* premier_plateau(){
    plateau *ptab=malloc(sizeof(plateau));
    if(!ptab){
        printf("impossible d'allouer un plateau\n");
        exit(1);
    }
    for (int ligne = 0; ligne < HAUTEUR; ligne++) {
        for (int colonne = 0; colonne < LARGEUR; colonne++) {
            (*ptab)[colonne][ligne]=nouvel_element();
        }
    }
    combinaison* resultat = evaluation(ptab);
    disparition(ptab, resultat->elimination);
    int encore_des_trous;
    do {
        encore_des_trous=0;
        for (int ligne = 0; ligne < HAUTEUR; ligne++) {
            for (int colonne = 0; colonne < LARGEUR; colonne++) {
                if ((*ptab)[colonne][ligne] == ' ') {
                    encore_des_trous=1;
                    position trou;
                    trou.ligne = ligne;
                    trou.colonne = colonne;
                    char element = nouvel_element();
                    chute(ptab, &trou, element);
                }
            }
        }
    }while(encore_des_trous);
    return ptab;
}

void disparition(plateau* ptab, int trous[LARGEUR][HAUTEUR]){}
void echange(plateau* ptab, position* A, position* B){}
void chute(plateau* ptab, position* trou, char element){}

