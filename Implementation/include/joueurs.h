#ifndef FONCTIONSJOUEURS_H
#define FONCTIONSJOUEURS_H 
#include "structures.h"


extern int nbrj;
extern joueur* tableaujoueurs;

joueur* demander_nombre_joueurs();

void demander_pseudo_joueur(joueur* tabjoueurs);

joueur* entrer_joueurs();

void demander_joueurs_humains(joueur* tabjoueurs);

joueur creer_ia(joueur j);

#endif
