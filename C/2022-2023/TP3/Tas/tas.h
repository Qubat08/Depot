#ifndef TAS_H
#define TAS_H

#include "../Arete/arete.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct tas
{
    arete **tab;
    int taille;
    int longueur;
} tas;

int getIndiceParent(int);
int getIndiceFilsDroit(int);
int getIndiceFilsGauche(int);

void entasser_max(tas *, int);
void initialiser_tas(tas *, arete **, int, int);
void detruire_tas(tas *);
void afficher_tas(tas);
void echanger(arete *, arete *);

#endif