#ifndef CELLULE_H
#define CELLULE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct cellule
{
    int sommet_graphe;
    struct cellule *succ;
    struct cellule *prec;
    int poids;
} cellule;

void initCellule(cellule *c, int s, int p);
void afficherCellule(cellule c);

#endif