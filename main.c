#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "plantamiz.h"
#include "evaluation.h"
#include "plateau.h"
#include "affichage.h"

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


int main(void) {
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
    curseur.colonne=13;
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
}END_OF_MAIN()
