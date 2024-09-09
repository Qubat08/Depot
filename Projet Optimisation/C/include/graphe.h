#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include "arete.h"
#include <string.h>

typedef struct graphe
{
    int nb_sommets;
    int oriente;
    int value;
    //struct liste2C *l_adj; /*Pas utilisé ici*/
    int *m_stockage; /* tableau de n*n sommets*/
    int **m_adj;
    arete **aretes;
    int nbaretes;
    arete **solutions; /*Tableau d'aretes des solutions*/
    int poidsSolutions; /*Poids de la solution*/
} graphe;

void initGrosGraphe(graphe *g, char *nom_file);


void initGraphe(graphe *g, char *nom_file);

void afficherGraphe(graphe g);

void detruireGraphe(graphe *g);
arete **trier_aretes(graphe *g);
int getNbArretes(graphe);
arete **generer_acpm_kruskal_tableau(arete **, int, int);
arete **generer_acpm_kruskal_sans_0_tableau(arete **, int, int);

arete** ajoutareteavec0(arete **,arete **, int, int);

int estFini(int[], int);
int calculBorneInitiale(graphe, int);
int estHamiltonien(arete**, int);
int* trouverLeSommetDegreSup2(arete** , int );
int trouverIndiceSommetDegreSup2(int*, int);
arete*** areteIncidente(arete** , int, int, int);
void fonctionEvaluation(graphe *, int);
void evaluerRacine(graphe *, int);

void bloquerArete(graphe*, arete*);
void debloquerArete(graphe*, arete*);

graphe *copieGraphe(graphe *);

#endif