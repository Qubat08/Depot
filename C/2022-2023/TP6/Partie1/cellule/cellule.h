#ifndef CELLULE_H
#define CELLULE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule
{
    char valeur[27];
    struct cellule *succ;
    struct cellule *prec;
} cellule;

void initCellule(cellule *, char *);
void afficherCellule(cellule);

#endif