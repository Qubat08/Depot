#ifndef TABLE_DE_HACHAGE
#define TABLE_DE_HACHAGE

#include <stdio.h>
#include <stdlib.h>

#include "../liste/liste.h"

#define MAX 11
typedef liste2C TH[MAX];

void initialiser_TH(TH *);
void detruire_TH(TH *);
void afficher_TH(TH);

unsigned long long convertir_ch_long(char *);
int hachage(unsigned long long);
cellule *rechercher_hachage(char *, TH);
void inserer_TH(TH *, cellule *);
void supprimer_hachage(cellule *, TH *);

int compter_TH(TH);

#endif