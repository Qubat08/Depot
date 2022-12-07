#include "liste.h"

void initListe2C(liste2C *l)
{
    l->tete = NULL;
}

void inserer_liste(liste2C *l, char *s)
{

    cellule *c = (cellule *)malloc(sizeof(cellule));
    initCellule(c, s);

    if (l->tete == NULL)
    {
        l->tete = c;
    }
    else
    {
        if (liste_Rechercher(*l, s) == NULL)
        {
            c->succ = l->tete;
            l->tete->prec = c;
            l->tete = c;
        }
    }
}

void supprimer_liste2C(liste2C *l, cellule *x)
{
    if (x->prec != NULL)
    {
        x->prec->succ = x->succ;
    }
    else
    {
        l->tete = x->succ;
    }
    if (x->succ != NULL)
    {
        x->succ->prec = x->prec;
    }
    free(x);
}

int ListeVide(liste2C x)
{
    if (x.tete = NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

cellule *liste_Rechercher(liste2C l, char *s)
{
    cellule *temp = l.tete;
    while (temp != NULL)
    {
        if (strcmp(temp->valeur, s) == 0)
        {
            return temp;
        }
        else
        {
            temp = temp->succ;
        }
    }
    return NULL;
}

void afficherListe(liste2C x)
{
    cellule *temp = x.tete;
    if (x.tete == NULL)
    {
        printf("Liste Vide \n");
    }
    else
    {
        while (temp != NULL)
        {
            afficherCellule(*temp);
            temp = temp->succ;
        }
    }
    printf("\n");
}

void viderListe(liste2C *x)
{
    while (x->tete != NULL)
    {
        supprimer_liste2C(x, x->tete);
    }
}

void compterListe(liste2C l)
{
    cellule *temp = l.tete;
    int total = 0;
    while (temp != NULL)
    {
        total++;
        temp = temp->succ;
    }

    printf("\nMots différents: %d\n", total);
}