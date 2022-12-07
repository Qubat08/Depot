#ifndef GRAPHE_H
#define GRAPHE_H

#include "../Cellule/cellule.h"
#include "../Liste/liste.h"
#include <stdio.h>
#include <stdlib.h>
#include "../Arete/arete.h"
#include <string.h>
#include <limits.h>

typedef struct graphe
{
    int nb_sommets;
    int oriente;
    int value;
    struct liste2C *l_adj;
    int *m_stockage; /* tableau de n*n sommets*/
    int **m_adj;
    arete **aretes;
    int *distance;
    int *pred;
    int nbaretes;
} graphe;

void initGraphe(graphe *g, char *nom_file);

void afficherGraphe(graphe g);

void detruireGraphe(graphe *g);
arete **trier_aretes(graphe *g);
int getNbArretes(graphe);
arete **generer_acpm_kruskal_tableau(arete **, int, int);
int estFini(int[], int);

void bellman_ford(graphe *g, int s);
void dijsktra(graphe *g, int s);
void afficher_tab(graphe g);

int getPoids(graphe *g, int u, int v);

#endif