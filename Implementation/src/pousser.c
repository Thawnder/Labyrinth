#include <stdio.h>
#include <stdlib.h>
#include "../include/structures.h"
#include "../include/pousser.h"
#include "../include/jouer_tour.h"
#include "../include/joueurs.h"
#include "../include/creerplateau.h"


int est_elle_decalable(int numligne, plateau p) {

	if (numligne == p.ligne_tmp) {
		return 0;
	}
	else {
		return 1;
	}
}

plateau pousser_rangee(int numdeligne, plateau p, joueur* jou, char orientation) {

	if (est_elle_decalable(numdeligne, p) == 1) {

		Case tmp;

		if (numdeligne <= 3) {//->
			tmp = p.tabcases[2 * numdeligne][7];

			for (int i = 7; i > 0; i--) {//on décale
				p.tabcases[2 * numdeligne][i + 1] = p.tabcases[2 * numdeligne][i];
				p.tabcases[2 * numdeligne][i + 1].largeur++;
			}

			p = inserer_case(2 * numdeligne, 1, p);
			p.tabcases[2 * numdeligne][1].hauteur = 2 * numdeligne;
			p.tabcases[2 * numdeligne][1].largeur = 1;
			p.tabcases[2 * numdeligne][1].type[1] = orientation;
			p.tabcases[2 * numdeligne][1] = changer_valeurs_orientations(p.tabcases[2 * numdeligne][1]);

			p.case_tmp = tmp;
			p.case_tmp.hauteur = 0;
			p.case_tmp.largeur = 0;
			p = derniere_ligne(numdeligne + 3, p);

			if (jou->c.largeur == 7 && (jou->c.hauteur == 2 * numdeligne)) {
				jou->c = p.tabcases[2 * numdeligne][1];
			}
			else if (jou->c.hauteur == 2 * numdeligne) {
				jou->c = p.tabcases[jou->c.hauteur][jou->c.largeur + 1];
			}
		}

		else if (numdeligne <= 6) {//<-
			tmp = p.tabcases[2 * (numdeligne - 3)][1];

			for (int i = 1; i < 8; i++) {
				p.tabcases[2 * (numdeligne - 3)][i - 1] = p.tabcases[2 * (numdeligne - 3)][i];
				p.tabcases[2 * (numdeligne - 3)][i - 1].largeur--;
			}

			p = inserer_case(2 * (numdeligne - 3), 7, p);
			p.tabcases[2 * (numdeligne - 3)][7].hauteur = (2 * numdeligne) - 3;
			p.tabcases[2 * (numdeligne - 3)][7].largeur = 7;
			p.tabcases[2 * (numdeligne - 3)][7].type[1] = orientation;
			p.tabcases[2 * (numdeligne - 3)][7] = changer_valeurs_orientations(p.tabcases[2 * (numdeligne - 3)][7]);

			p.case_tmp = tmp;
			p.case_tmp.hauteur = 0;
			p.case_tmp.largeur = 0;
			p = derniere_ligne(numdeligne - 3, p);

			if (jou->c.largeur == 1 && (jou->c.hauteur == 2 * (numdeligne - 3))) {
				jou->c = p.tabcases[2 * (numdeligne - 3)][7];
			}
			else if (jou->c.hauteur == 2 * (numdeligne - 3)) {
				jou->c = p.tabcases[jou->c.hauteur][jou->c.largeur - 1];
			}
		}

		else if (numdeligne <= 9) {//v
			tmp = p.tabcases[7][2 * (numdeligne - 6)];

			for (int i = 7; i > 0; i--) {
				p.tabcases[i + 1][2 * (numdeligne - 6)] = p.tabcases[i][2 * (numdeligne - 6)];
				p.tabcases[i + 1][2 * (numdeligne - 6)].hauteur++;
			}

			p = inserer_case(1, 2 * (numdeligne - 6), p);
			p.tabcases[1][2 * (numdeligne - 6)].largeur = 2 * (numdeligne - 6);
			p.tabcases[1][2 * (numdeligne - 6)].hauteur = 1;
			p.tabcases[1][2 * (numdeligne - 6)].type[1] = orientation;
			p.tabcases[1][2 * (numdeligne - 6)] = changer_valeurs_orientations(p.tabcases[1][2 * (numdeligne - 6)]);

			p.case_tmp = tmp;
			p.case_tmp.hauteur = 0;
			p.case_tmp.largeur = 0;
			p = derniere_ligne(numdeligne + 3, p);

			if (jou->c.hauteur == 7 && (jou->c.largeur == 2 * (numdeligne - 6))) {
				jou->c = p.tabcases[1][2 * (numdeligne - 6)];
			}
			else if (jou->c.largeur == 2 * (numdeligne - 6)){
				jou->c = p.tabcases[jou->c.hauteur + 1][jou->c.largeur];
			}
		}

		else {//^
			tmp = p.tabcases[1][2 * (numdeligne - 9)];

			for (int i = 1; i < 8; i++) {
				p.tabcases[i - 1][2 * (numdeligne - 9)] = p.tabcases[i][2 * (numdeligne - 9)];
				p.tabcases[i - 1][2 * (numdeligne - 9)].hauteur--;
			}

			p = inserer_case(7, 2 * (numdeligne - 9), p);
			p.tabcases[7][2 * (numdeligne - 9)].largeur = 2 * (numdeligne - 9);
			p.tabcases[7][2 * (numdeligne - 9)].hauteur = 7;
			p.tabcases[1][2 * (numdeligne - 9)].type[1] = orientation;
			p.tabcases[1][2 * (numdeligne - 9)] = changer_valeurs_orientations(p.tabcases[1][2 * (numdeligne - 9)]);

			p.case_tmp = tmp;
			p.case_tmp.hauteur = 0;
			p.case_tmp.largeur = 0;
			p = derniere_ligne(numdeligne - 3, p);

			if (jou->c.hauteur == 1 && (jou->c.largeur == 2 * (numdeligne - 9))) {
				jou->c = p.tabcases[7][2 * (numdeligne - 9)];
			}
			else if (jou->c.largeur == 2 * (numdeligne - 9)) {
				jou->c = p.tabcases[jou->c.hauteur - 1][jou->c.largeur];
			}
		}

		if (est_ce_une_ia_qui_joue == 0) {
			printf("On pousse la rangée %d:\n", numdeligne);
		}
	}
	else {

		if (est_ce_une_ia_qui_joue == 0) {
			printf("Vous n'avez pas le droit de pousser la ligne inverse de celle qui a été poussée juste avant.\n");
		}
	}

	return p;
}

plateau derniere_ligne(int l, plateau p) {
	p.ligne_tmp = l;
	return p;
}

plateau inserer_case(int i, int j, plateau p) {
	p.tabcases[i][j] = p.case_tmp;
	return p;
}

Case changer_valeurs_orientations(Case c) {//version light de assigner_valeurs_orientation pour changer les valeurs quand on tourne la case temporaire

			if (c.type[0] == 'a' && c.type[1] == 'n') {
				c.h = 1;
				c.b = 1;
				c.g = 0;
				c.d = 0;
			}
			if (c.type[0] == 'a' && c.type[1] == 'e') {
				c.d = 1;
				c.g = 1;
				c.h = 0;
				c.b = 0;
			}
			if (c.type[0] == 'a' && c.type[1] == 's') {
				c.h = 1;
				c.b = 1;
				c.g = 0;
				c.d = 0;
			}
			if (c.type[0] == 'a' && c.type[1] == 'o') {
				c.d = 1;
				c.g = 1;
				c.h = 0;
				c.b = 0;
			}
			if (c.type[0] == 'b' && c.type[1] == 'n') {
				c.h = 1;
				c.d = 1;
				c.b = 0;
				c.g = 0;
			}
			if (c.type[0] == 'b' && c.type[1] == 'e') {
				c.d = 1;
				c.b = 1;
				c.g = 0;
				c.h = 0;
			}
			if (c.type[0] == 'b' && c.type[1] == 's') {
				c.g = 1;
				c.b = 1;
				c.h = 0;
				c.d = 0;
			}
			if (c.type[0] == 'b' && c.type[1] == 'o') {
				c.h = 1;
				c.g = 1;
				c.b = 0;
				c.d = 0;
			}
			if (c.type[0] == 'c' && c.type[1] == 'n') {
				c.h = 1;
				c.b = 1;
				c.d = 1;
				c.g = 0;
			}
			if (c.type[0] == 'c' && c.type[1] == 'e') {
				c.d = 1;
				c.b = 1;
				c.g = 1;
				c.h = 0;
			}
			if (c.type[0] == 'c' && c.type[1] == 's') {
				c.h = 1;
				c.b = 1;
				c.g = 1;
				c.d = 0;
			}
			if (c.type[0] == 'c' && c.type[1] == 'o') {
				c.h = 1;
				c.d = 1;
				c.g = 1;
				c.b = 0;
			}
			return c;
}