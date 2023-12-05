#include <stdio.h>
#include <stdlib.h>
#include "../include/joueurs.h"
#include "../include/pousser.h"
#include "../include/creerplateau.h"
#include "../include/joueurs_test.h"
#include "../include/structures.h"
#include "../unity/src/unity.h"

void pousser_rangee_test() {
	joueur* j = malloc(sizeof(joueur) * 2);
	plateau pt = creer_plateau(j);
	pt = pousser_rangee(1, pt, j, 'n');
	for (int i = 7; i <= 12; i++) {
		TEST_ASSERT_EQUAL_INT(i, pt.tabcases[1][i-6].numcase);
	}
	pt = creer_plateau(j);
	pt = pousser_rangee(4, pt, j, 'n');
	for (int i = 13; i >= 8; i--) {
		TEST_ASSERT_EQUAL_INT(i, pt.tabcases[1][i - 7].numcase);
	}
	pt = creer_plateau(j);
	pt = pousser_rangee(7, pt, j, 'n');
	for (int i = 1; i <=36; i=i+7) {
		TEST_ASSERT_EQUAL_INT(i, pt.tabcases[(i/7) +1][1].numcase);
	}
	pt = creer_plateau(j);
	pt = pousser_rangee(10, pt, j, 'n');
	for (int i = 43; i >= 8; i=i-7) {
		TEST_ASSERT_EQUAL_INT(i, pt.tabcases[(i / 7) + 1][1].numcase);
	}
	TEST_ASSERT_EQUAL_INT(0, est_elle_decalable(10, pt));
}

int mainfpoussert(void)
{
	RUN_TEST(pousser_rangee_test);
	return 0;
}