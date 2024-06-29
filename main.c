#include <stdio.h>
#include <stdlib.h>

#include "plantamiz.h"
#include "jeux.h"
#include "sauvegarde.h"

#define NOMBRE_OPTIONS_MENU 3


typedef struct {
    char *texte;
    void (*action)();
} OptionMenu;

void quitter();
void dessiner_menu(OptionMenu *options_menu, int selection);

// Fonction pour quitter le jeu
void quitter() {
    clear_to_color(screen, makecol(0, 0, 0));
    textout_ex(screen, font, "Quitter sélectionné", LARGEUR_ECRAN / 2 - 100, HAUTEUR_ECRAN / 2, makecol(255, 255, 255), -1);
    readkey();
    exit(0);
}

// Fonction pour dessiner le menu
void dessiner_menu(OptionMenu *options_menu, int selection) {
    clear_to_color(screen, makecol(0, 0, 0));
    for (int i = 0; i < NOMBRE_OPTIONS_MENU; i++) {
        int couleur = (i == selection) ? makecol(255, 0, 0) : makecol(255, 255, 255);
        textout_ex(screen, font, (i == selection) ? "> " : "  ", LARGEUR_ECRAN / 2 - 70, HAUTEUR_ECRAN / 2 - 40 + i * 30, couleur, -1);
        textout_ex(screen, font, options_menu[i].texte, LARGEUR_ECRAN / 2 - 50, HAUTEUR_ECRAN / 2 - 40 + i * 30, couleur, -1);
    }
}

// Fonction principale du jeu
int main(void) {
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, LARGEUR_ECRAN, HAUTEUR_ECRAN, 0, 0);

    OptionMenu options_menu[NOMBRE_OPTIONS_MENU] = {
            {"Nouvelle partie", demarrer_nouvelle_partie},
            {"Charger une partie", charger_partie},
            {"Quitter", quitter}
    };

    int selection = 0;
    dessiner_menu(options_menu, selection);

    while (1) {
        if (keypressed()) {
            int touche = readkey()>>8;
            if (touche == KEY_UP) {
                selection = (selection > 0) ? selection - 1 : NOMBRE_OPTIONS_MENU - 1;
            } else if (touche == KEY_DOWN) {
                selection = (selection < NOMBRE_OPTIONS_MENU - 1) ? selection + 1 : 0;
            } else if (touche == KEY_ENTER_PAD) {
                options_menu[selection].action();
                // Redessiner le menu après avoir joué ou chargé une partie
            }
            dessiner_menu(options_menu, selection);
        }
    }

    return 0;
}END_OF_MAIN()


