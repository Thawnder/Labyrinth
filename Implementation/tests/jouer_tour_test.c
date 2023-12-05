#include <stdio.h>
#include <stdlib.h>
#include "../include/joueurs.h"
#include "../include/pousser.h"
#include "../include/creerplateau.h"
#include "../include/joueurs_test.h"
#include "../include/structures.h"
#include "../unity/src/unity.h"
#include "../include/jouer_tour.h"

void trouvercaseavectresortest() {
	joueur* j = malloc(sizeof(joueur) * 2);
	plateau pt = creer_plateau(j);
	int tmp = 0;
	for (int k = 0; k < 24; k++) {
		for (int i = 1; i <= 7; i++) {
			for (int l = 1; l <= 7; l++) {
				if (k < 12) {
					if (j[0].listetresors[k].numero == pt.tabcases[i][l].tresor.numero) { tmp++; }
				}
			}
		}
	}
	TEST_ASSERT_EQUAL_INT(24, tmp);
	free(j);
}

void casecompatibletest() {
	joueur* j = malloc(sizeof(joueur) * 2);
	plateau pt = creer_plateau(j);
	if ((pt.tabcases[2][1].type[0] == 'a' && (pt.tabcases[2][1].type[1] == 'e' || pt.tabcases[2][1].type[1] == 'o')) || (pt.tabcases[2][1].type[0] == 'b' && (pt.tabcases[2][1].type[1] == 'e' || pt.tabcases[2][1].type[1] == 'n')) || (pt.tabcases[2][1].type[0] == 'c' && (pt.tabcases[2][1].type[1] == 'e' || pt.tabcases[2][1].type[1] == 'o' || pt.tabcases[2][1].type[1] == 'n'))) {
		TEST_ASSERT_EQUAL_INT(1, case_compatible(pt.tabcases[2][1], pt.tabcases[2][2], 'd'));
	}
	else {
		TEST_ASSERT_EQUAL_INT(0, case_compatible(pt.tabcases[2][1], pt.tabcases[2][2], 'd'));
	}
	free(j);
}



int mainfjouer_tourt(void)
{
	RUN_TEST(trouvercaseavectresortest);
	RUN_TEST(casecompatibletest);
	return 0;
}