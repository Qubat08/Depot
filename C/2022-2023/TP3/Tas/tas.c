#include "tas.h"

void initialiser_tas(tas *t, arete **tabArete, int max, int taille)
{
    int cpt = 0, i = 0, j = 0;
    t->longueur = max;
    t->tab = (arete **)malloc(max * sizeof(arete *));
}

void afficher_tas(tas t)
{
    for (int i = 0; i < t.longueur; i++)
    {
        if (t.tab[i] != NULL)
        {
            afficherArete(t.tab[i]);
        }
    }
}

int getIndiceParent(int i)
{
    return (int)(i - 1) / 2;
}

int getIndiceFilsDroit(int i)
{
    return 2 * i + 2;
}
int getIndiceFilsGauche(int i)
{
    return 2 * i + 1;
}

void entasser_max(tas *t, int i)
{
    if (i < t->taille && i > 0)
    {
        int g = getIndiceFilsGauche(i);
        int d = getIndiceFilsDroit(i);
        int max = -1;
        if (g < t->taille && t->tab[g]->poids > t->tab[i]->poids)
        {
            max = g;
        }
        if (d < t->taille && t->tab[d]->poids > max)
        {
            max = d;
        }
        if (max != i)
        {
            echanger(t->tab[i], t->tab[max]);
            entasser_max(t, max);
        }
    }
}
void echanger(arete *a, arete *b)
{

    arete *c = (arete *)malloc(sizeof(arete));
    initialiserArete(c, a->extremetite, a->origine, a->poids);
    a->extremetite = b->extremetite;
    a->origine = b->origine;
    a->poids = b->poids;

    b->extremetite = c->extremetite;
    b->origine = c->origine;
    b->poids = c->poids;
    free(c);
}