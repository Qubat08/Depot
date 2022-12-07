#include "Cellule.h"

void initCellule(cellule *c, int s, int p)
{
    c->sommet_graphe = s;
    c->prec = NULL;
    c->succ = NULL;
    c->poids = p;
}

void afficherCellule(cellule c)
{
    printf(" %d -> ", c.sommet_graphe);
}