#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"

void initialiser_cellule(cellule *c, int sommet)
{
    c->sommet = sommet;
    c->succ = NULL;
    c->pred = NULL;
}