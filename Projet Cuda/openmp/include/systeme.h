#ifndef __SYSTEME_H
#define __SYSTEME_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
typedef struct systeme_t{
    int n;
    double* m; // matrice une dimension de taille n * n +1 pour stocker le resultat
    double ** matrice; // tableau de pointeurs pour acceder aux lignes de la matrice
} systeme_t ;


void systeme_init(systeme_t*);
void systeme_detruire(systeme_t*);
void systeme_afficher(systeme_t);
void systeme_lecture(systeme_t*, char*);
double* systeme_choisir_pivot(systeme_t *, int); // choisir le pivot et returner la ligne du pivot
void systeme_soustraction_lignes(systeme_t *, double*, int); // calculer la soustraction entre deux lignes
void systeme_diviser_ligne(systeme_t*, int); // diviser une ligne par un nombre
void systeme_remontee_de_gauss(systeme_t*); // remontée de gauss
void systeme_resoudre(systeme_t*, int); // résoudre le système
void systeme_echanger_lignes(systeme_t* , int, int); // échanger entre deux lignes
void systeme_output(systeme_t* , char*, int); // écrire le résultat dans un fichier

void propagation_pivot_para(systeme_t *, int, int, double);

#endif