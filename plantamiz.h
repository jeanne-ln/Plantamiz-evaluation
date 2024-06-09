//
// Created by jeanne on 08/06/24.
//

#ifndef PLANTAMIZ_PLANTAMIZ_H
#define PLANTAMIZ_PLANTAMIZ_H

#endif //PLANTAMIZ_PLANTAMIZ_H
#define LARGEUR 25
#define HAUTEUR 40

typedef struct position{
int ligne;
int colonne;
} position;

typedef struct combinaison{
    int nombre_eliminations;
    position *elimination;
    int nb_soleils;
    int nb_fraises;
    int nb_oignons;
    int nb_pommes;
    int nb_mandarine;

} combinaison;

combinaison* evaluation(char tab[LARGEUR][HAUTEUR]);
