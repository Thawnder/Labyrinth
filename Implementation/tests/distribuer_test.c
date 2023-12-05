#include <stdio.h>
#include <stdlib.h>
#include "../include/joueurs.h"
#include "../include/pousser.h"
#include "../include/creerplateau.h"
#include "../include/joueurs_test.h"
#include "../include/structures.h"
#include "../unity/src/unity.h"


void tritabaleatest() {
	int* t = tritabalea(34);
	TEST_ASSERT_NULL(t);
}

void inittresorstest() {
	tresor* t = inittresors();
	TEST_ASSERT_NULL(t);
}

int mainfdistribuert(void)
{
	RUN_TEST(tritabaleatest);
	RUN_TEST(inittresorstest);
	return 0;
}