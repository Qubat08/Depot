#ifndef CELLULE_H
#define CELLULE_H
#include "element.h"


typedef struct cellule{
	element e;
	struct cellule* succ;
}cellule;


#endif