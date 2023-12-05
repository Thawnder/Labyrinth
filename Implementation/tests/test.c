#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/joueurs.h"
#include "../include/structures.h"
#include "../include/victoire.h"
#include "../include/joueurs_test.h"
#include "../include/victoire_test.h"
#include "../include/pousser_test.h"
#include "../include/creerplateau_test.h"
#include "../include/distribuer_test.h"
#include "../include/jouer_tour_test.h"
#include "../unity/src/unity.h"

void setUp() {}

void tearDown() {}

int main(void) {
    UNITY_BEGIN();
    mainfjoueurt();
    mainfvictoiret();
    mainfpoussert();
    mainfcreer_plateaut();
    mainfjouer_tourt();
    mainfdistribuert();
    return UNITY_END();
    return 0;
}
