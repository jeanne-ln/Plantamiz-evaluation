#include <stdio.h>
#include "sauvegarde.h"

int load_game(const char *filename, Partie *data);
// Fonction pour charger une partie
Partie* charger_partie() {
    Partie* pdata;
    pdata=(Partie*)malloc(sizeof(Partie));
    if(!pdata){
        printf("impossible d'allouer une partie\n");
        exit(1);
    }
    if (load_game("sauvegarde.dat", pdata)) {
        // Utilisez les données chargées pour initialiser le jeu
        // Exemple: player.x = data.player_x; player.y = data.player_y; score = data.score;

    } else {
        allegro_message("Erreur lors du chargement de la partie.");
    }
}

// Fonction pour charger la partie sauvegardée
int load_game(const char *filename, Partie *data) {
    FILE *file = fopen(filename, "rb"); // Ouvrir le fichier en mode lecture binaire
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        return 0;
    }

    if (fread(data, sizeof(Partie), 1, file) != 1) {
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