#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/victoire.h"
#include "../include/victoire_test.h"
#include "../include/structures.h"
#include "../unity/src/unity.h"

joueur j;

void case_depart_test() {
    int tmp = case_depart(j);
    TEST_ASSERT_EQUAL_UINT(0, tmp);
    tmp++;
}

int mainfvictoiret(void)
{
    RUN_TEST(case_depart_test);
    return 0;
}
