
#ifndef PLANTAMIZ_SAUVEGARDE_H
#define PLANTAMIZ_SAUVEGARDE_H
#include "plantamiz.h"

void sauvegarder_jeu(const char *nom_fichier, Partie *partie);
Partie* charger_partie();
void sauvegarder_partie(Partie*);
#endif //PLANTAMIZ_SAUVEGARDE_H
