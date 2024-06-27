#include <allegro.h> 
#include "plantamiz.h"
// Dimensions du tableau
#define LARGEUR 40
#define HAUTEUR 25


void affiche(plateau *ptab) {

    // Définir les couleurs pour chaque lettre
    int colors[256];
    colors['S'] = makecol(255, 255, 0);// Jaune pour "Soleil"
    colors['F'] = makecol(255, 0, 0);// Rouge pour "Fraise"
    colors['P'] = makecol(0, 255, 0); // Vert pour "Pomme"
    colors['O'] = makecol(255, 165, 0); // Orange pour "Oignon"
    colors['M'] = makecol(255, 140, 0); // Mandarine
    // Effacer l'écran
    clear_to_color(screen, makecol(0, 0, 0));
    // Afficher le tableau avec les couleurs
    for (int ligne = 0; ligne < HAUTEUR; ligne++) {
        for (int colonne = 0; colonne < LARGEUR; colonne++) {
            char c = (*ptab)[colonne][ligne];
            int color = colors[c];
            textprintf_ex(screen, font, colonne * 20, ligne * 20, color, -1, "%c", c);
        }
    }

}
