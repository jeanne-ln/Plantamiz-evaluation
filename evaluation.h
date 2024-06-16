//
// Created by jeanne on 08/06/24.
//

#ifndef PLANTAMIZ_PLANTAMIZ_H
#define PLANTAMIZ_PLANTAMIZ_H

#endif //PLANTAMIZ_PLANTAMIZ_H
#define LARGEUR 40
#define HAUTEUR 25

typedef struct position{
int ligne;
int colonne;
} position;

typedef struct combinaison{
    int elimination[LARGEUR][HAUTEUR];
    int nb_soleils;
    int nb_fraises;
    int nb_oignons;
    int nb_pommes;
    int nb_mandarine;
} combinaison;

combinaison* evaluation(char tab[LARGEUR][HAUTEUR]);
