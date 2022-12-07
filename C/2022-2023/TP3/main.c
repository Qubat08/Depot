#include "Graphe/graphe.h"
#include "Tas/tas.h"
#include "Arete/arete.h"
#include <stdio.h>

int main(void)
{

    graphe g;
    arete **a;
    arete *b;
    tas t;
    int nbarretes = 0, parent = -1;
    initGraphe(&g, "Graphe/graphe5.txt");

    // afficherGraphe(g);

    a = g.aretes;
    nbarretes = getNbArretes(g);
    // afficherGraphe(g);

    initialiser_tas(&t, a, 50, nbarretes);
    afficher_tas(t);

    entasser_max(&t, 1);
    printf("\n \n \n");

    afficher_tas(t);

    detruireGraphe(&g);

    return 0;
}