#include "Cellule.h"



void initCellule(cellule * c, int s){
    c->sommet_graphe = s;
    c->prec = NULL;
    c->succ = NULL;
}

void afficherCellule(cellule c){
    printf("%d -> ",c.sommet_graphe);
}