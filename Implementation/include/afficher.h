#ifndef FONCTIONSAFFICHER_H
#define FONCTIONSAFFICHER_H
#include "structures.h"
#include "joueurs.h"

void afficher_plateau(plateau p);

void afficher_case_tmp(Case casetmp);

void afficher_lignes(plateau p);

void afficher_ligne(int numl, plateau p);

void afficher_case(Case c, int num);

void afficher_liste_tresors();

void afficher_coup(Case c1, Case c2, int l, joueur j);

#endif