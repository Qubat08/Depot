#include "pileCh.h"
#include <stdio.h>
#include <stdlib.h>



void creerPile(pilech* pile){
	pile->top = NULL;

}

void afficherPile(pilech pile){
	printf("Affichage de la pile: \n");
	if(pileVide(pile)){
		
	}
	else{
		cellule* actuel = pile.top;

		while(actuel != NULL){
			printf("-> %d ",actuel->e);
			actuel = actuel->succ;
		}
		printf("\n");
	}
}


void ajouterCellule(pilech* pile, element e){
	cellule* ptr =malloc(sizeof(cellule));
	ptr->e = e;
	ptr->succ = pile->top;
	pile->top = ptr;
	
}


void supprimerCellule(pilech* pile){ 
	int x = 0;
	if(pile->top != NULL){
		cellule* temp = pile->top->succ;
		// element x = pile->top->e;
		free(pile->top);
		pile->top  = temp;
	}
}

int pileVide(pilech pile){
	if (pile.top == NULL){
		return 1;
	}else{
		return 0;
	}
}