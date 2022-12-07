#include <stdio.h>
#include <stdlib.h>  
#include "pileCh.h"
#include "cellule.h"
#include "element.h"

#define MAX 100

void viderPile(pilech* p){
	while(p->top != NULL){
		supprimerCellule(&(*p));
	}
}

void inverserPile(pilech* p){
	element tab[MAX];
	int i=0,cpt=0;
	while(p->top !=NULL){
		tab[i] = p->top->e;
		// printf("%d \n",tab[i]);
		supprimerCellule(&(*p));
		i++;
		cpt++;

	}
	viderPile(&(*p));
	for(i=0;i<cpt;i++){
		// printf("%d \n",tab[i]);
		ajouterCellule(&(*p),tab[i]);
	}
}

int main(){

	pilech p;
	element a;
	creerPile(&p);
	// afficherPile(p);

	// printf("%p",p.top);
	saisirElement(&a);

	ajouterCellule(&p,a);
	// afficherPile(p);

	saisirElement(&a);
	ajouterCellule(&p,a);
	// afficherPile(p);


	saisirElement(&a);
	ajouterCellule(&p,a);

	saisirElement(&a);
	ajouterCellule(&p,a);
	afficherPile(p);


	supprimerCellule(&p);
	afficherPile(p);


	inverserPile(&p);
	afficherPile(p);


	viderPile(&p);
	afficherPile(p);
	return 0;
}