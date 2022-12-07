#ifndef GRAPHE_H
#define GRAPHE_H

#include "../Cellule/cellule.h"
#include "../Liste/liste.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Arete/arete.h"
#include <string.h>

typedef struct graphe
{
    int nb_sommets;
    int oriente;
    int value;
    struct liste2C *l_adj;
    int *m_stockage; /* tableau de n*n sommets*/
    int **m_adj;
    arete **aretes;
    int nbaretes;
} graphe;

void initGraphe(graphe *g, char *nom_file);

void afficherGraphe(graphe g);

void detruireGraphe(graphe *g);

arete **generer_acpm_prim_tableau(graphe *, int);
int rechercheIndiceMin(int *, int *, int);

#endif