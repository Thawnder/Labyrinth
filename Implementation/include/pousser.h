#ifndef FONCTIONSPOUSSER_H
#define FONCTIONSPOUSSER_H
#include "structures.h"
#include "joueurs.h"
#include "creerplateau.h"
#include "jouer_tour.h"


int est_elle_decalable(int l, plateau p);

plateau pousser_rangee(int numdeligne, plateau p, joueur* jou, char orientation);

plateau derniere_ligne(int l, plateau p);

plateau inserer_case(int i, int j, plateau p);

Case changer_valeurs_orientations(Case c);

#endif