#include <stdio.h>
#include <stdlib.h>

#include "TH.h"
#include "LR.h"


void LR_vider(LR* x){
	while(! LR_estVide(x)){
		// afficher(*x);
		LR_supprimer(x,*x);
	}
}

void TH_vider (TH* tab){
	for (int i = 0;i<MAX;i++){
		LR_vider(&((*tab)[i]));
	}
}
void TH_afficher(TH tab){
	for (int i=0;i<MAX;i++){
		printf("%d: ",i);
		afficher(tab[i]);
		printf("\n");
	}
	printf("\n");
}
int main(){
	TH t;
	Element2P* p;
	TH_creer(&t);
	TH_afficher(t);

	TH_inserer(&t,5141);
	TH_inserer(&t,234);
	TH_inserer(&t,645);
	TH_afficher(t);

	for(int i=0; i<=4 ; i++){
		TH_inserer(&t, 340*i);
	}
	TH_afficher(t);
	p=TH_rechercher(t,215);
	printf("%p \n",p);

	p=TH_rechercher(t,680);
	printf("%p \n",p);
	TH_afficher(t);
	printf("\n SUPPRESSION 680 \n");
	TH_supprimer(&t,p);
	TH_afficher(t);


	printf("\n Vide TH \n");
	TH_vider(&t);
	TH_afficher(t);
	return 0;
}