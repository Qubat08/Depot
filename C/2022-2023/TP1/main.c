#include <stdio.h>
#include <stdlib.h>

#include "liste.h"
#include "cellule.h"
#include "graphe.h"



int main(void){

    /* int i = 0, cpt = 0;

    // liste2C l;

    // initListe(&l);
    // printf("Saisir nombre de sommets : ");
    // scanf("%d",&cpt);

    // for (i=0;i<cpt;i++){
    //     cellule* c = (cellule*)malloc(sizeof(cellule));
    //     initCellule(c,i);
    //     inserer_liste(&l, c);
    //     afficherListe(l);
    // }
    //     viderListe(&l);
    // afficherListe(l); */

    graphe graphe;
    initGraphe(&graphe,"graphe2.txt");
    afficherGraphe(graphe);
    detruireGraphe(&graphe);
    afficherGraphe(graphe);

    return 0;
}