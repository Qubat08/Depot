#include <stdio.h>
#include <stdlib.h>
#include "TH.h"
#include "LR.h"


int TH_hachage(int k){
	return k%MAX;
}

void TH_creer(TH* tab){
	for (int i = 0; i<MAX; i++){
		LR_creer(&((*tab)[i]));
	} 
}

int TH_estVide(TH* tab){
	int i =0;
	while (i<MAX && !LR_estVide(&((*tab)[i]))){
		i++;
	}
	return i==MAX;
}

Element2P* TH_rechercher(TH tab, int k){
	return LR_rechercher(tab[TH_hachage(k)],k);
}

void TH_inserer(TH* tab, int k){
	int i = TH_hachage(k);
	LR_inserer((&(*tab)[i]),k);
}

void TH_supprimer(TH* tab, Element2P* ptr){
	if(ptr !=NULL){
	int i = TH_hachage(ptr->cle);

	LR_supprimer(&((*tab)[i]),ptr);
	}
}