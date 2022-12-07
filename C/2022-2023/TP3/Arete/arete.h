#ifndef ARETE_H
#define ARETE_H
#include <stdio.h>
typedef struct arete
{
    int origine;
    int extremetite;
    int poids;
} arete;

void initialiserArete(arete *, int, int, int);
void afficherArete(arete *);
#endif