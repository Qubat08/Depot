#ifndef LISTE2C_H
#define LISTE2C_H
#include "../cellule/cellule.h"
#include <stdio.h>

typedef struct liste2C
{
    struct cellule *tete;
} liste2C;

void initListe2C(liste2C *);
void inserer_liste(liste2C *, char *);
void supprimer_liste2C(liste2C *, cellule *);
int ListeVide(liste2C);

cellule *liste_Rechercher(liste2C, char *);
void afficherListe(liste2C);
void viderListe(liste2C *);

int compterListe(liste2C);

#endif