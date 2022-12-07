#include "pileTab.h"
#include <stdio.h>
#include <stdlib.h>

void initialiser_pile(pileTab *p, int taille)
{
    p->tab = (int *)malloc(taille * sizeof(int));
    if (p->tab == NULL)
    {
        return;
    }
    p->taille = taille;
    p->sommet = -1;
}

void detruire_pile(pileTab *p)
{
    p->tab = NULL;
    free(p->tab);
    p->sommet = -1;
}

int pile_pleine(pileTab p)
{
    return p.sommet == p.taille - 1;
}

int pile_vide(pileTab p)
{
    return p.sommet == -1;
}

int sommet_pile(pileTab p)
{
    return p.tab[p.sommet];
}

void empiler(pileTab *p, int valeur)
{
    if (pile_pleine(*p))
    {
        printf("Pile pleine\n");
        return;
    }
    p->sommet++;
    p->tab[p->sommet] = valeur;
}

int depiler(pileTab *p)
{
    if (pile_vide(*p))
    {
        printf("Pile vide\n");
        return -1;
    }
    int valeur = p->tab[p->sommet];
    p->sommet--;
    return valeur;
}

void afficher_pile(pileTab p)
{
    if (pile_vide(p))
    {
        printf("Pile vide\n");
        return;
    }
    while (!pile_vide(p))
    {
        printf("%d ", depiler(&p));
    }
    printf("\n");
}