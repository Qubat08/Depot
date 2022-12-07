#include "Graphe/graphe.h"
#include "Arete/arete.h"

int main(void)
{
    graphe g;
    arete **a;
    arete **b;
    int nbarrete;
    initGraphe(&g, "Graphe/graphe5.txt");
    // afficherGraphe(g);
    a = trier_aretes(&g);
    // for (int i = 0; i < g.nbaretes; i++)
    // {
    //     afficherArete(a[i]);
    // }

    b = generer_acpm_kruskal_tableau(a, g.nb_sommets, g.nbaretes);

    detruireGraphe(&g);

    return 0;
}