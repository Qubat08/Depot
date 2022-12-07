#ifndef LR_H
#define LR_H

typedef struct Element2P{
	int cle;
	struct Element2P* prec;
	struct Element2P* succ;
}Element2P;

typedef Element2P* LR; 

void LR_creer(LR* x);
void LR_inserer(LR* x, int k);
void LR_supprimer(LR* x, Element2P* ptr);
int LR_estVide(LR* x);
Element2P* LR_rechercher(LR x, int k);
int test (LR* x);
void afficher(LR x);
void vider(LR* x);
#endif