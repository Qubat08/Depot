#include "file.h"

void initTas(Tas_t *t, int capacite) {
    t->capacity = capacite;
    t->size = 0;
    t->elements = (element_t *)malloc(capacite * sizeof(element_t));
}

void insererElement(Tas_t *t, element_t e) {
    if (t->size == t->capacity) {
        return; // Tas plein, gestion d'erreur ou agrandissement nécessaire
    }
    t->elements[t->size] = e;
    int current = t->size;
    t->size++;
    while (current != 0 && t->elements[getIndiceParent(current)].sommet > t->elements[current].sommet) {
        echanger(&t->elements[current], &t->elements[getIndiceParent(current)]);
        current = getIndiceParent(current);
    }
}

void echanger(element_t *a, element_t *b) {
    element_t temp = *a;
    *a = *b;
    *b = temp;
}

int getIndiceParent(int i) {
    return (i - 1) / 2;
}

int getIndiceFilsDroit(int i) {
    return 2 * i + 2;
}

int getIndiceFilsGauche(int i) {
    return 2 * i + 1;
}

void entasser_min(Tas_t *t, int i) {
    int g = getIndiceFilsGauche(i);
    int d = getIndiceFilsDroit(i);
    int min = i;
    if (g < t->size && t->elements[g].sommet < t->elements[i].sommet) {
        min = g;
    }
    if (d < t->size && t->elements[d].sommet < t->elements[min].sommet) {
        min = d;
    }
    if (min != i) {
        echanger(&t->elements[i], &t->elements[min]);
        entasser_min(t, min);
    }
}


element_t extraire_min(Tas_t *t) {
    if (t->size == 0) {
        fprintf(stderr, "Erreur : le tas est vide.\n");
        return (element_t){-1, NULL}; // Retourner un élément d'erreur, ajuster selon le besoin
    }
    element_t minElement = t->elements[0]; // L'élément à la racine du tas
    t->elements[0] = t->elements[t->size - 1]; // Déplace le dernier élément à la racine
    t->size--; // Réduit la taille du tas
    entasser_min(t, 0); // Rétablit la propriété du tas min
    
    return minElement; // Retourne l'élément minimum
}

void detruireTas(Tas_t *t) {
    if (t->elements != NULL) {
        for (int i = 0; i < t->size; i++) {
            if (t->elements[i].g != NULL)
            detruireGraphe(t->elements[i].g); 
        }
        free(t->elements);
        t->elements = NULL; 
    }
    t->size = 0;
    t->capacity = 0;
    free(t);
}

void afficherTas(Tas_t *t) {
    for (int i = 0; i < t->size; i++) {
        printf("%d ", t->elements[i].sommet);
    }
    printf("\n");
}
