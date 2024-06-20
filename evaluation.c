#include <stdio.h>
#include "evaluation.h"

combinaison resultat;

combinaison* evaluation(char tab[LARGEUR][HAUTEUR]){
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;colonne++){
            resultat.elimination[colonne][ligne] = 0;
        }
    }
    resultat.nb_soleils = 0;
    resultat.nb_fraises = 0;
    resultat.nb_mandarine =0;
    resultat.nb_oignons =0 ;
    resultat.nb_pommes =0 ;
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;colonne++){
            char symbole=tab[colonne][ligne];
            int longueur=1;
            int score=0;
            while (colonne<LARGEUR && tab[++colonne][ligne] == symbole) {
                longueur++;
            }
            if (longueur >= 6) {
                for(int i=0;i<HAUTEUR;i++){
                    for(int j=0;j<LARGEUR;j++){
                        if(tab[j][i]==symbole){
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
            switch(symbole) {
                case 'S': resultat.nb_soleils += score; break;
                case 'F': resultat.nb_fraises += score; break;
                case 'M': resultat.nb_mandarine += score; break;
                case 'O': resultat.nb_oignons += score; break;
                case 'P': resultat.nb_pommes += score; break;
            }
        }
    }
    for(int colonne=0;colonne<LARGEUR;colonne++){
        for(int ligne=0;ligne<HAUTEUR;ligne++){
            char symbole=tab[colonne][ligne];
            int longueur=1;
            int score=0;
            while (ligne<HAUTEUR && tab[colonne][++ligne] == symbole) {
                longueur++;
            }
            if (longueur >= 6) {
                for(int i=0;i<LARGEUR;i++){
                    for(int j=0;j<HAUTEUR;j++){
                        if(tab[j][i]==symbole){
                            score++;
                            resultat.elimination[j][i]=1;
                        }
                    }
                }
            }else if(longueur>=3) {
                score=longueur;
                for (int j = ligne-longueur; j<ligne; j++){
                    resultat.elimination[colonne][j] = 1;
                }
            }
            switch(symbole) {
                case 'S': resultat.nb_soleils += score; break;
                case 'F': resultat.nb_fraises += score; break;
                case 'M': resultat.nb_mandarine += score; break;
                case 'O': resultat.nb_oignons += score; break;
                case 'P': resultat.nb_pommes += score; break;
            }
        }
    }
    return &resultat;
}
