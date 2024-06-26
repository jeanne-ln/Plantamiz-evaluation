#ifndef PLANTAMIZ_EVALUATION_H
#define PLANTAMIZ_EVALUATION_H


#include "plantamiz.h"


typedef struct score{
    int nb_soleils;
    int nb_fraises;
    int nb_oignons;
    int nb_pommes;
    int nb_mandarine;
} score;

score* evaluation(plateau* ptab);

void affichage(plateau* ptab, score *resultat);
void lecturetest(plateau* ptab);
#endif //PLANTAMIZ_EVALUATION_H
