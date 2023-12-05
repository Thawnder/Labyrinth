#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../include/distribuer.h"
#include "../include/joueurs.h"
#include "../include/victoire.h"
#include "../include/creerplateau.h"
#include "../include/jouer_tour.h"
#include "../include/afficher.h"
#include "../include/structures.h"
#include "../include/pousser.h"



int main(void) {
	srand(time(NULL));
	joueur* j = entrer_joueurs();
	j = trier_tresors(j);
	plateau p = creer_plateau(j);

	for (int i = 0; i < nbrj; i++) {//positions de départ
		if (i == 0) { j[i].c = p.tabcases[1][1]; }
		else if (i == 1) { j[i].c = p.tabcases[1][7]; }
		else if (i == 2) { j[i].c = p.tabcases[7][1]; }
		else if (i == 3) { j[i].c = p.tabcases[7][7]; }
	}

	printf("Début de la partie:\n");

	int nbrjou = 0, quoifaire = -1, quoifaire2 = -1, i1, i2, tmpdepl = 0, numligne = 0, ligneentree = 0, orientationentree = 0;
	char orientation;
	Case casetmptmp;


	while (unjoueuragagne == 0) {//boucle des tours

		quoifaire = -1;
		quoifaire2 = -1;

		if (nbrjou == nbrj) { nbrjou = 0; }//si on dépasse le nombre de joueur on revient a 0 pour faire une boucle

		if (j[nbrjou].ia == 1) {//tour d'une ia

			est_ce_une_ia_qui_joue = 1;

			printf("C'est à l'IA %s de jouer:\n", j[nbrjou].pseudo);
			printf("%s a pour objectif actuel d'atteindre le trésor %s", j[nbrjou].pseudo, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1].nom);
			printf(" qui se trouve sur la case d'indice %d,%d ", trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).hauteur, trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).largeur);
			printf("et %s se trouve actuellement sur la case d'indices %d,%d.\n", j[nbrjou].pseudo, j[nbrjou].c.hauteur, j[nbrjou].c.largeur);

			afficher_plateau(p);

			coupsIA coupIA = analyse_coups_possibles_IA(p, j[nbrjou], j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1], j);

			joueur* jtmpia = &j[nbrjou];

			j[nbrjou].c = p.tabcases[coupIA.dest.hauteur][coupIA.dest.largeur];

			p = pousser_rangee(coupIA.ligne, p, jtmpia, coupIA.sens);

			printf("L'IA %s a poussé la rangée %d, puis a déplacé son pion sur la case %d %d\n", j[nbrjou].pseudo, coupIA.ligne, coupIA.dest.hauteur, coupIA.dest.largeur);

			if (est_on_sur_tresor(j[nbrjou]) == 1) {
				printf("%s a trouvé le trésor %s", j[nbrjou].pseudo, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1].nom);
				j[nbrjou].nbrtreres--;
				printf("%s doit maintenant aller chercher le trésor %s", j[nbrjou].pseudo, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1].nom);
				printf("qui se trouve sur la case d'indice %d %d\n", trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).hauteur, trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).largeur);
				printf("Il reste désormais à %s %d trésors à trouver.\n", j[nbrjou].pseudo, j[nbrjou].nbrtreres);
			}

			est_ce_une_ia_qui_joue = 0;

		}

		else {//tour d'un.e humain.e


			printf("C'est à %s de jouer:\n", j[nbrjou].pseudo);
			printf("%s a pour objectif actuel d'atteindre le trésor %s", j[nbrjou].pseudo, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1].nom);
			printf(" qui se trouve sur la case d'indice %d,%d ", trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).hauteur, trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).largeur);
			printf("et %s se trouve actuellement sur la case d'indices %d,%d.\n", j[nbrjou].pseudo, j[nbrjou].c.hauteur, j[nbrjou].c.largeur);

			afficher_plateau(p);

			while (quoifaire != 0 && quoifaire != 1) {//on choisit si on déplace notre pion ou si on pousse directement une rangée
				printf("%s veut-il déplacer son pion(tapez 0) ou pousser une rangée(tapez 1)?\n", j[nbrjou].pseudo);
				scanf("%d", &quoifaire);
				if (quoifaire != 0 && quoifaire != 1) { printf("Erreur: veuillez choisir quoi faire en tapant 0 ou 1.\n"); }
			}

			if (quoifaire == 0) {

				while (tmpdepl == 0) {//boucle pour bouger le pion autant de fois qu'on veut

					printf("Ou voulez-vous déplacer votre pion? Rentrez les indices de la case.\n");
					scanf("%d %d", &i1, &i2);

					while (deplacer_pion(j[nbrjou], p, p.tabcases[i1][i2]) == -1) {
						printf("Rentrez à nouveau les indices:\n");
						scanf("%d %d", &i1, &i2);
					}

					j[nbrjou].c = p.tabcases[i1][i2];

					if (est_on_sur_tresor(j[nbrjou]) == 1) {
						printf("%s a trouvé le trésor %s", j[nbrjou].pseudo, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1].nom);
						j[nbrjou].nbrtreres--;
						printf("%s doit maintenant aller chercher le trésor %s", j[nbrjou].pseudo, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1].nom);
						printf("qui se trouve sur la case d'indice %d %d\n", trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).hauteur, trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).largeur);
						printf("Il reste désormais à %s %d trésors à trouver.\n", j[nbrjou].pseudo, j[nbrjou].nbrtreres);
					}

					victoire_dun_joueur(j[nbrjou]);
					printf("%s est désormais sur la case d'indice %d,%d, et le trésor qu'il doit atteindre sur la case d'indice %d,%d.\n", j[nbrjou].pseudo, j[nbrjou].c.hauteur, j[nbrjou].c.largeur, trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).hauteur, trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).largeur);
					afficher_plateau(p);
					printf("Avez-vous terminé de déplacer votre pion? Oui->1, Non->0\n");
					scanf("%d", &tmpdepl);
				}

				tmpdepl = 0;

				while (quoifaire2 != 0 && quoifaire2 != 1) {//on choisit si on veut pousser une rangée
					printf("%s veut-il pousser une ligne(tapez 0) ou non(tapez 1)?\n", j[nbrjou].pseudo);
					scanf("%d", &quoifaire2);
					if (quoifaire2 != 0 && quoifaire2 != 1) { printf("Erreur: veuillez choisir quoi faire en tapant 0 ou 1.\n"); }
				}

			}

			if (quoifaire == 1 || quoifaire2 == 0) {//on veut pousser une rangée

				while (ligneentree == 0) {//on choisit le numéro de la rangée
					printf("Entrez le numéro de la ligne que vous voulez pousser:\n");
					scanf("%d", &numligne);
					if (numligne < 1 || numligne>12) { printf("Numéro de ligne incorrect; rentrez un numéro entre 1 et 12.\n"); }
					else { ligneentree = 1; }
				}

				//on affiche la case temporaire dans les 4 sens pour montrer quelle lettre correspond à quel sens
				casetmptmp = p.case_tmp;
				casetmptmp.type[1] = 'n';
				printf("Orientation n(nord):\n");
				afficher_case_tmp(casetmptmp);
				casetmptmp.type[1] = 'e';
				printf("Orientation e(est):\n");
				afficher_case_tmp(casetmptmp);
				casetmptmp.type[1] = 's';
				printf("Orientation s(sud):\n");
				afficher_case_tmp(casetmptmp);
				casetmptmp.type[1] = 'o';
				printf("Orientation o(ouest):\n");
				afficher_case_tmp(casetmptmp);


				while (orientationentree == 0) {//on entre l'orientation
					printf("Entrez l'orientation que vous voulez attribuer à la case temporaire:\n");
					scanf(" %c", &orientation);
					if (orientation!='n' && orientation!='s' && orientation!='e' && orientation!='o') { printf("Orientation incorrecte; rentrez n, e, s ou o.\n"); }
					else { orientationentree = 1; }
				}

				joueur* jtmp = &j[nbrjou];
				p = pousser_rangee(numligne, p, jtmp, orientation); 
				

				orientationentree = 0;
				ligneentree = 0;

			}
			afficher_plateau(p);
			printf("%s est désormais sur la case d'indice %d,%d, et le trésor qu'il doit atteindre sur la case d'indice %d,%d.\n", j[nbrjou].pseudo, j[nbrjou].c.hauteur, j[nbrjou].c.largeur, trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).hauteur, trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).largeur);

			do {//on regarde si on veut déplacer notre pion ou terminer notre tour
				printf("%s veut-il déplacer son pion(tapez 0) ou terminer son tour?(tapez 1)?\n", j[nbrjou].pseudo);
				scanf("%d", &quoifaire);
				if (quoifaire != 0 && quoifaire != 1) { printf("Erreur: veuillez choisir quoi faire en tapant 0 ou 1.\n"); }
			} while (quoifaire != 0 && quoifaire != 1);

			if (quoifaire == 0) {//si on veut déplacer notre pion, idem que précedemment
				tmpdepl = 0;

				while (tmpdepl == 0) {

					printf("Ou voulez-vous déplacer votre pion? Rentrez les indices de la case.\n");
					scanf("%d %d", &i1, &i2);

					while (deplacer_pion(j[nbrjou], p, p.tabcases[i1][i2]) == -1) {
						printf("Rentrez à nouveau les indices:\n");
						scanf("%d %d", &i1, &i2);
						deplacer_pion(j[nbrjou], p, p.tabcases[i1][i2]);
					}

					j[nbrjou].c = p.tabcases[i1][i2];

					if (est_on_sur_tresor(j[nbrjou]) == 1) {
						printf("%s a trouvé le trésor %s", j[nbrjou].pseudo, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1].nom);
						j[nbrjou].nbrtreres--;
						printf("%s doit maintenant aller chercher le trésor %s ", j[nbrjou].pseudo, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1].nom);
						printf("qui se trouve sur la case d'indice %d %d\n", trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).hauteur, trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).largeur);
						printf("Il reste désormais à %s %d trésors à trouver.\n", j[nbrjou].pseudo, j[nbrjou].nbrtreres);
					}

					victoire_dun_joueur(j[nbrjou]);
					printf("%s est désormais sur la case d'indice %d,%d, et le trésor qu'il doit atteindre sur la case d'indice %d,%d.\n", j[nbrjou].pseudo, j[nbrjou].c.hauteur, j[nbrjou].c.largeur, trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).hauteur, trouver_case_avec_tresor(p, j[nbrjou].listetresors[j[nbrjou].nbrtreres - 1]).largeur);
					afficher_plateau(p);
					printf("Avez-vous terminé de déplacer votre pion? Oui->1, Non->0\n");
					scanf("%d", &tmpdepl);
				}
				tmpdepl = 0;

			}
		}
		nbrjou++;//on itère le numéro de joueur
	}

	return 0;
}