//
// Created by jeanne on 27/06/24.
//

#ifndef PLANTAMIZ_AFFICHAGE_H
#define PLANTAMIZ_AFFICHAGE_H
#include "plantamiz.h"
void affiche(plateau *ptab,position* selection);
void affiche_curseur(position, int is_selected);
void affiche_selection(plateau *ptab,position);
void efface_selection(plateau *ptab,position);
#endif //PLANTAMIZ_AFFICHAGE_H
