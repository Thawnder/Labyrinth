#ifndef FONCTIONSJOUER_TOUR_H
#define FONCTIONSJOUER_TOUR_H
#include "pousser.h"
#include "creerplateau.h"
#include "structures.h"

extern int est_ce_une_ia_qui_joue;

Case trouver_case_avec_tresor(plateau p, tresor t);

int est_on_sur_tresor(joueur j);

void tresor_suivant(joueur j);

int deplacer_pion(joueur j, plateau p, Case c);

int pion_deplacable(plateau p, Case c1, Case c2);

int peut_on_deplacer_ici(plateau p, Case c1, Case c2);

Case case_proche_tresor(plateau p, Case c1, tresor t);

int case_compatible(Case c1, Case c2, char orientation);

coupsIA analyse_coups_possibles_IA(plateau p, joueur j, tresor t, joueur* joupt);



#endif
