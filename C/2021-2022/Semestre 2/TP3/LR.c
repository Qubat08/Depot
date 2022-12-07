#include "LR.h"
#include <stdio.h>
#include <stdlib.h>


void LR_creer(LR* x){
	*x = NULL;
}
void LR_inserer(LR* x, int k){
	Element2P* temp = (Element2P*)malloc(sizeof(Element2P));
	temp->cle = k;
	temp->prec = NULL;
	temp->succ = *x;

	if (*x==NULL){
		*x = temp;
	}
	else{
		(*x)->prec = temp;
		(*x)= temp;
	}
	
}

void LR_supprimer(LR* x, Element2P* ptr){
	if (*x!= NULL){
		if (ptr!=NULL){
			if (ptr->succ != NULL && ptr->prec != NULL){
				ptr->prec->succ = ptr->succ;
				ptr->succ->prec = ptr->prec;
				free(ptr);
			}
			if (ptr->succ !=NULL && ptr->prec == NULL){
				ptr->succ->prec=NULL;
				*x=ptr->succ;
				ptr->succ = NULL;
				free(ptr);
			}
			if (ptr->succ == NULL && ptr->prec !=NULL){
				ptr->prec->succ = NULL;
				ptr->prec = NULL;
				free(ptr);
			}
			if(ptr->succ == NULL && ptr->prec == NULL){
				free(ptr);
				*x=NULL;
			}
		}
	}
}



int LR_estVide(LR* x){
	int test;
	if (*x == NULL){
		test= 1;
	}
	else{
		test= 0;
	}
	return test;	
}

Element2P* LR_rechercher(LR x, int k){
	while((x->succ) != NULL){
		if(x->cle == k){
			return x;
		}
		x = x->succ;
	}

	return NULL;
}

void afficher(LR x){
	// printf("\n Affichage Liste: \n");
	while(x->succ != NULL){
		printf(" Cle:  %d ",x->cle);
		x=x->succ;

	}
}
