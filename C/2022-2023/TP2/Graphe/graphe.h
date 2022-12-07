#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include "../Liste/liste.h"
#include "../FileTab/fileTab.h"
#include "../PileTab/pileTab.h"
#include "../Sommet/sommet.h"

typedef struct graphe
{
    int n_sommet;
    int oriente;
    int valeur;
    liste *liste_adj;
    int **m_adj;
    int *m_stockage;
    sommet *tableau_sommet;
} graphe;

void intisaliser_graphe(graphe *g, char *NomDuFichier);
void afficher_graphe(graphe g);
void detruire_graphe(graphe *g);
void parcours_largeur(graphe *g, int s);
void afficher_chemin(graphe g, int s);
void chemin_recursif(graphe g, int s, int i);
void information_sommet(graphe g);
void parcours_profondeur(graphe *g, int s);
void parcours_profondeur_recursif(graphe *g, sommet *s);
void afficher_parcours_profondeur(graphe g);
void parcours_profondeur_iteratif(graphe *g, int s);

#endif // __GRAPHE_H__