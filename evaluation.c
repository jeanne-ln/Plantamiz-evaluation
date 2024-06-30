#include <stdio.h>
#include <stdlib.h>
#include "evaluation.h"

void motif_horizontal(plateau* ptab,int trous[LARGEUR][HAUTEUR]);
void motif_vertical(plateau* ptab, int trous[LARGEUR][HAUTEUR]);
void motif_h(plateau* ptab, int trous[LARGEUR][HAUTEUR]);
void motif_rect(plateau* ptab, int trous[LARGEUR][HAUTEUR]);
void MAJ_score(char symbole, int score);
int haut(plateau* ptab, int colonne,int ligne);
int bas(plateau* ptab, int colonne,int ligne);
int gauche(plateau* ptab, int colonne,int ligne);
int droite(plateau* ptab, int colonne,int ligne);


score resultat;

score* evaluation(plateau* ptab) {
    int trous[LARGEUR][HAUTEUR];
    for (int ligne = 0; ligne < HAUTEUR; ligne++) {
        for (int colonne = 0; colonne < LARGEUR; colonne++) {
            trous[colonne][ligne] = 0;
        }
    }
    resultat.nb_soleils = 0;//initialisation du score
    resultat.nb_fraises = 0;
    resultat.nb_mandarine = 0;
    resultat.nb_oignons = 0;
    resultat.nb_pommes = 0;
    motif_horizontal(ptab, trous);//recherche des motifs
    motif_vertical(ptab, trous);
    motif_h(ptab, trous);
    motif_rect(ptab, trous);
    for (int ligne = 0; ligne < HAUTEUR; ligne++) {
        for (int colonne = 0; colonne < LARGEUR; colonne++) {
            if(trous[colonne][ligne]){
                (*ptab)[colonne][ligne]=' ';// affichage des trous
            }
        }
    }
    if(resultat.nb_soleils +resultat.nb_fraises + resultat.nb_mandarine + resultat.nb_oignons + resultat.nb_pommes){
        return &resultat;
    }
    return 0;// si il n'y a pas de points, il n'y a pas de combinaisons donc pas de trous
}

void MAJ_score(char symbole, int score){
    switch(symbole) {
        case 'S': resultat.nb_soleils += score; break;
        case 'F': resultat.nb_fraises += score; break;
        case 'M': resultat.nb_mandarine += score; break;
        case 'O': resultat.nb_oignons += score; break;
        case 'P': resultat.nb_pommes += score; break;
    }
}

void motif_horizontal(plateau* ptab, int trous[LARGEUR][HAUTEUR]){// recherche de motifs horizontal
    for(int ligne=0;ligne<HAUTEUR;ligne++){ //on parcours le tableau
        for(int colonne=0;colonne<LARGEUR;){
            char symbole=(*ptab)[colonne][ligne]; //on regarde le symbole de la case
            int longueur=1; // initialisation de la longueur
            int score=0;
            while (colonne++<LARGEUR-1 && (*ptab)[colonne][ligne] == symbole) {
                longueur++;//on regarde les symboles à coté, tant que ce sont les même on augmente la valeur
            }
            if (longueur >= 6) {// si la longueur est plus grande que 6 on enlève tous les élements du même type du tableau
                for(int i=0;i<HAUTEUR;i++){
                    for(int j=0;j<LARGEUR;j++){
                        if((*ptab)[j][i]==symbole){
                            score++;
                            trous[j][i]=1;
                        }
                    }
                }
            }else if(longueur>=3) {
                score=longueur;
                for (int j = colonne-longueur; j<colonne; j++){
                    trous[j][ligne] = 1;
                }
            }
            MAJ_score(symbole,score);
        }
    }
}

void motif_vertical(plateau* ptab, int trous[LARGEUR][HAUTEUR]){
    for(int colonne=0;colonne<LARGEUR;colonne++){
        for(int ligne=0;ligne<HAUTEUR;){
            char symbole=(*ptab)[colonne][ligne];
            int longueur=1;
            int score=0;
            while (ligne++<HAUTEUR-1 && (*ptab)[colonne][ligne] == symbole) {
                longueur++;
            }
            if (longueur >= 6) {
                for(int i=0;i<HAUTEUR;i++){
                     for(int j=0;j<LARGEUR;j++){
                        if((*ptab)[j][i]==symbole){
                            score++;
                            trous[j][i]=1;
                        }
                    }
                }
            }else if(longueur>=3) {
                score=longueur;
                for (int i = ligne-longueur; i<ligne; i++){
                    trous[colonne][i] = 1;
                }
            }
            MAJ_score(symbole,score);
        }
    }
}

int haut(plateau* ptab, int colonne,int ligne){// calcul d'une longueur vers le haut
    char symbole=(*ptab)[colonne][ligne];
    int longueur=1;
    while (ligne-->0 && (*ptab)[colonne][ligne] == symbole) {
        longueur++;
    }
    return longueur;
}

int bas(plateau* ptab, int colonne,int ligne){//calcul d'une longueur vers le bas
    char symbole=(*ptab)[colonne][ligne];
    int longueur=1;
    while (ligne++<HAUTEUR-1 && (*ptab)[colonne][ligne] == symbole) {
        longueur++;
    }
    return longueur;
}

int gauche(plateau* ptab, int colonne,int ligne){//calcul d'une longueur vers la gauche
    char symbole=(*ptab)[colonne][ligne];
    int longueur=1;
    while (colonne-->0 && (*ptab)[colonne][ligne] == symbole) {
        longueur++;
    }
    return longueur;
}

int droite(plateau* ptab, int colonne,int ligne){//calcul d'une longueur vers la droite
    char symbole=(*ptab)[colonne][ligne];
    int longueur=1;
    while (colonne++<LARGEUR-1 && (*ptab)[colonne][ligne] == symbole) {
        longueur++;
    }
    return longueur;
}

int min(int x, int y){// calcul du minimum de deux nombres
    if(x>y) return y;
    else return x;
}

void motif_h(plateau* ptab, int trous[LARGEUR][HAUTEUR]){
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;colonne++){
            int hauteurmax=min(haut(ptab,colonne,ligne),bas(ptab,colonne,ligne));
            if(hauteurmax<2){
                continue;
            }
            int largeurmax = droite(ptab,colonne,ligne);
            if(largeurmax<3){
                continue;
            }
            for(int largeur=3;largeur<=largeurmax;largeur++){
                int hauteur_droite=min(haut(ptab,colonne+largeur-1,ligne),bas(ptab,colonne+largeur-1,ligne));
                if(hauteur_droite<2){
                    continue;
                }
                //on a trouvé un H !
                int hauteur=min(hauteurmax,hauteur_droite)*2-1;
                for(int l=ligne-(hauteur-1)/2;l<=ligne+(hauteur-1)/2;l++){
                    trous[colonne][l]=1;
                    trous[colonne+largeur-1][l]=1;
                }
                for(int c=colonne;c<=colonne+largeur-1;c++){
                    trous[c][ligne]=1;
                }
                int score=2*(2*hauteur+largeur-2);
                char symbole=(*ptab)[colonne][ligne];
                MAJ_score(symbole,score);
            }
        }
    }
}


void motif_rect(plateau* ptab, int trous[LARGEUR][HAUTEUR]){
    for(int ligne=0;ligne<HAUTEUR;ligne++){// on parcours le tableau
        for(int colonne=0;colonne<LARGEUR;colonne++){
            int hauteur_max=bas(ptab, colonne,ligne);//on regarde la longueur vers le bas
            int largeur_max=droite(ptab,colonne,ligne);// et la longueur vers la droite
            if(hauteur_max<2 || largeur_max<2){// si la hauteur ou la largeur est plus petite que 2 il n'y a pas de rectangle on passe à la case suivante
                continue;
            }
            for(int l=ligne+1;l<=ligne+hauteur_max-1;l++){//on parcours le rectangle formé par la hauteur et la largeur trouvé
                for(int c=colonne+1;c<=colonne+largeur_max-1;c++){
                    int hauteur=l-ligne+1;//on calcul la hauteur et la largeur necessaire pour former un rectangle
                    int largeur=c-colonne+1;
                    if(haut(ptab,c,l)<hauteur){//si la hauteur actuelle est plus petite que la hauteur necessaire il n'y a pas de rectangle
                        continue;
                    }
                    if(gauche(ptab,c,l)<largeur){//si la largeur actuelle est plus petite que la largeur necessaire il n'y a pas de rectangle
                        continue;
                    }
                    //on a un rectangle !!
                    for(int lig=ligne;lig<=ligne+hauteur-1;lig++){//mise à jour du tableau des trous
                        trous[colonne][lig]=1;
                        trous[colonne+largeur-1][lig]=1;
                    }
                    for(int col=colonne;col<=colonne+largeur-1;col++){
                        trous[col][ligne]=1;
                        trous[col][ligne+hauteur-1]=1;
                    }
                    int score=2*hauteur*largeur;// calcul du score
                    char symbole=(*ptab)[colonne][ligne];
                    MAJ_score(symbole,score);
                }
            }
        }
    }
}
