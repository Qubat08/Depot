#ifndef LISTECH_H
#define LISTECH_H

#include "Cellule.h"
#include "Element.h"

typedef struct listeCh{
	struct cellule* fin;
	struct cellule* deb;
	struct cellule* crt;
}listeCh;

void creerListe(listeCh* l);
void inserer(listeCh* l, element a);
void supprimer(listeCh* l);
int ListeVide(listeCh l);
element valeurCourante(listeCh l);

void allerDebut(listeCh* l);
int estDebut(listeCh l);
int estFin(listeCh l);
void allerFin(listeCh* l);

void avancer(listeCh* l);


#endif