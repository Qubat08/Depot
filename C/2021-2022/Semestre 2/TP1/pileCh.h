#ifndef PILECH_H
#define PILECH_H

#include "cellule.h"

typedef struct pilech{
	cellule* top;
}pilech;

void creerPile(pilech* pile);
void ajouterCellule(pilech* pile, element e);
void supprimerCellule(pilech* pile);
int pileVide(pilech pile);
void afficherPile(pilech pile);
#endif