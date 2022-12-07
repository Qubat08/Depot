#ifndef __CELLULE_H__
#define __CELLULE_H__

typedef struct cellule
{
    int sommet;
    struct cellule *pred;
    struct cellule *succ;
} cellule;

void initialiser_cellule(cellule *c, int sommet);

#endif // __CELLULE_H__