#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/joueurs.h"
#include "../include/structures.h"

int nbrj;
joueur* tableaujoueurs;

joueur creer_ia(joueur j) {
    j.ia = 1;
    return j;
}

void demander_joueurs_humains(joueur* tabjoueurs) {
    int nbria;
    printf("Combien il y a-t-il d'IA?\n");
    scanf("%d", &nbria);
    if (nbria > nbrj - 1) {
        printf("Erreur: le nombre d'IA n'est pas cohérent, il faut au mois un.e joueur.euse.s");
    }

    for (int i = 0; i < nbria; i++) {
        tabjoueurs[i] = creer_ia(tabjoueurs[i]);
    }
}

joueur* demander_nombre_joueurs() {
    int nbr;
    printf("Combien de joueur.euse.s dans cette partie?\n");
    scanf("%d", &nbr);
    nbrj = nbr;
    if (nbr != 2 && nbr != 3 && nbr != 4) {
        printf("Erreur: le nombre de joueur.euse.s n'est pas approprié. Il doit être égal à 2,3 ou 4.");
    }
    joueur* tabj = (joueur*)malloc(sizeof(joueur) * nbr);

    for (int i = 0; i < nbr; i++) {
        tabj[i].pseudo = (char*)malloc(sizeof(char) * 30);
        tabj[i].couleur = (char*)malloc(sizeof(char) * 30);
        tabj[i].listetresors = (tresor*)malloc(sizeof(tresor) * 49);
        tabj[i].nbrtreres = 24 / nbrj;
    }

    for (int i = 0; i < nbr; i++) {
        tabj[i].numero = i + 1;
    }

    return tabj;
}

void demander_pseudo_joueur(joueur* tabjoueurs) {
    for (int i = 0; i < nbrj; i++) {
        printf("Quelle est le pseudo du joueur %d?\n", i + 1);
        scanf("%s", tabjoueurs[i].pseudo);
    }
}



joueur* entrer_joueurs() {
    tableaujoueurs = demander_nombre_joueurs();
    demander_joueurs_humains(tableaujoueurs);
    demander_pseudo_joueur(tableaujoueurs);
    return tableaujoueurs;
}

