#include "liste.h"

void initListe(liste2C* l){
    l->tete = NULL; /*liste2C Vide*/
}

void inserer_liste(liste2C* l, cellule* temp){
    if (ListeVide(*l)){
        l->tete = temp;
    }
    else{ /*pas vide*/
        temp->succ = l->tete;
        l->tete->prec= temp;
        l->tete = temp;
    }

}
void supprimer_liste2C(liste2C* l, cellule* x){
   if (x->prec != NULL){
    x->prec->succ = x->succ;
   } else{
    l->tete = x->succ;
   }
   if (x->succ != NULL){
    x->succ->prec = x->prec;
   }

   free(x);
}


int ListeVide(liste2C x){
    if (x.tete == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

cellule* liste_Rechercher(liste2C x, int k){
    cellule* temp = x.tete;

    while(temp != NULL){
        if (temp->sommet_graphe == k){
            return temp;
        }
        else{
            temp = temp->succ;
        }
    }
    return NULL;
}
void afficherListe(liste2C x){
    cellule* temp = x.tete;
if (x.tete == NULL){
    printf("Liste Vide \n");
}
else{
    while(temp != NULL){
        afficherCellule(*temp);
        temp = temp->succ;
    }
}
    printf("\n");
}

void viderListe(liste2C* x){
    while(x->tete!= NULL){
        supprimer_liste2C(x,x->tete);
    }
}