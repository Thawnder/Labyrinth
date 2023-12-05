#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/structures.h"
#include "../include/afficher.h"
#include "../include/joueurs.h"

void afficher_plateau(plateau p) {
	afficher_lignes(p);
	afficher_case_tmp(p.case_tmp);
}

void afficher_case_tmp(Case casetmp) {
	printf("Case remplaçable:\n");
	for (int i = 1; i < 4; i++) {//on affiche chacune des 3 lignes de la case
		afficher_case(casetmp, i);
		printf("\n");
	}
}

void afficher_lignes(plateau p) {
	printf("           7         8         9       \n");
	printf("           |         |         |       \n");
	printf("           v         v         v       \n");
	for (int i = 1; i < 8; i++) {
		afficher_ligne(i, p);
	}
	printf("           ^         ^         ^       \n");
	printf("           |         |         |       \n");
	printf("           10        11        12      \n");
}

void afficher_ligne(int numl, plateau p) {
	for (int i = 1; i < 4; i++) {
		if (numl % 2 == 0 && i == 2) { printf("%d-> ", numl / 2); }
		else { printf("    "); }
		for (int j = 1; j < 8; j++) {
			afficher_case(p.tabcases[numl][j], i);
		}
		if (numl % 2 == 0 && i == 2) { printf(" <-%d\n", (numl / 2) + 3); }
		else { printf("    \n"); }
	}
}

void afficher_case(Case c, int num) {
	if (num == 1) {
		if ((c.type[0] == 'a' && c.type[1] == 'n') || (c.type[0] == 'b' && c.type[1] == 'n') || (c.type[0] == 'c' && c.type[1] == 'n') || (c.type[0] == 'a' && c.type[1] == 's') || (c.type[0] == 'c' && c.type[1] == 's') || (c.type[0] == 'b' && c.type[1] == 'o') || (c.type[0] == 'c' && c.type[1] == 'o')) {
			printf("┌─╥─┐");
		}
		else {
			printf("┌───┐");
		}
	}
	else if (num == 2) {
		if ((c.type[0] == 'a' && c.type[1] == 'n') || (c.type[0] == 'a' && c.type[1] == 's')) {
			printf("│ ║ │");
		}
		else if (c.type[0] == 'b' && c.type[1] == 'n') {
			printf("│ ╚═╡");
		}
		else if (c.type[0] == 'c' && c.type[1] == 'n') {
			printf("│ ╠═╡");
		}
		else if ((c.type[0] == 'a' && c.type[1] == 'e') || (c.type[0] == 'a' && c.type[1] == 'o')) {
			printf("╞═══╡");
		}
		else if (c.type[0] == 'b' && c.type[1] == 'e') {
			printf("│ ╔═╡");
		}
		else if (c.type[0] == 'c' && c.type[1] == 'e') {
			printf("╞═╦═╡");
		}
		else if (c.type[0] == 'b' && c.type[1] == 's') {
			printf("╞═╗ │");
		}
		else if (c.type[0] == 'c' && c.type[1] == 's') {
			printf("╞═╣ │");
		}
		else if (c.type[0] == 'b' && c.type[1] == 'o') {
			printf("╞═╝ │");
		}
		else if (c.type[0] == 'c' && c.type[1] == 'o') {
			printf("╞═╩═╡");
		}
		else { printf("   "); }
	}
	else {
		if ((c.type[0] == 'a' && c.type[1] == 'n') || (c.type[0] == 'c' && c.type[1] == 'n') || (c.type[0] == 'b' && c.type[1] == 'e') || (c.type[0] == 'c' && c.type[1] == 'e') || (c.type[0] == 'a' && c.type[1] == 's') || (c.type[0] == 'b' && c.type[1] == 's') || (c.type[0] == 'c' && c.type[1] == 's')) {
			printf("└─╨─┘");
		}
		else {
			printf("└───┘");
		}
	}
}

void afficher_liste_tresors() {
	int j = 24 / nbrj;
	for (int i = 0; i < nbrj; i++) {
		printf("Trésors restants pour %s:\n", tableaujoueurs[i].pseudo);
		j = tableaujoueurs[i].nbrtreres - 1;
		while (j >= 0) {
			printf("%d. %s\n", tableaujoueurs[i].listetresors[j].numero - (i * 24 / nbrj) + 1, tableaujoueurs[i].listetresors[j].nom);
			j--;
		}
	}
}