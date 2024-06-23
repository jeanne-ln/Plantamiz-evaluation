#ifndef PLANTAMIZ_PLANTAMIZ_H
#define PLANTAMIZ_PLANTAMIZ_H
#define LARGEUR 40
#define HAUTEUR 25
//on doit tous travailler sur un tableau de ce type
//avec dans chaque case 'F' ou 'P' ou 'O' ou 'S' ou 'M' (en majuscule)
//char tab[LARGEUR][HAUTEUR];

typedef struct position{
    int ligne;
    int colonne;
} position;

#endif //PLANTAMIZ_PLANTAMIZ_H

