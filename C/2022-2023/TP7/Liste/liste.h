#ifndef LISTE2C_H
#define LISTE2C_H

#include "../Cellule/cellule.h"
#include <stdio.h>
typedef struct liste2C
{
	struct cellule *tete;
} liste2C;

void initListe(liste2C *l);
void inserer_liste(liste2C *l, cellule *temp);
void supprimer_liste2C(liste2C *l, cellule *x);
int ListeVide(liste2C x);

cellule *liste_Rechercher(liste2C x, int k);
void afficherListe(liste2C x);
void viderListe(liste2C *x);

#endif