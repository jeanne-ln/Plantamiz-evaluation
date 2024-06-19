#include <stdio.h>
#include "evaluation.h"

combinaison resultat;

combinaison* evaluation(char tab[LARGEUR][HAUTEUR]){
    int nb=0,i=1;
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;colonne++){
            resultat.elimination[colonne][ligne] = 0;
        }
    }
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;colonne++){
            if(tab[colonne][ligne]==tab[colonne+1][ligne]){
                nb=0;
                i=1;
                if(tab[colonne][ligne]=='S') {
                    nb++;
                    if (tab[colonne][ligne] == tab[colonne + 1][ligne]) {
                        while (tab[colonne + i][ligne] == 'S') {
                            nb++;
                            i++;
                        }
                        if (nb >= 4) {
                            resultat.nb_soleils += nb;
                            for (int j = colonne; j<colonne+i; j++) {
                                resultat.elimination[j][ligne] = 1;
                            }
                            colonne=colonne+i-2;
                        }
                    }
                    continue;
                }
                if(tab[colonne][ligne]=='F') {
                    nb++;
                    if (tab[colonne][ligne] == tab[colonne + 1][ligne]) {
                        while (tab[colonne + i][ligne] == 'F') {
                            nb++;
                            i++;
                        }
                        if (nb >= 4) {
                            resultat.nb_fraises += nb;
                            for (int j = colonne; j<colonne+i; j++) {
                                resultat.elimination[j][ligne] = 1;
                            }
                            colonne=colonne+i-2;
                        }
                    }
                    continue;
                }
                if(tab[colonne][ligne]=='O') {
                    nb++;
                    if (tab[colonne][ligne] == tab[colonne + 1][ligne]) {
                        while (tab[colonne + i][ligne] == 'O') {
                            nb++;
                            i++;
                        }
                        if (nb >= 4) {
                            resultat.nb_oignons += nb;
                            for (int j = colonne; j<colonne+i; j++) {
                                resultat.elimination[j][ligne] = 1;
                            }
                            colonne=colonne+i-2;
                        }
                    }
                    continue;
                }
                if(tab[colonne][ligne]=='P') {
                    nb++;
                    if (tab[colonne][ligne] == tab[colonne + 1][ligne]) {
                        while (tab[colonne + i][ligne] == 'P') {
                            nb++;
                            i++;
                        }
                        if (nb >= 4) {
                            resultat.nb_pommes += nb;
                            for (int j = colonne; j<colonne+i; j++) {
                                resultat.elimination[j][ligne] = 1;
                            }
                            colonne=colonne+i-2;
                        }
                    }
                    continue;
                }
                if(tab[colonne][ligne]=='M') {
                    nb++;
                    if (tab[colonne][ligne] == tab[colonne + 1][ligne]) {
                        while (tab[colonne + i][ligne] == 'M') {
                            nb++;
                            i++;
                        }
                        if (nb >= 4) {
                            resultat.nb_mandarine += nb;
                            for (int j = colonne; j<colonne+i; j++) {
                                resultat.elimination[j][ligne] = 1;
                            }
                            colonne=colonne+i-2;
                        }
                    }
                    continue;
                }
            }
        }
    }

    return &resultat;
}
