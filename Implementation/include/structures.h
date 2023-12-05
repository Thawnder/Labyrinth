#ifndef STRUCTURE_H
#define STRUCTURE_H

struct tresor {
	char* nom;
	int numero;
};
typedef struct tresor tresor;

struct Case {
	int h, b, g, d, numcase, numligne, hauteur, largeur;
	char type[2];
	tresor tresor;
};
typedef struct Case Case;

struct joueur {
	char* pseudo, * couleur;
	int ia, numero, nbrtreres;
	Case c;
	tresor* listetresors;
};
typedef struct joueur joueur;

struct plateau {
	Case case_tmp;
	int ligne_tmp;
	Case tabcases[9][9];
};
typedef struct plateau plateau;

struct coupsIA {
	Case init;
	int ligne;
	char sens;
	Case dest;
	int atteint;
};
typedef struct coupsIA coupsIA;



#endif
