#include <stdio.h>
#include "evaluation.h"

combinaison resultat;

combinaison* evaluation(char tab[LARGEUR][HAUTEUR]){
    resultat.nb_soleils=1;
    resultat.nb_fraises=2;
    resultat.nb_oignons=3;
    resultat.nb_pommes=4;
    resultat.nb_mandarine=5;
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;colonne++){
            resultat.elimination[colonne][ligne] = 0;
        }
    }
    resultat.elimination[0][0] = 1;
    resultat.elimination[1][1] = 1;
    resultat.elimination[2][2] = 1;
    resultat.elimination[3][3] = 1;
    resultat.elimination[4][4] = 1;
    resultat.elimination[5][5] = 1;
    return &resultat;
}
