#include "pile.h"
#include <stdlib.h>

pile_t* creer_pile() {
    return NULL;
}

int pile_vide(pile_t* pile) {
    return pile == NULL;
}

void empiler(pile_t** pile, prob_t* probleme) {
    pile_t* nouveau = (pile_t*)malloc(sizeof(pile_t));
    if (nouveau == NULL) {
        return;
    }

    nouveau->probleme = probleme;
    nouveau->suivant = *pile;
    *pile = nouveau;
}

prob_t* depiler(pile_t** p) {
    if (pile_vide(*p)) {
        return NULL;
    }
    pile_t* elementSupprime = *p; 
    prob_t* probleme = elementSupprime->probleme; 
    *p = elementSupprime->suivant; 
    free(elementSupprime); 
    return probleme; 
}

void detruire_pile(pile_t** p) {
    while (!pile_vide(*p)) {
        prob_t* probleme = depiler(p);
        liberer_memoire_probleme(probleme);
    }
}