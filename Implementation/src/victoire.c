#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include "../include/victoire.h"
#include "../include/structures.h"

void afficher_message_victoire(joueur j) {
    printf("%s a remporté la partie!", j.pseudo);
}

int case_depart(joueur j) {

    if (j.nbrtreres == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int unjoueuragagne = 0;

void victoire_dun_joueur(joueur j) {

    if (case_depart(j) == 1) {
        afficher_message_victoire(j);
        unjoueuragagne = 1;
    }
}
