#include <time.h>
#include <stdio.h>
#include "jeux.h"
#include "plateau.h"
#include "affichage.h"
#include "evaluation.h"
#include "sauvegarde.h"
#define BOARD_ROWS 25
#define BOARD_COLS 45
#define MAX_MOVES 30
#define INITIAL_LIVES 5
#define NOMBRE_CONTRATS 3

void mise_a_jour_score(score* delta_score,Partie *partie);
int affiche_temps(time_t start_time, int temps_limite);

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
    affiche(&partie->tab,selection, &curseur,&partie->points);
    time_t start_time;
    start_time = time(NULL);
    int arret=0;
    while(!arret){
        arret=affiche_temps(start_time, 60);
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
            if(touche == KEY_ESC){
                sauvegarder_jeu("sauvegarde_plantamiz.txt",partie);
                arret=1;
            }
            if(selection && (touche==KEY_DOWN || touche==KEY_UP || touche==KEY_LEFT || touche==KEY_RIGHT)){
                selection=0;
                echange(&partie->tab, &precedent, &curseur);
                score* delta_score=evaluation(&partie->tab);
                if(delta_score){
                    mise_a_jour_score(delta_score,partie);
                    affiche(&partie->tab,selection, &curseur,&partie->points);
                    affiche_temps(start_time, 60);

                    while(1) {
                        sleep(1);
                        bouche_les_trous(&partie->tab);
                        delta_score = evaluation(&partie->tab);
                        affiche(&partie->tab,selection, &curseur,&partie->points);
                        affiche_temps(start_time, 60);
                        if(!delta_score) break;
                        mise_a_jour_score(delta_score,partie);
                    }
                }

            }
            affiche(&partie->tab,selection, &curseur,&partie->points);
            affiche_temps(start_time, 60);

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

int affiche_temps(time_t start_time, int temps_limite){
    time_t current_time;
    current_time=time(NULL);
    int temps_restant;
    static int precedent=0;
    int ecoule;
    ecoule = (int)(current_time - start_time);
    temps_restant = temps_limite - ecoule;
    if(precedent!=temps_restant) {
        rectfill(screen, 120, 570, 800, 600, makecol(0, 0, 0));
        textprintf_ex(screen, font, 10, 575, makecol(255, 255, 255), -1, "temps restant: %d", temps_restant);
        precedent=temps_restant;
    }
    if(temps_restant<=0){
        return 1;
    }
    return 0;
}



