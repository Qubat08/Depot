#include "Element.h"
#include "Cellule.h"
#include "ListeCh.h"
#include <stdio.h>
#include <stdlib.h>



void creerListe(listeCh* l){
	cellule* temp = (cellule*)malloc(sizeof(cellule));
	temp->succ = NULL;
	temp->prec = NULL;
	temp->e = 0;
	l->deb = temp;
	l->fin = temp;
	l->crt = temp;
}

int ListeVide(listeCh l){
	if (l.deb == NULL){
		return 1;
	}
	else{
		return 0;
	}
}
element valeurCourante(listeCh l){
	cellule* temp = l.crt;
	return temp->e;
}


void inserer(listeCh* l, element a){
	cellule* ptr = (cellule*)malloc(sizeof(cellule));
	ptr->e = a;
	ptr->succ = NULL;
	ptr->prec = NULL;

	if(l->crt == NULL){
	}
	else{
		ptr->prec = l->crt;	
		ptr->succ = l->crt->succ;
		l->crt->succ = ptr;
		avancer(&(*l));
		allerFin(&(*l));
	}

}
void supprimer(listeCh* l){
		if (l->crt !=NULL){
			if (l->crt->succ != NULL && l->crt->prec != NULL){
				l->crt->prec->succ = l->crt->succ;
				l->crt->succ->prec = l->crt->prec;
				free(l->crt);
			}
			if (l->crt->succ !=NULL && l->crt->prec == NULL){
				l->crt->succ->prec=NULL;
				l->deb=l->crt->succ;
				l->crt->succ = NULL;
				free(l->crt);
				l->crt = l->deb;
			}
			if (l->crt->succ == NULL && l->crt->prec !=NULL){
				l->crt->prec->succ = NULL;
				l->fin = l->crt->prec;
				l->crt->prec = NULL;
				free(l->crt);
			}
			// if(l->crt->succ == NULL && l->crt->prec == NULL){
			// 	free(l->crt);
			// }
		}
	}


void avancer(listeCh* l){
	if(l->crt != NULL){
		l->crt = l->crt->succ;
	}
}


void allerDebut(listeCh* l){
	l->crt = l->deb;
}
int estDebut(listeCh l){
	if (l.crt == l.deb->succ){
		return 1;
	}
	else{
		return 0;
	}
}


int estFin(listeCh l){
	if (l.crt == l.fin){
		return 1;
	} else{
		return 0;
	}
}
void allerFin(listeCh* l){
	while(l->crt->succ !=NULL){
		l->fin = l->crt->succ;
		l->crt = l->crt->succ;
	}
	l->crt = l->fin;
}