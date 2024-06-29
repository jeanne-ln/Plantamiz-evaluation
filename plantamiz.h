#ifndef PLANTAMIZ_PLANTAMIZ_H
#define PLANTAMIZ_PLANTAMIZ_H
#include <allegro.h>
#define LARGEUR 40
#define HAUTEUR 25
#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600


typedef char plateau[LARGEUR][HAUTEUR];

typedef struct position{
    int ligne;
    int colonne;
} position;

typedef struct score{
    int nb_soleils;
    int nb_fraises;
    int nb_oignons;
    int nb_pommes;
    int nb_mandarine;
} score;

typedef struct {
    int niveau;
    score points;
    plateau tab;
    int nb_coup_restant;
    int temps_restant;
} Partie;

typedef struct {
    score contrat;
    int nb_coups;
    int temps;
}Contrat;


#endif //PLANTAMIZ_PLANTAMIZ_H

