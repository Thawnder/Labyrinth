#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/creerplateau.h"
#include "../include/distribuer.h"
#include "../include/structures.h"
#include "../include/joueurs.h"

plateau creer_plateau(joueur* j) {

	plateau p = creer_casesfixes();//les 16 cases qui ne bougent pas
	p.ligne_tmp = 0;
	p = assignation_indices_cases(p);//on assigne les indices hauteur et largeur  chaque case (0,0) pour la case_tmp
	p = tri_aleatoire_cases_mouvantes(p);//on assigne les types des cases
	p = assigner_valeurs_orientations(p);//les valeurs h,g,b,d en fonction des types
	p = placer_tresors(p, j);//on place les trsors sur le plateau
	return p;
}

plateau placer_tresors(plateau p, joueur* jo) {

	int* tab = tritabalea(49);
	int j = 0, tmp1, * p1 = &tmp1, tmp2, * p2 = &tmp2;

	for (int i = 0; i < 24; i++) {//pour chaque trsor on lui assigne le numro associ dans tab
		cherchercaseavecnum(p, tab[i], p1, p2);

		if ((tmp1 == 1 && tmp2 == 1) || (tmp1 == 1 && tmp2 == 7) || (tmp1 == 7 && tmp2 == 1) || (tmp1 == 7 && tmp2 == 7)) {//la case est un coin
			cherchercaseavecnum(p, 24 + j, p1, p2);
			p.tabcases[tmp1][tmp2].tresor = jo[i / (24 / nbrj)].listetresors[i % (24 / nbrj)];
			j++;
		}
		else {
			cherchercaseavecnum(p, tab[i], p1, p2);
			p.tabcases[tmp1][tmp2].tresor = jo[i / (24 / nbrj)].listetresors[i % (24 / nbrj)];
		}
	}
	return p;
}

void cherchercaseavecnum(plateau p, int num, int* pi, int* pj) {

	for (int i = 1; i <= 7; i++) {//on veut trouver les indices d'une case  partir de son numro
		for (int j = 1; j <= 7; j++) {
			if (p.tabcases[i][j].numcase == num) {
				*pi = i;
				*pj = j;
			}
		}
	}
}

int* transformertab(int* tab, plateau p) {//on transforme un tableau de 34 cases avec des numros de 0  33 en tableau de 34 en nombres entre 0 et 49, mais SANS les numros des cases fixes

	int* tabfin = (int*)malloc(sizeof(int) * 34);
	int tabtmp[10] = { 35,36,37,38,39,40,41,43,45,47 };
	int j = 0;

	for (int i = 0; i < 34; i++) {
		if (tab[i] == 0 || tab[i] == 2 || tab[i] == 4 || tab[i] == 6 || tab[i] == 14 || tab[i] == 16 || tab[i] == 18 || tab[i] == 20 || tab[i] == 28 || tab[i] == 30) {
			tabfin[i] = tabtmp[j]; j++;
		}
		else if (tab[i] == 32) {
			p.case_tmp.numcase = -1; 
		}
		else {
			tabfin[i] = tab[i]; 
		}
	}
	return tabfin;
}

char orientationalea() {
	int tmp = rand() % 4;
	if (tmp == 0) {
		return 'n';
	}
	else if (tmp == 1) {
		return 'e';
	}
	else if (tmp == 2) {
		return 's';
	}
	else if (tmp == 3) {
		return 'o';
	}
	else {
		return 'z';
	}
}

plateau tri_aleatoire_cases_mouvantes(plateau p) {

	int* tab = transformertab(tritabalea(34), p);//on a les numros associs aux types dans tab
	int tmp1, tmp2;
	int* pj = &tmp2, * pi = &tmp1;

	for (int i = 0; i <= 11; i++) {//on place les 12 case a
		if (tab[i] > 49) {
			p.case_tmp.type[0] = 'a';
			p.case_tmp.type[1] = orientationalea();
		}
		else {
			cherchercaseavecnum(p, tab[i], pi, pj);
			p.tabcases[tmp1][tmp2].type[0] = 'a';
			p.tabcases[tmp1][tmp2].type[1] = orientationalea();
		}
	}

	for (int i = 12; i <= 17; i++) {//les 6 cases c
		if (tab[i] > 49) {
			p.case_tmp.type[0] = 'c';
			p.case_tmp.type[1] = orientationalea();
		}
		else {
			pi = &tmp1;
			pj = &tmp2;
			cherchercaseavecnum(p, tab[i], pi, pj);
			p.tabcases[tmp1][tmp2].type[0] = 'c';
			p.tabcases[tmp1][tmp2].type[1] = orientationalea();
		}
	}

	for (int i = 18; i <= 33; i++) {//les 16 cases b
		if (tab[i] > 49) {
			p.case_tmp.type[0] = 'b';
			p.case_tmp.type[1] = orientationalea();
		}
		else {
			pi = &tmp1;
			pj = &tmp2;
			cherchercaseavecnum(p, tab[i], pi, pj);
			p.tabcases[tmp1][tmp2].type[0] = 'b';
			p.tabcases[tmp1][tmp2].type[1] = orientationalea();
		}
	}

	return p;
}

plateau assignation_indices_cases(plateau p) {

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			p.tabcases[i + 1][j + 1].numcase = (7 * i) + j;
			p.tabcases[i + 1][j + 1].hauteur = i + 1;
			p.tabcases[i + 1][j + 1].largeur = j + 1;
		}
	}
	p.case_tmp.numcase = 50;
	p.case_tmp.hauteur = 0;
	p.case_tmp.largeur = 0;
	return p;
}

plateau creer_casesfixes() {
	plateau p;
	p.tabcases[1][1].type[0] = 'b';
	p.tabcases[1][1].type[1] = 'e';
	p.tabcases[1][3].type[0] = 'c';
	p.tabcases[1][3].type[1] = 'e';
	p.tabcases[1][5].type[0] = 'c';
	p.tabcases[1][5].type[1] = 'e';
	p.tabcases[1][7].type[0] = 'b';
	p.tabcases[1][7].type[1] = 's';
	p.tabcases[3][1].type[0] = 'c';
	p.tabcases[3][1].type[1] = 'n';
	p.tabcases[3][3].type[0] = 'c';
	p.tabcases[3][3].type[1] = 'n';
	p.tabcases[3][5].type[0] = 'c';
	p.tabcases[3][5].type[1] = 'e';
	p.tabcases[3][7].type[0] = 'c';
	p.tabcases[3][7].type[1] = 's';
	p.tabcases[5][1].type[0] = 'c';
	p.tabcases[5][1].type[1] = 'n';
	p.tabcases[5][3].type[0] = 'c';
	p.tabcases[5][3].type[1] = 'o';
	p.tabcases[5][5].type[0] = 'c';
	p.tabcases[5][5].type[1] = 's';
	p.tabcases[5][7].type[0] = 'c';
	p.tabcases[5][7].type[1] = 's';
	p.tabcases[7][1].type[0] = 'b';
	p.tabcases[7][1].type[1] = 'n';
	p.tabcases[7][3].type[0] = 'c';
	p.tabcases[7][3].type[1] = 'o';
	p.tabcases[7][5].type[0] = 'c';
	p.tabcases[7][5].type[1] = 'o';
	p.tabcases[7][7].type[0] = 'b';
	p.tabcases[7][7].type[1] = 'o';
	return p;
}

plateau assigner_valeurs_orientations(plateau p) {

	for (int i = 1; i < 8; i++) {
		for (int j = 1; j < 8; j++) {
			if (p.tabcases[i][j].type[0] == 'a' && p.tabcases[i][j].type[1] == 'n') {
				p.tabcases[i][j].h = 1;
				p.tabcases[i][j].b = 1;
				p.tabcases[i][j].g = 0;
				p.tabcases[i][j].d = 0;
			}
			if (p.tabcases[i][j].type[0] == 'a' && p.tabcases[i][j].type[1] == 'e') {
				p.tabcases[i][j].d = 1;
				p.tabcases[i][j].g = 1;
				p.tabcases[i][j].h = 0;
				p.tabcases[i][j].b = 0;
			}
			if (p.tabcases[i][j].type[0] == 'a' && p.tabcases[i][j].type[1] == 's') {
				p.tabcases[i][j].h = 1;
				p.tabcases[i][j].b = 1;
				p.tabcases[i][j].g = 0;
				p.tabcases[i][j].d = 0;
			}
			if (p.tabcases[i][j].type[0] == 'a' && p.tabcases[i][j].type[1] == 'o') {
				p.tabcases[i][j].d = 1;
				p.tabcases[i][j].g = 1;
				p.tabcases[i][j].h = 0;
				p.tabcases[i][j].b = 0;
			}
			if (p.tabcases[i][j].type[0] == 'b' && p.tabcases[i][j].type[1] == 'n') {
				p.tabcases[i][j].h = 1;
				p.tabcases[i][j].d = 1;
				p.tabcases[i][j].b = 0;
				p.tabcases[i][j].g = 0;
			}
			if (p.tabcases[i][j].type[0] == 'b' && p.tabcases[i][j].type[1] == 'e') {
				p.tabcases[i][j].d = 1;
				p.tabcases[i][j].b = 1;
				p.tabcases[i][j].g = 0;
				p.tabcases[i][j].h = 0;
			}
			if (p.tabcases[i][j].type[0] == 'b' && p.tabcases[i][j].type[1] == 's') {
				p.tabcases[i][j].g = 1;
				p.tabcases[i][j].b = 1;
				p.tabcases[i][j].h = 0;
				p.tabcases[i][j].d = 0;
			}
			if (p.tabcases[i][j].type[0] == 'b' && p.tabcases[i][j].type[1] == 'o') {
				p.tabcases[i][j].h = 1;
				p.tabcases[i][j].g = 1;
				p.tabcases[i][j].b = 0;
				p.tabcases[i][j].d = 0;
			}
			if (p.tabcases[i][j].type[0] == 'c' && p.tabcases[i][j].type[1] == 'n') {
				p.tabcases[i][j].h = 1;
				p.tabcases[i][j].b = 1;
				p.tabcases[i][j].d = 1;
				p.tabcases[i][j].g = 0;
			}
			if (p.tabcases[i][j].type[0] == 'c' && p.tabcases[i][j].type[1] == 'e') {
				p.tabcases[i][j].d = 1;
				p.tabcases[i][j].b = 1;
				p.tabcases[i][j].g = 1;
				p.tabcases[i][j].h = 0;
			}
			if (p.tabcases[i][j].type[0] == 'c' && p.tabcases[i][j].type[1] == 's') {
				p.tabcases[i][j].h = 1;
				p.tabcases[i][j].b = 1;
				p.tabcases[i][j].g = 1;
				p.tabcases[i][j].d = 0;
			}
			if (p.tabcases[i][j].type[0] == 'c' && p.tabcases[i][j].type[1] == 'o') {
				p.tabcases[i][j].h = 1;
				p.tabcases[i][j].d = 1;
				p.tabcases[i][j].g = 1;
				p.tabcases[i][j].b = 0;
			}
		}
	}
	//case temporaire
	if (p.case_tmp.type[0] == 'a' && p.case_tmp.type[1] == 'n') {
		p.case_tmp.h = 1;
		p.case_tmp.b = 1;
		p.case_tmp.g = 0;
		p.case_tmp.d = 0;
	}
	if (p.case_tmp.type[0] == 'a' && p.case_tmp.type[1] == 'e') {
		p.case_tmp.d = 1;
		p.case_tmp.g = 1;
		p.case_tmp.h = 0;
		p.case_tmp.b = 0;
	}
	if (p.case_tmp.type[0] == 'a' && p.case_tmp.type[1] == 's') {
		p.case_tmp.h = 1;
		p.case_tmp.b = 1;
		p.case_tmp.g = 0;
		p.case_tmp.d = 0;
	}
	if (p.case_tmp.type[0] == 'a' && p.case_tmp.type[1] == 'o') {
		p.case_tmp.d = 1;
		p.case_tmp.g = 1;
		p.case_tmp.h = 0;
		p.case_tmp.b = 0;
	}
	if (p.case_tmp.type[0] == 'b' && p.case_tmp.type[1] == 'n') {
		p.case_tmp.h = 1;
		p.case_tmp.d = 1;
		p.case_tmp.b = 0;
		p.case_tmp.g = 0;
	}
	if (p.case_tmp.type[0] == 'b' && p.case_tmp.type[1] == 'e') {
		p.case_tmp.d = 1;
		p.case_tmp.b = 1;
		p.case_tmp.g = 0;
		p.case_tmp.h = 0;
	}
	if (p.case_tmp.type[0] == 'b' && p.case_tmp.type[1] == 's') {
		p.case_tmp.g = 1;
		p.case_tmp.b = 1;
		p.case_tmp.h = 0;
		p.case_tmp.d = 0;
	}
	if (p.case_tmp.type[0] == 'b' && p.case_tmp.type[1] == 'o') {
		p.case_tmp.h = 1;
		p.case_tmp.g = 1;
		p.case_tmp.b = 0;
		p.case_tmp.d = 0;
	}
	if (p.case_tmp.type[0] == 'c' && p.case_tmp.type[1] == 'n') {
		p.case_tmp.h = 1;
		p.case_tmp.b = 1;
		p.case_tmp.d = 1;
		p.case_tmp.g = 0;
	}
	if (p.case_tmp.type[0] == 'c' && p.case_tmp.type[1] == 'e') {
		p.case_tmp.d = 1;
		p.case_tmp.b = 1;
		p.case_tmp.g = 1;
		p.case_tmp.h = 0;
	}
	if (p.case_tmp.type[0] == 'c' && p.case_tmp.type[1] == 's') {
		p.case_tmp.h = 1;
		p.case_tmp.b = 1;
		p.case_tmp.g = 1;
		p.case_tmp.d = 0;
	}
	if (p.case_tmp.type[0] == 'c' && p.case_tmp.type[1] == 'o') {
		p.case_tmp.h = 1;
		p.case_tmp.d = 1;
		p.case_tmp.g = 1;
		p.case_tmp.b = 0;
	}

	return p;
}
