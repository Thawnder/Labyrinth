#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/creerplateau.h"
#include "../include/distribuer.h"
#include "../include/structures.h"
#include "../include/joueurs.h"
#include "../unity/src/unity.h"

joueur* j;
plateau pt;

void placertresorstest() {
	j= (joueur*)malloc(sizeof(joueur) * 2);
	pt = creer_plateau(j);
	pt = placer_tresors(pt, j);
	int tmp = 0;
	for (int i = 1; i <= 7; i++) {
		for (int k = 1; k <= 7; k++) {
			for (int l = 0; l < 12; l++) {
				if (j[0].listetresors[l].numero == pt.tabcases[i][l].tresor.numero) { tmp++; }
			}
			for (int l = 0; l < 12; l++) {
				if (j[1].listetresors[l].numero == pt.tabcases[i][l].tresor.numero) { tmp++; }
			}
		}
		
	}
	TEST_ASSERT_EQUAL_INT(24, tmp);
}

void transformertabtest() {
	int* t = tritabalea(34);
	int* tab = transformertab(t, pt);
	int tmp = 0;
	for (int i = 0; i < 49; i++) {
		if (tab[i] == 0 || tab[i] == 2 || tab[i] == 4 || tab[i] == 6 || tab[i] == 14 || tab[i] == 16 || tab[i] == 18 || tab[i] == 20 || tab[i] == 28 || tab[i] == 30) {
			tmp = 1;
		}
	}
	TEST_ASSERT_EQUAL_INT(0, tmp);
}

void orientationaleatest() {
	char tmp;
	int tmp2 = 0;
	for (int i = 0; i < 50; i++) {
		tmp = orientationalea();
		if (tmp != 'h' && tmp != 'g' && tmp != 'd' && tmp != 'b') { tmp2 = 1; }
	}
	TEST_ASSERT_EQUAL_INT(0, tmp2);

}

void assignationindicescasestest() {
	for (int i = 1; i <= 7; i++) {
		for (int j = 1; j <= 7; j++) {
			TEST_ASSERT_EQUAL_INT(i, pt.tabcases[i][j].hauteur);
			TEST_ASSERT_EQUAL_INT(j, pt.tabcases[i][j].largeur);
		}
	}
}



int mainfcreer_plateaut(void)
{
	RUN_TEST(placertresorstest);
	RUN_TEST(transformertabtest);
	RUN_TEST(orientationaleatest);
	RUN_TEST(assignationindicescasestest);
	return 0;
}