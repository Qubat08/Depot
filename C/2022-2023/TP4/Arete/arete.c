#include "arete.h"

void initialiserArete(arete *a, int o, int e, int p)
{
    a->extremetite = e;
    a->origine = o;
    a->poids = p;
}

void afficherArete(arete *a)
{
    if (a != NULL)
        printf("(%d,%d) : %d \n", a->origine, a->extremetite, a->poids);
}