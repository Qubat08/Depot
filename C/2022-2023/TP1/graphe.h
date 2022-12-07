#ifndef GRAPHE_H
#define GRAPHE_H

#include "cellule.h"
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graphe{
    int nb_sommets;
    int oriente;
    int value;
    struct liste2C* l_adj;
    int * m_stockage; /* tableau de n*n sommets*/
    int ** m_adj;
}graphe;


void initGraphe(graphe* g, char* nom_file);

void afficherGraphe(graphe g);

void detruireGraphe(graphe* g);

#endif