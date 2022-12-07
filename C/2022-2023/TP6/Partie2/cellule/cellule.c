#include "cellule.h"

void initCellule(cellule *c, char *s)
{
    c->prec = NULL;
    c->succ = NULL;

    strcpy(c->valeur, s);
}

void afficherCellule(cellule c)
{
    printf(" %s ->", c.valeur);
}