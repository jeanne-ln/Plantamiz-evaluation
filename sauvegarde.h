
#ifndef PLANTAMIZ_SAUVEGARDE_H
#define PLANTAMIZ_SAUVEGARDE_H
#include "plantamiz.h"
typedef struct {
    int player_x;
    int player_y;
    int score;
    // Ajoutez d'autres variables nécessaires pour l'état du jeu
} SaveData;

void charger_partie();
int load_game(const char *filename, SaveData *data);
void jeu_charger_partie();
#endif //PLANTAMIZ_SAUVEGARDE_H
