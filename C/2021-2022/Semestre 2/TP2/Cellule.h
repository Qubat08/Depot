#ifndef CELLULE_H
#define CELLULE_H

#include "Element.h"


typedef struct cellule{
	element e;
	struct cellule* succ;
	struct cellule* prec;
}cellule;


#endif