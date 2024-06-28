#include <allegro.h> 
#include "plantamiz.h"
// Dimensions du tableau
#define LARGEUR 40
#define HAUTEUR 25
#define TILE_SIZE 20


void affiche(plateau *ptab, position* selection) {

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


void affiche_curseur(position curseur, int is_selected){
    // Déterminer la couleur du curseur
    int cursor_color = is_selected ? makecol(0, 0, 0) : makecol(255, 255, 255);

    // Afficher le curseur autour de la lettre spécifiée
    rect(screen, curseur.colonne * TILE_SIZE - 6 , curseur.ligne * TILE_SIZE  - 8,
         curseur.colonne * TILE_SIZE + TILE_SIZE - 8, curseur.ligne * TILE_SIZE + TILE_SIZE -6,
         cursor_color);
    rect(screen, curseur.colonne * TILE_SIZE - 5 , curseur.ligne * TILE_SIZE  - 7,
         curseur.colonne * TILE_SIZE + TILE_SIZE - 9, curseur.ligne * TILE_SIZE + TILE_SIZE -7,
         cursor_color);
    rect(screen, curseur.colonne * TILE_SIZE - 4 , curseur.ligne * TILE_SIZE  - 6,
         curseur.colonne * TILE_SIZE + TILE_SIZE - 10, curseur.ligne * TILE_SIZE + TILE_SIZE -8,
         cursor_color);

}

void affiche_selection(plateau *ptab,position selection){
    // Définir les couleurs pour chaque lettre
    int colors[256] = {0};
    colors['S'] = makecol(255, 255, 0); // Jaune pour "Soleil"
    colors['F'] = makecol(255, 0, 0);   // Rouge pour "Fraise"
    colors['P'] = makecol(0, 255, 0);   // Vert pour "Pomme"
    colors['O'] = makecol(255, 165, 0); // Orange pour "Oignon"
    colors['M'] = makecol(255, 140, 0); // Mandarine
    // Déterminer la couleur de la lettre sélectionnée
    char selected_char = (*ptab)[selection.colonne][selection.ligne];
    int letter_color = colors[(unsigned char)selected_char];
    int background_color = makecol(115, 8, 0); // Rouge pour la sélection

    // Afficher le fond coloré derrière la lettre
    rectfill(screen, selection.colonne * TILE_SIZE-6, selection.ligne * TILE_SIZE-8,
             selection.colonne * TILE_SIZE + TILE_SIZE-8, selection.ligne * TILE_SIZE + TILE_SIZE-6,
             background_color);

    // Réafficher la lettre par-dessus le fond coloré
    textprintf_ex(screen, font, selection.colonne * TILE_SIZE, selection.ligne * TILE_SIZE,
                  letter_color, -1, "%c", selected_char);
}

void efface_selection(plateau *ptab,position selection){
    // Définir les couleurs pour chaque lettre
    int colors[256] = {0};
    colors['S'] = makecol(255, 255, 0); // Jaune pour "Soleil"
    colors['F'] = makecol(255, 0, 0);   // Rouge pour "Fraise"
    colors['P'] = makecol(0, 255, 0);   // Vert pour "Pomme"
    colors['O'] = makecol(255, 165, 0); // Orange pour "Oignon"
    colors['M'] = makecol(255, 140, 0); // Mandarine
    // Déterminer la couleur de la lettre sélectionnée
    char selected_char = (*ptab)[selection.colonne][selection.ligne];
    int letter_color = colors[(unsigned char)selected_char];
    int background_color = makecol(0, 0, 0); // effacement du rouge

    // Afficher le fond coloré derrière la lettre
    rectfill(screen, selection.colonne * TILE_SIZE-6, selection.ligne * TILE_SIZE-8,
             selection.colonne * TILE_SIZE + TILE_SIZE-8, selection.ligne * TILE_SIZE + TILE_SIZE-6,
             background_color);

    // Réafficher la lettre par-dessus le fond coloré
    textprintf_ex(screen, font, selection.colonne * TILE_SIZE, selection.ligne * TILE_SIZE,
                  letter_color, -1, "%c", selected_char);
}