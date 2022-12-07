#ifndef TH_H
#define TH_H

#include "LR.h"


#define MAX 10
typedef LR TH[MAX];


void TH_creer(TH* tab);
void TH_inserer(TH* tab, int k);
void TH_supprimer(TH* tab, Element2P* ptr);
Element2P* TH_rechercher(TH tab, int k);
int TH_estVide(TH* tab);
int TH_hachage(int k);



#endif