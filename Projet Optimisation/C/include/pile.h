#ifndef PILE_H
#define PILE_H

#include "probleme.h"

typedef struct pile_t{
    prob_t* probleme;
    struct pile_t* suivant;
} pile_t;

pile_t* creer_pile();
int pile_vide(pile_t*);
void empiler(pile_t**, prob_t*);
prob_t* depiler(pile_t**);
void detruire_pile(pile_t**);

#endif