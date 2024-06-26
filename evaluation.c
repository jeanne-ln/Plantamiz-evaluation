#include <stdio.h>
#include <stdlib.h>
#include "evaluation.h"

void motif_horizontal(plateau* ptab);
void motif_vertical(plateau* ptab);
void motif_h(plateau* ptab);
void motif_rect(plateau* ptab);
void MAJ_score(char symbole, int score);
int haut(plateau* ptab, int colonne,int ligne);
int bas(plateau* ptab, int colonne,int ligne);
int gauche(plateau* ptab, int colonne,int ligne);
int droite(plateau* ptab, int colonne,int ligne);


combinaison resultat;

combinaison* evaluation(plateau* ptab) {

    for (int ligne = 0; ligne < HAUTEUR; ligne++) {
        for (int colonne = 0; colonne < LARGEUR; colonne++) {
            resultat.elimination[colonne][ligne] = 0;
        }
    }
    resultat.nb_soleils = 0;
    resultat.nb_fraises = 0;
    resultat.nb_mandarine = 0;
    resultat.nb_oignons = 0;
    resultat.nb_pommes = 0;
    motif_horizontal(ptab);
    motif_vertical(ptab);
    motif_h(ptab);
    motif_rect(ptab);
    if(resultat.nb_soleils +resultat.nb_fraises + resultat.nb_mandarine + resultat.nb_oignons + resultat.nb_pommes){
        return &resultat;
    }
    return 0;
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

void motif_horizontal(plateau* ptab){
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;){
            char symbole=(*ptab)[colonne][ligne];
            int longueur=1;
            int score=0;
            while (colonne++<LARGEUR-1 && (*ptab)[colonne][ligne] == symbole) {
                longueur++;
            }
            if (longueur >= 6) {
                for(int i=0;i<HAUTEUR;i++){
                    for(int j=0;j<LARGEUR;j++){
                        if((*ptab)[j][i]==symbole){
                            score++;
                            resultat.elimination[j][i]=1;
                        }
                    }
                }
            }else if(longueur>=3) {
                score=longueur;
                for (int j = colonne-longueur; j<colonne; j++){
                    resultat.elimination[j][ligne] = 1;
                }
            }
            MAJ_score(symbole,score);
        }
    }
}

void motif_vertical(plateau* ptab){
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
                            resultat.elimination[j][i]=1;
                        }
                    }
                }
            }else if(longueur>=3) {
                score=longueur;
                for (int i = ligne-longueur; i<ligne; i++){
                    resultat.elimination[colonne][i] = 1;
                }
            }
            MAJ_score(symbole,score);
        }
    }
}

int haut(plateau* ptab, int colonne,int ligne){
    char symbole=(*ptab)[colonne][ligne];
    int longueur=1;
    while (ligne-->0 && (*ptab)[colonne][ligne] == symbole) {
        longueur++;
    }
    return longueur;
}

int bas(plateau* ptab, int colonne,int ligne){
    char symbole=(*ptab)[colonne][ligne];
    int longueur=1;
    while (ligne++<HAUTEUR-1 && (*ptab)[colonne][ligne] == symbole) {
        longueur++;
    }
    return longueur;
}

int gauche(plateau* ptab, int colonne,int ligne){
    char symbole=(*ptab)[colonne][ligne];
    int longueur=1;
    while (colonne-->0 && (*ptab)[colonne][ligne] == symbole) {
        longueur++;
    }
    return longueur;
}

int droite(plateau* ptab, int colonne,int ligne){
    char symbole=(*ptab)[colonne][ligne];
    int longueur=1;
    while (colonne++<LARGEUR-1 && (*ptab)[colonne][ligne] == symbole) {
        longueur++;
    }
    return longueur;
}

int min(int x, int y){
    if(x>y) return y;
    else return x;
}

void motif_h(plateau* ptab){
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
                    resultat.elimination[colonne][l]=1;
                    resultat.elimination[colonne+largeur-1][l]=1;
                }
                for(int c=colonne;c<=colonne+largeur-1;c++){
                    resultat.elimination[c][ligne]=1;
                }
                int score=2*(2*hauteur+largeur-2);
                char symbole=(*ptab)[colonne][ligne];
                MAJ_score(symbole,score);
            }
        }
    }
}


void motif_rect(plateau* ptab){
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;colonne++){
            int hauteur_max=bas(ptab, colonne,ligne);
            int largeur_max=droite(ptab,colonne,ligne);
            if(hauteur_max<2 || largeur_max<2){
                continue;
            }
            for(int l=ligne+1;l<=ligne+hauteur_max-1;l++){
                for(int c=colonne+1;c<=colonne+largeur_max-1;c++){
                    int hauteur=l-ligne+1;
                    int largeur=c-colonne+1;
                    if(haut(ptab,c,l)<hauteur){
                        continue;
                    }
                    if(gauche(ptab,c,l)<largeur){
                        continue;
                    }
                    //on a un rectangle !!
                    for(int lig=ligne;lig<=ligne+hauteur-1;lig++){
                        resultat.elimination[colonne][lig]=1;
                        resultat.elimination[colonne+largeur-1][lig]=1;
                    }
                    for(int col=colonne;col<=colonne+largeur-1;col++){
                        resultat.elimination[col][ligne]=1;
                        resultat.elimination[col][ligne+hauteur-1]=1;
                    }
                    int score=2*hauteur*largeur;
                    char symbole=(*ptab)[colonne][ligne];
                    MAJ_score(symbole,score);
                }
            }
        }
    }
}
