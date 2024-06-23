#ifndef PLANTAMIZ_PLATEAU_H
#define PLANTAMIZ_PLATEAU_H


#include "plantamiz.h"


typedef struct combinaison{
    int elimination[LARGEUR][HAUTEUR];
    int nb_soleils;
    int nb_fraises;
    int nb_oignons;
    int nb_pommes;
    int nb_mandarine;
} combinaison;

combinaison* evaluation(char tab[LARGEUR][HAUTEUR]);
void affichage(char tab[LARGEUR][HAUTEUR], combinaison *resultat);
void lecturetest(char tab[LARGEUR][HAUTEUR]);
#endif //PLANTAMIZ_PLATEAU_H
