#ifndef FILE_T_H
#define FILE_T_H

#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int sommet;  // Valeur évaluée du sommet
    graphe* g;   // Pointeur vers le graphe
} element_t;

typedef struct {
    element_t *elements; // Tableau dynamique pour les éléments du tas
    int capacity;   // Capacité maximale du tas
    int size;       // Nombre actuel d'éléments dans le tas
} Tas_t;

// Déclarations de fonctions
void initTas(Tas_t *, int );
void entasser_min(Tas_t *, int );
void echanger(element_t *, element_t *);
void insererElement(Tas_t *, element_t );
int getIndiceParent(int );
int getIndiceFilsDroit(int );
int getIndiceFilsGauche(int );
element_t extraire_min(Tas_t *);
void detruireTas(Tas_t *);
void afficherTas(Tas_t *);

#endif // FILE_T_H
