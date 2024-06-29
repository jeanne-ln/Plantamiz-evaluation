#include <time.h>
#include <stdio.h>
#include "jeux.h"
#include "plateau.h"
#include "affichage.h"
#include "evaluation.h"
#define BOARD_ROWS 25
#define BOARD_COLS 45
#define MAX_MOVES 30
#define INITIAL_LIVES 5
#define NOMBRE_CONTRATS 3

void mise_a_jour_score(score* delta_score,Partie *partie);

const Contrat tab_contrats[NOMBRE_CONTRATS] = {
        {{10,10,10,10,10}, 100, 300},
        {{30,30,30,30,30}, 50, 250},
        {{40,40,40,40,40}, 40, 200}
};


Partie* nouvelle_partie(){
    Partie* partie;
    partie=(Partie*)malloc(sizeof(Partie));
    if(!partie){
        printf("impossible d'allouer une partie\n");
        exit(1);
    }
    partie->points.nb_pommes=0;
    partie->points.nb_soleils=0;
    partie->points.nb_oignons=0;
    partie->points.nb_fraises=0;
    partie->points.nb_mandarine=0;
    partie->niveau=0;
    partie->nb_coup_restant = tab_contrats[partie->niveau].nb_coups;
    partie->temps_restant = tab_contrats[partie->niveau].temps;
    initialise_plateau(&partie->tab);

    return partie;
}
void jouer(Partie* partie){
    position curseur;
    int selection=0;
    curseur.colonne=0;
    curseur.ligne=0;
    affiche(&partie->tab,selection, &curseur);
    while(1){
        if (keypressed()) {
            position precedent;
            precedent.colonne=curseur.colonne;
            precedent.ligne=curseur.ligne;
            int touche = readkey() >> 8;
            if (touche == KEY_UP) {
                if (curseur.ligne == 0) {
                    curseur.ligne = HAUTEUR - 1;
                    selection=0;
                }else{
                    curseur.ligne--;
                }
            }
            if (touche == KEY_DOWN) {
                if (curseur.ligne == HAUTEUR-1) {
                    curseur.ligne = 0;
                    selection=0;
                }else{
                    curseur.ligne++;
                }
            }
            if (touche == KEY_RIGHT) {
                if (curseur.colonne == LARGEUR-1) {
                    curseur.colonne = 0;
                    selection=0;
                }else{
                    curseur.colonne++;
                }
            }
            if (touche == KEY_LEFT) {
                if (curseur.colonne == 0) {
                    curseur.colonne = LARGEUR-1;
                    selection=0;
                }else{
                    curseur.colonne--;
                }
            }
            if(touche== KEY_SPACE){
                selection=1-selection;
            }
            if(selection && (touche==KEY_DOWN || touche==KEY_UP || touche==KEY_LEFT || touche==KEY_RIGHT)){
                selection=0;
                echange(&partie->tab, &precedent, &curseur);
                score* delta_score=evaluation(&partie->tab);
                if(delta_score){
                    mise_a_jour_score(delta_score,partie);
                    affiche(&partie->tab,selection, &curseur);

                    while(1) {
                        while(!key[KEY_ENTER_PAD]){}
                        bouche_les_trous(&partie->tab);
                        delta_score = evaluation(&partie->tab);
                        affiche(&partie->tab,selection, &curseur);
                        if(!delta_score) break;
                        mise_a_jour_score(delta_score,partie);
                    }

                    printf("\n\n");
                    printf("score mandarine:%d\n", partie->points.nb_mandarine);
                    printf("score fraise:%d\n", partie->points.nb_fraises);
                    printf("score soleil:%d\n", partie->points.nb_soleils);
                    printf("score oignons:%d\n", partie->points.nb_oignons);
                    printf("score pomme:%d\n", partie->points.nb_pommes);


                }

            }
            affiche(&partie->tab,selection, &curseur);
        }

    }

}

void mise_a_jour_score(score* delta_score,Partie *partie){
    partie->points.nb_mandarine+=delta_score->nb_mandarine;
    partie->points.nb_fraises+=delta_score->nb_fraises;
    partie->points.nb_soleils+=delta_score->nb_soleils;
    partie->points.nb_oignons+=delta_score->nb_oignons;
    partie->points.nb_pommes+=delta_score->nb_pommes;
}

/*
void affichage(plateau* ptab, score *resultat);
void lecturetest(plateau* ptab);
void demarrer_nouvelle_partie(){

}

void lecturetest(plateau *ptab){
    char *texte = NULL;
    long longueur = 0;
    FILE *f=fopen("test", "r");
    if(!f){
        printf("impossible d'ouvrir le fichier");
        exit(1);
    }
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        if(getline(&texte, &longueur, f) == -1) {
            printf("il manque la ligne numéro %d\n", ligne);
            exit(1);
        }
        for(int colonne=0;colonne<LARGEUR;colonne++){
            char symbole = texte[colonne];
            switch(symbole) {
                case 'S':
                case 's':
                    (*ptab)[colonne][ligne] = 'S';
                    break;
                case 'F':
                case 'f':
                    (*ptab)[colonne][ligne] = 'F';
                    break;
                case 'O':
                case 'o':
                    (*ptab)[colonne][ligne] = 'O';
                    break;
                case 'P':
                case 'p':
                    (*ptab)[colonne][ligne] = 'P';
                    break;
                case 'M':
                case 'm':
                    (*ptab)[colonne][ligne] = 'M';
                    break;
                default:
                    printf("symbole inconnu ligne %d colonne %d : '%c'\n", ligne, colonne, symbole);
                    exit(1);
            }
        }
    }
    free(texte);
    fclose(f);
}

void affichage(plateau *ptab, score *resultat){
    printf("résultat de l'évaluation :\n");
    if(resultat) {
        printf("%d points soleils\n", resultat->nb_soleils);
        printf("%d points fraises\n", resultat->nb_fraises);
        printf("%d points oignons\n", resultat->nb_oignons);
        printf("%d points pommes\n", resultat->nb_pommes);
        printf("%d points mandarine\n", resultat->nb_mandarine);
    } else {
        printf("aucune combinaison trouvée\n");
    }
    printf("\n");
    for(int ligne=0;ligne<HAUTEUR;ligne++){
        for(int colonne=0;colonne<LARGEUR;colonne++){
            printf("%c",(*ptab)[colonne][ligne]);
        }
        printf("\n");
    }
}

int ancienmain(void) {
// Initialisation d'Allegro
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    score *resultat=0;
    position* selection;
    plateau *ptab=nouveau_plateau();
    //resultat = evaluation(ptab);
    affiche(ptab,  selection);
    position curseur;
    position select;
    select.ligne=20;
    select.colonne=14;
    curseur.ligne=20;
    curseur.colonne=14;
    int bool=0;
    while(!key[KEY_ESC]) {
        affiche_curseur(curseur, bool);
        readkey();
        bool=!bool;
        if(bool==0) {
            affiche_selection(*ptab,select);
        }
        if(bool==1){
            efface_selection(*ptab, select);
        }
    }
    return 0;
}

// Implémentation des fonctions du jeu
void jeu_nouvelle_partie() {
    clear_to_color(screen, makecol(0, 0, 0));
    textout_ex(screen, font, "Jeu - Nouvelle partie", LARGEUR_ECRAN / 2 - 100, HAUTEUR_ECRAN / 2, makecol(255, 255, 255), -1);
    readkey();
    // Initialisez ici les variables de la nouvelle partie
}

int process_move(char board[BOARD_ROWS][BOARD_COLS], int r1, int c1, int r2, int c2) {
    int selected_r = -1, selected_c = -1, score;
    if (key[KEY_UP]) {
        selected_r -= 1;
    } else if (key[KEY_DOWN]) {
        selected_r += 1;
    } else if (key[KEY_LEFT]) {
        selected_c -= 1;
    } else if (key[KEY_RIGHT]) {
        selected_c += 1;
    } else if (key[KEY_SPACE]) {
        if (selected_r >= 0 && selected_r < BOARD_ROWS && selected_c >= 0 && selected_c < BOARD_COLS) {
            int r2 = selected_r, c2 = selected_c;
            if (selected_r > 0) {
                int r1 = selected_r - 1, c1 = selected_c;
                int points = process_move(board, r1, c1, r2, c2);
                score += points;
            } else if (selected_r < BOARD_ROWS - 1) {
                int r1 = selected_r + 1, c1 = selected_c;
                int points = process_move(board, r1, c1, r2, c2);
                score += points;
            } else if (selected_c > 0) {
                int r1 = selected_r, c1 = selected_c - 1;
                int points = process_move(board, r1, c1, r2, c2);
                score += points;
            } else if (selected_c < BOARD_COLS - 1) {
                int r1 = selected_r, c1 = selected_c + 1;
                return 0;
            }
        }
    }
}
*/