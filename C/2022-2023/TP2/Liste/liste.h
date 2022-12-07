#ifndef __LISTE_H__
#define __LISTE_H__
#include "../Cellule/cellule.h"

typedef struct liste
{
    struct cellule *tete;
} liste;

void initialiser_liste(liste *l);
void detruire_liste(liste *l);
void inserer(liste *l, cellule *c);
void afficher_liste(liste l);
cellule *rechercher(liste l, int sommet);
void supprimer(cellule *c, liste *l);

#endif // __LISTE_H__