#include <stdio.h>
#include "sauvegarde.h"
// Fonction pour charger une partie
void charger_partie() {
    SaveData data;
    if (load_game("sauvegarde.dat", &data)) {
        // Utilisez les données chargées pour initialiser le jeu
        // Exemple: player.x = data.player_x; player.y = data.player_y; score = data.score;
        jeu_charger_partie();
    } else {
        allegro_message("Erreur lors du chargement de la partie.");
    }
}

// Fonction pour charger la partie sauvegardée
int load_game(const char *filename, SaveData *data) {
    FILE *file = fopen(filename, "rb"); // Ouvrir le fichier en mode lecture binaire
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        return 0;
    }

    if (fread(data, sizeof(SaveData), 1, file) != 1) {
        perror("Erreur lors de la lecture du fichier de sauvegarde");
        fclose(file);
        return 0;
    }

    fclose(file); // Fermer le fichier
    return 1;
}

void jeu_charger_partie() {
    clear_to_color(screen, makecol(0, 0, 0));
    textout_ex(screen, font, "Jeu - Charger une partie", LARGEUR_ECRAN / 2 - 100, HAUTEUR_ECRAN / 2, makecol(255, 255, 255), -1);
    readkey();
    // Initialisez ici les variables de la partie chargée
}