#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/distribuer.h"
#include "../include/joueurs.h"
#include "../include/structures.h"

int* tritabalea(int num) {//trie un tableau d'int de taille num avec des numéros de 0 à num-1 aléatoirement

    int tab[num], * tab2, tmp;
    tab2 = malloc(sizeof(int) * num);

    for (int i = 0; i < num; i++) {
        tab[i] = i;
    }

    for (int i = num; i > 0; i--) {
        tmp = rand() % i;
        tab2[num - i] = tab[tmp];
        for (int j = tmp; j < num; j++) {
            tab[j] = tab[j + 1];
        }
    }

    return tab2;
}

tresor* inittresors() {//crée le tableau de trésors

    tresor* listetresors;
    listetresors = malloc(sizeof(tresor) * 49);

    for (int i = 0; i < 24; i++) {
        listetresors[i].nom = malloc(sizeof(char) * 33);
    }

    FILE* f = fopen("tresors.txt", "r");
    int* tab = tritabalea(24);

    for (int i = 0; i < 24; i++) {
        listetresors[tab[i]].nom = fgets(listetresors[tab[i]].nom, 33, f);
        listetresors[i].numero = i;
    }

    fclose(f);

    return listetresors;
}

joueur* trier_tresors(joueur* tabj) {//distribue les trésors aux joueurs et joueuses
    int j;
    tresor* listet = inittresors();

    for (int i = 0; i < nbrj; i++) {

        if (tabj[i].listetresors == NULL) {
            printf("erreur: trier_tresors: malloc tabj[%d].listetresors", i);
        }
        j = 0;

        while (j < 24/nbrj) {
            tabj[i].listetresors[j] = listet[j + (i * (24 / nbrj))];
            j++;
        }

    }

    return tabj;
}