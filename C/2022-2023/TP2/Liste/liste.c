#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void initialiser_liste(liste *l)
{
    l->tete = NULL;
}

void inserer(liste *l, cellule *c)
{
    if (l->tete == NULL)
    {
        c->succ = NULL;
    }
    else
    {
        c->succ = l->tete;
        l->tete->pred = c;
    }
    c->pred = NULL;
    l->tete = c;
}

void afficher_liste(liste l)
{

    if (l.tete == NULL)
    {
        printf("Liste vide\n");
    }
    else
    {
        cellule *c = l.tete;
        while (c != NULL)
        {
            printf("%d -> ", c->sommet);
            c = c->succ;
        }
        printf("NULL\n");
    }
}

cellule *rechercher(liste l, int sommet)
{
    cellule *c = l.tete;
    if (l.tete == NULL)
    {
        printf("liste vide\n");
    }
    else
    {
        while (c != NULL && c->sommet != sommet)
        {
            c = c->succ;
        }
    }
    return c;
}

void supprimer(cellule *c, liste *l)
{
    if (c != NULL)
    {
        if (c->pred != NULL)
        {
            c->pred->succ = c->succ;
        }
        else
        {
            l->tete = c->succ;
        }
        if (c->succ != NULL)
        {
            c->succ->pred = c->pred;
        }
        else
        {
            l->tete = c->pred;
        }
        free(c);
    }
    else
    {
        printf("cellule non existante\n");
    }
}

void detruire_liste(liste *l)
{
    while (l->tete != NULL)
    {
        supprimer(l->tete, l);
    }
}