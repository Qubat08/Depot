#include <stdio.h>
#include <stdlib.h>
#include "Graphe/graphe.h"

int main(void)
{
    // ---------- liste ----------
    // liste l;
    // cellule c;
    // initialiser_cellule(&c, 4);
    // cellule c1;
    // initialiser_cellule(&c1, 2);

    // initialiser_liste(&l);

    // inserer(&l, &c);
    // inserer(&l, &c1);
    // afficher_liste(l);

    // supprimer(rechercher(l, 1), &l);
    // afficher_liste(l);
    // detruire_liste(&l);
    // afficher_liste(l);

    // ---------- file ----------
    // fileTab f;
    // initialiser_file(&f, 3);
    // defiler(&f);
    // printf("file vide : %d  file pleine : %d    \n", file_vide(f), file_pleine(f));
    // enfiler(&f, 1);
    // enfiler(&f, 2);
    // afficher_file(f);
    // printf("file vide : %d  file pleine : %d    \n", file_vide(f), file_pleine(f));
    // enfiler(&f, 3);
    // printf("file vide : %d  file pleine : %d    \n", file_vide(f), file_pleine(f));

    // afficher_file(f);
    // detruire_file(&f);
    // printf("file vide : %d  file pleine : %d    \n", file_vide(f), file_pleine(f));
    // afficher_file(f);

    // ---------- pile ----------
    // pileTab p;
    // initialiser_pile(&p, 3);
    // depiler(&p);
    // printf("file vide : %d  file pleine : %d    \n", pile_vide(p), pile_pleine(p));
    // empiler(&p, 1);
    // empiler(&p, 2);
    // afficher_pile(p);
    // printf("file vide : %d  file pleine : %d    \n", pile_vide(p), pile_pleine(p));
    // empiler(&p, 3);
    // printf("file vide : %d  file pleine : %d    \n", pile_vide(p), pile_pleine(p));

    // afficher_pile(p);
    // detruire_pile(&p);
    // printf("file vide : %d  file pleine : %d    \n", pile_vide(p), pile_pleine(p));
    // afficher_pile(p);

    // ---------- graphe ----------
    graphe g;
    intisaliser_graphe(&g, "Graphe/graphe2.txt");
    afficher_graphe(g);
    // detruire_graphe(&g);
    //  afficher_graphe(g);

    printf("\nParcours en largeur :\n");
    parcours_largeur(&g, 0);

    printf("\nAfficher chemin :\n");
    afficher_chemin(g, 0);

    information_sommet(g);

    printf("\nParcours profondeur recursif :\n");
    parcours_profondeur(&g, 3);
    afficher_parcours_profondeur(g);

    printf("\nParcours profondeur iteratif :\n");
    parcours_profondeur_iteratif(&g, 3);
    afficher_parcours_profondeur(g);

    return 0;
}
