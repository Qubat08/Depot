#include "sommet.h"
#include <stdio.h>
#include <stdlib.h>

sommet *initialiser_sommet(int valeur)
{
    sommet *s = (sommet *)malloc(sizeof(sommet));
    s->valeur = valeur;
    s->couleur = BLANC;
    s->distance = 0;
    s->pere = NULL;
    s->d = -1;
    s->f = -1;
    return s;
}

void detruire_sommet(sommet *s)
{
    s->pere = NULL;
    s = NULL;
    free(s);
}