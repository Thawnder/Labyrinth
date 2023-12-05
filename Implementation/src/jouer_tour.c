#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/pousser.h"
#include "../include/jouer_tour.h"
#include "../include/structures.h"
#include "../include/creerplateau.h"

int tabcases[49];
int est_ce_une_ia_qui_joue = 0;

Case trouver_case_avec_tresor(plateau p, tresor t) {

	for (int i = 1; i <= 8; i++) {//on cherche le trésor sur toutes les cases du plateau
		for (int j = 1; j <= 8; j++) {
			if (p.tabcases[i][j].tresor.numero == t.numero) {
				return p.tabcases[i][j];
			}
		}
	}

	if (p.case_tmp.tresor.numero == t.numero) { return p.case_tmp; }
	printf("Erreur dans trouver_case_avec_tresor; le trésor n'a pas pu être trouvé sur le plateau.\n");
	return p.tabcases[1][1];
}

int est_on_sur_tresor(joueur j) {

	if (j.c.tresor.numero == j.listetresors[j.nbrtreres-1].numero) {//est_ce que le trésor sur lequel on est correspond au dernier dans notre liste
		return 1;
	}

	else { return 0; }
}

void tresor_suivant(joueur j) {
	j.nbrtreres--;
}


int deplacer_pion(joueur j, plateau p, Case c) {

	if (pion_deplacable(p, j.c, c) == 1) {
		return 0;
	}
	else {
		printf("Le pion ne peut pas être déplacé ici.\n");
		return -1;
	}
}

int tabcaseint = 0;
int tmp, tmp2;

int pion_deplacable(plateau p, Case c1, Case c2) {

	int a = peut_on_deplacer_ici(p, c1, c2);
	if (a == 1) {

		for (int i = 0; i < tabcaseint; i++) { //on reset tabcases et tabcaseint
			tabcases[i] = -1; 
		}
		tabcaseint = 0;
		return 1;
	}
	else {

		for (int i = 0; i < tabcaseint; i++) { 
			tabcases[i] = -1;
		}

		tabcaseint = 0;
		return 0;
	}
}


int peut_on_deplacer_ici(plateau p, Case c1, Case c2) {

	tabcases[tabcaseint] = c1.numcase;
	tabcaseint++;
	tmp2 = 0;

	for (int i = 0; i < 4; i++) {//dans chaque direction
		if (i == 0) {//haut
			if (c1.hauteur > 1) {//si on est pas au bord

				for (int j = 0; j < tabcaseint; j++) {//on regarde si on a pas déjà enregistré cette case
					if (p.tabcases[c1.hauteur - 1][c1.largeur].numcase == tabcases[j]) {
						tmp2 = 1;
					}
				}

				if (tmp2 != 1) {
					if (case_compatible(c1, p.tabcases[c1.hauteur - 1][c1.largeur], 'h') == 1) {//si on peut aller sur la case ce ce coté on relance la fonction pour la case à côté
						tmp = peut_on_deplacer_ici(p, p.tabcases[c1.hauteur - 1][c1.largeur], c2);
					}
				}

				tmp2 = 0;
			}
		}
		else if (i == 1) {//droite
			if (c1.largeur < 7) {

				for (int j = 0; j < tabcaseint; j++) {
					if (p.tabcases[c1.hauteur][c1.largeur + 1].numcase == tabcases[j]) {
						tmp2 = 1;
					}
				}

				if (tmp2 != 1) {
					if (case_compatible(c1, p.tabcases[c1.hauteur][c1.largeur + 1], 'd') == 1) {
						tmp = peut_on_deplacer_ici(p, p.tabcases[c1.hauteur][c1.largeur + 1], c2);
					}
				}

				tmp2 = 0;
			}
		}
		else if (i == 2) {//bas
			if (c1.hauteur < 7) {

				for (int j = 0; j < tabcaseint; j++) {
					if (p.tabcases[c1.hauteur + 1][c1.largeur].numcase == tabcases[j]) {
						tmp2 = 1;
					}
				}

				if (tmp2 != 1) {
					if (case_compatible(c1, p.tabcases[c1.hauteur + 1][c1.largeur], 'b') == 1) {
						tmp = peut_on_deplacer_ici(p, p.tabcases[c1.hauteur + 1][c1.largeur], c2);
					}
				}

				tmp2 = 0;
			}
		}
		else if (i == 3) {//gauche
			if (c1.largeur > 1) {

				for (int j = 0; j < tabcaseint; j++) {
					if (p.tabcases[c1.hauteur][c1.largeur - 1].numcase == tabcases[j]) {
						tmp2 = 1;
					}
				}
				if (tmp2 != 1) {
					if (case_compatible(c1, p.tabcases[c1.hauteur][c1.largeur - 1], 'g') == 1) {
						tmp = peut_on_deplacer_ici(p, p.tabcases[c1.hauteur][c1.largeur - 1], c2);
					}
				}

				tmp2 = 0;
			}
		}
	}
	tmp = 0;

	for (int i = 0; i <= tabcaseint; i++) {
		if (c2.numcase == tabcases[i]) {
			tmp = 1;
		}
	}

	return tmp;
}

Case case_proche_tresor(plateau p, Case c1, tresor t) {
	int x = 1;
	int y = 0;
	int cptr1 = 1;
	int cptr2 = 1;

	for (int i = 1; i < 8; i++) {
		for (int j = 1; j < 8; j++) {

			if (p.tabcases[i][j].tresor.numero == t.numero) {

				if (pion_deplacable(p, c1, p.tabcases[i][j]) == 1) {
					return p.tabcases[i][j];
				}
				else {

					while (cptr1 < 13) {

						if (pion_deplacable(p, c1, p.tabcases[i][j]) == 1)
							return p.tabcases[i][j];

						if (i - x > 0 && j - y > 0) {
							if (pion_deplacable(p, c1, p.tabcases[i - x][j - y]) == 1)
								return p.tabcases[i - x][j - y];
						}

						if (i - y > 0 && j - x > 0) {
							if (pion_deplacable(p, c1, p.tabcases[i - y][j - x]) == 1)
								return p.tabcases[i - y][j - x];
						}

						if (i + x < 8 && j + y < 8) {
							if (pion_deplacable(p, c1, p.tabcases[i + x][j + y]) == 1)
								return p.tabcases[i + x][j + y];
						}

						if (i + y < 8 && j + x < 8) {
							if (pion_deplacable(p, c1, p.tabcases[i + y][j + x]) == 1)
								return p.tabcases[i + y][j + x];
						}

						if (i - x > 0 && j + y < 8) {
							if (pion_deplacable(p, c1, p.tabcases[i - x][j + y]) == 1)
								return p.tabcases[i - x][j + y];
						}

						if (i + y < 8 && j - x>0) {
							if (pion_deplacable(p, c1, p.tabcases[i + y][j - x]) == 1)
								return p.tabcases[i + y][j - x];
						}

						if (i + x < 8 && j - y>0) {
							if (pion_deplacable(p, c1, p.tabcases[i + x][j - y]) == 1)
								return p.tabcases[i + x][j - y];
						}

						if (i - y > 0 && j + x < 8) {
							if (pion_deplacable(p, c1, p.tabcases[i - y][j + x]) == 1)
								return p.tabcases[i - y][j + x];
						}

						if (cptr2 != cptr1) {
							x--;
							y++;
							cptr2++;
						}
						else {
							cptr1++;
							x = cptr1;
							cptr2 = 1;
							y = 0;
						}
					}
				}
			}
		}
	}
	return c1;
}



int case_compatible(Case c1, Case c2, char orientation) {

	if (orientation == 'h') {//on regarde si il y a un chemin

		if (c1.h == 1 && c2.b == 1) {
			return 1;
		}
		else { return 0; }
	}
	else if (orientation == 'g') {

		if (c1.g == 1 && c2.d == 1) {
			return 1;
		}
		else { return 0; }
	}
	else if (orientation == 'd') {

		if (c1.d == 1 && c2.g == 1) {
			return 1;
		}
		else { return 0; }
	}
	else if (orientation == 'b') {

		if (c1.b == 1 && c2.h == 1) {
			return 1;
		}
		else { return 0; }
	}
	else {
		printf("Erreur case_compatible: orientation non reconnue");
		return -1;
	}
}

coupsIA analyse_coups_possibles_IA(plateau p, joueur j, tresor t, joueur* joupt) {

	est_ce_une_ia_qui_joue = 1;
	int t1 = 0, t2 = 0, ligne, sens/*,num*/;

	joueur j_tmp;
	plateau p_tmp;
	// joueur* joupt2;
	// joueur j2;
	coupsIA tabcoupsT1[48];
	coupsIA tabcoupsT2[48];
	// coupsIA coupAdv[nbrj][48];

	// si on peut atteindre le trésor en un coup->on y va

	while (t1 < 48) {

		for (ligne = 1; ligne <= 12; ligne++) {
			for (sens = 0; sens < 4; sens++) {

				p_tmp = p;
				j_tmp = j;
				tabcoupsT1[t1].ligne = ligne;

				if (sens == 0)
					tabcoupsT1[t1].sens = 'n';
				else if (sens == 1)
					tabcoupsT1[t1].sens = 's';
				else if (sens == 2)
					tabcoupsT1[t1].sens = 'e';
				else if (sens == 3)
					tabcoupsT1[t1].sens = 'o';

				p_tmp = pousser_rangee(tabcoupsT1[t1].ligne, p_tmp, joupt, tabcoupsT1[t1].sens);

				tabcoupsT1[t1].init = j_tmp.c;
				tabcoupsT1[t1].dest = case_proche_tresor(p_tmp, j_tmp.c, t);

				j_tmp.c = p_tmp.tabcases[tabcoupsT1[t1].dest.hauteur][tabcoupsT1[t1].dest.largeur];

				tabcoupsT1[t1].atteint = est_on_sur_tresor(j_tmp);

				if (tabcoupsT1[t1].atteint == 1)
					return tabcoupsT1[t1];
				t1++; // Retour à la position initiale
			}
			sens = 0;
		}
	}

	// sinon si on peut en 2 coups->on fait le premier coup
	t1 = 0;
	t2 = 0;
	while (t1 < 48) {

		while (t2 < 48) {

			for (ligne = 1; ligne <= 12; ligne++) {

				for (sens = 0; sens < 4; sens++) {


					p_tmp = p;
					p_tmp = pousser_rangee(tabcoupsT1[t1].ligne, p, joupt, tabcoupsT1[t1].sens);

					j_tmp = j;
					tabcoupsT2[t2].ligne = ligne;
					if (sens == 0)
						tabcoupsT2[t2].sens = 'n';
					else if (sens == 1)
						tabcoupsT2[t2].sens = 's';
					else if (sens == 2)
						tabcoupsT2[t2].sens = 'e';
					else if (sens == 3)
						tabcoupsT2[t2].sens = 'o';

					p_tmp = pousser_rangee(tabcoupsT2[t2].ligne, p_tmp, joupt, tabcoupsT2[t2].sens);

					tabcoupsT2[t2].init = tabcoupsT1[t1].dest;
					tabcoupsT2[t2].dest = case_proche_tresor(p_tmp, j_tmp.c, t);

					j_tmp.c = p_tmp.tabcases[tabcoupsT2[t2].dest.hauteur][tabcoupsT2[t2].dest.largeur];

					tabcoupsT2[t2].atteint = est_on_sur_tresor(j_tmp);

					if (tabcoupsT2[t2].atteint == 1)
						return tabcoupsT1[t1];
					t2++; // Retour à la position initiale
				}
				sens = 0;
			}
		}
		t1++; // On change le premier coup
		t2 = 0;
	}


	// sinon on embête les autres(on refait l'algo pour les autres joueurs)

	// Non fonctionnel, car ne s'exécute pas normalement (à la fin du tour l'IA pousse la rangée 0). Et l'existence même de cet algorithme fait parfois bugger le plateau même quand on ne passe pas dans l'algo.
/*
	t1=0;
	for (num=0;num<nbrj;num++){
		printf("Analyse coups pour le joueur d'indice %d\n",num);
		if(j.numero != tableaujoueurs[num].numero){
			printf("Joueur d'indice %d n'est pas l'IA\n", num);
			j2=tableaujoueurs[num];
			joupt2=&tableaujoueurs[num];
			while (t1<48){
				for (ligne=1;ligne<=12;ligne++){
					for (sens=0;sens<4;sens++){
						printf("Analyse du coup n°%d\n",t1);

						p_tmp=p;
						j_tmp=j2;

						coupAdv[num][t1].init=j2.c;
						coupAdv[num][t1].ligne=ligne;
						if (sens==0)
							coupAdv[num][t1].sens='n';
						else if (sens==1)
							coupAdv[num][t1].sens='s';
						else if (sens==2)
							coupAdv[num][t1].sens='e';
						else if (sens==3)
							coupAdv[num][t1].sens='o';

						p_tmp=pousser_rangee(coupAdv[num][t1].ligne,p_tmp,joupt2,coupAdv[num][t1].sens);

						coupAdv[num][t1].dest = case_proche_tresor(p_tmp, j_tmp.c, j_tmp.listetresors[j_tmp.nbrtreres-1]);

						j_tmp.c = p_tmp.tabcases[coupAdv[num][t1].dest.hauteur][coupAdv[num][t1].dest.largeur];

						coupAdv[num][t1].atteint=est_on_sur_tresor(j_tmp);

						t1++; // Retour à la position initiale
					}
					sens=0;
				}
			}
		}
	}
	int test=0;
	num=0;
	t1=0;
	while (t1<48){
		printf("Comparaison des coups n°%d pour les autres joueurs\n",t1);
		if(j.numero == tableaujoueurs[num].numero){
			printf("Joueur courant donc num++\n");
			num++;
		}
		if (coupAdv[num][t1].atteint == 0){
			printf("Test est incrémenté\n");
			test++;
			num++;
			if (test == nbrj-1){	// Si le coup empêche tous les autres joueurs d'accéder au trésor, on le retourne, et l'IA se rapprochera de son trésor.
				printf("Coup trouvé\n");
				coupAdv[num][t1].dest=case_proche_tresor(p_tmp, j.c, t);
				return coupAdv[num][t1];
			}
		}
		else{
			printf("Test est remis à zéro\n");
			test=0;
			num=0;
			t1++;
		}
	}
*/
// sinon coup au hasard(ligne au hasard et orientation au hasard)

	srand(time(NULL));
	coupsIA coupRandom;
	ligne = 1 + (rand() % 12);
	coupRandom.ligne = ligne;

	sens = rand() % 4;
	if (sens == 0)
		coupRandom.sens = 'n';
	else if (sens == 1)
		coupRandom.sens = 's';
	else if (sens == 2)
		coupRandom.sens = 'e';
	else if (sens == 3)
		coupRandom.sens = 'o';

	p = pousser_rangee(coupRandom.ligne, p, joupt, coupRandom.sens);
	coupRandom.init = j.c;
	coupRandom.dest = case_proche_tresor(p, j.c, t);
	j.c = p.tabcases[coupRandom.dest.hauteur][coupRandom.dest.largeur];
	coupRandom.atteint = est_on_sur_tresor(j);


	est_ce_une_ia_qui_joue = 0;
	return coupRandom;
}