#ifndef FONCTIONSCREERPLATEAU_H
#define FONCTIONSCREERPLATEAU_H
#include "structures.h"
#include "distribuer.h"
#include "joueurs.h"

plateau creer_plateau(joueur* j);

int* transformertab(int* tab, plateau p);

plateau placer_tresors(plateau p, joueur* j);

void cherchercaseavecnum(plateau p, int num, int* pi, int* pj);

char orientationalea();

plateau tri_aleatoire_cases_mouvantes(plateau p);

plateau assignation_indices_cases(plateau p);

plateau creer_casesfixes();

plateau assigner_valeurs_orientations(plateau p);


#endif