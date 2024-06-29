#include <stdlib.h>
#include <stdio.h>
#include "plateau.h"
#include "evaluation.h"
#include <time.h>


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

void initialise_plateau(plateau* ptab){
    srand(time(0));
    for (int ligne = 0; ligne < HAUTEUR; ligne++) {
        for (int colonne = 0; colonne < LARGEUR; colonne++) {
            (*ptab)[colonne][ligne]=nouvel_element();
        }
    }
    while(1) {
        score *resultat = evaluation(ptab);
        if(!resultat) break;
        int encore_des_trous;
        do {
            encore_des_trous = 0;
            for (int ligne = 0; ligne < HAUTEUR; ligne++) {
                for (int colonne = 0; colonne < LARGEUR; colonne++) {
                    if ((*ptab)[colonne][ligne] == ' ') {
                        encore_des_trous = 1;
                        position trou;
                        trou.ligne = ligne;
                        trou.colonne = colonne;
                        char element = nouvel_element();
                        chute(ptab, &trou, element);
                    }
                }
            }
        } while (encore_des_trous);
    }
}


void echange(plateau* ptab, position* A, position* B){
    char symbole = (*ptab)[A->colonne][A->ligne];
    (*ptab)[A->colonne][A->ligne]=(*ptab)[B->colonne][B->ligne];
    (*ptab)[B->colonne][B->ligne]= symbole;
}

void chute(plateau* ptab, position* trou, char element){
    int colonne=trou->colonne;
    for(int ligne=trou->ligne;ligne>0;ligne--){
        (*ptab)[colonne][ligne]=(*ptab)[colonne][ligne-1];
    }
    (*ptab)[colonne][0]=element;
}

