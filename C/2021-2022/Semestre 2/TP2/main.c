#include "Element.h"
#include "ListeCh.h"
#include "Cellule.h"
#include <stdio.h>


void afficherListe(listeCh* l){
	printf("=====Affichage======\n");
	allerDebut(&(*l));	
	while(l->crt!=l->fin->succ){
		if(l->crt != l->deb){
			afficherElement(valeurCourante(*l));
			avancer(&(*l));
		}
		else if (l->crt == l->fin){
			// afficherElement(valeurCourante(*l));
			allerDebut(&(*l));
			break;
		}
		else{
			avancer(&(*l));
		}
	}
	allerDebut(&(*l));
	printf("\n");
}

void remplir(listeCh* l, element e){
	saisirElement(&e);
	inserer(&(*l),e);
	allerFin(&(*l));
}

void vider(listeCh* l){
	allerDebut(&(*l));
	while(l->crt!=NULL){
		allerDebut(&(*l));
		supprimer(&(*l));
		avancer(&(*l));
	}
}

int main(){

	listeCh liste;
	element e;


	creerListe(&liste);

	for(int i =0;i<5;i++){
		remplir(&liste,e);
	}
	afficherListe(&liste);

	allerDebut(&liste);
	//afficherElement(valeurCourante(liste));
	avancer(&liste);// 2e position
	//afficherElement(valeurCourante(liste));
	remplir(&liste,e);
	
	afficherListe(&liste); // 1ere position
	allerDebut(&liste);
	remplir(&liste,e);
	afficherListe(&liste);

	allerFin(&liste);
	remplir(&liste,e);
	afficherListe(&liste);

	afficherListe(&liste);


	vider(&liste);
	afficherListe(&liste);
	return 0;
}