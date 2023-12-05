#include <stdio.h>
#include <stdlib.h>
#include "../include/joueurs.h"
#include "../include/joueurs_test.h"
#include "../include/structures.h"
#include "../unity/src/unity.h"

joueur* jtest;

void nbr_joueurs_test() {
    jtest= demander_nombre_joueurs();
    TEST_ASSERT_INT_WITHIN(1,3,nbrj);
    
}

int tmp=0;

void nbr_joueurs_humains_test() {
    demander_joueurs_humains(jtest);
    for (int i=0;i<nbrj;i++) {
        if (jtest[i].ia==1) {tmp++;}
    }
    TEST_ASSERT_LESS_OR_EQUAL_UINT (nbrj-1, tmp);
}

void numero_test() {
    for (int i=0;i<nbrj;i++) {
        TEST_ASSERT_EQUAL_UINT (i+1, jtest[i].numero);
    }
}

void nbr_d_ia_test() {
    int tmp2=0;
    for (int i=0;i<nbrj;i++) {
        if (jtest[i].ia==1) {tmp2++;}
    }
    TEST_ASSERT_EQUAL_UINT (tmp, tmp2);
} 

int mainfjoueurt(void)
{
    RUN_TEST(nbr_joueurs_test);
    RUN_TEST(nbr_joueurs_humains_test);
    RUN_TEST(numero_test);
    RUN_TEST(nbr_d_ia_test);
    return 0;
}
