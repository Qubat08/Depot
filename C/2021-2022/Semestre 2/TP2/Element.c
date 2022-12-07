#include <stdio.h>
#include "Element.h"

void afficherElement(element e){
	printf("%d \t", e);
}

void saisirElement(element* e){
	printf("\nSaisir Element:  \n");
	scanf("%d",e);
}