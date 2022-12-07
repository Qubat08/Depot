#include "Graphe/graphe.h"
#include "Arete/arete.h"
#include <stdio.h>

int main(void)
{

    graphe g;
    arete **a;
    int somme = 0;
    int nbarretes = 0, parent = -1;
    initGraphe(&g, "Graphe/graphe5.txt");
    // afficherGraphe(g);
    for (int i = 0; i < g.nbaretes; i++)
    {
        afficherArete(g.aretes[i]);
    }
    a = generer_acpm_prim_tableau(&g, 0);
    printf("PRIM \n");
    for (int i = 0; i < g.nb_sommets - 1; i++)
    {
        afficherArete(a[i]);
        if (a[i] != NULL)
        {
            somme += a[i]->poids;
        }
    }
    printf("\n Poids: %d \n", somme);

    detruireGraphe(&g);

    return 0;
}