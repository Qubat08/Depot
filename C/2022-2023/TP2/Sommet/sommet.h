#ifndef __SOMMET_H__
#define __SOMMET_H__

typedef enum
{
    BLANC,
    GRIS,
    NOIR
} couleur;

typedef struct sommet
{
    int valeur;          // valeur du sommet
    couleur couleur;     // couleur du sommet (BLANC, GRIS, NOIR)
    int distance;        // distance du sommet par rapport au sommet d'origine
    struct sommet *pere; // père du sommet dans l'arbre de parcours
    int d;               // date de découverte
    int f;               // date de fin
} sommet;

sommet *initialiser_sommet(int valeur);
void detruire_sommet(sommet *s);

#endif // __SOMMET_H__