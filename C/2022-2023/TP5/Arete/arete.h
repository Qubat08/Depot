#ifndef ARETE_H
#define ARETE_H
#include <stdio.h>
typedef struct arete
{
    int origine;
    int extremite;
    int poids;
} arete;

void initialiserArete(arete *, int, int, int);
void afficherArete(arete *);
#endif