#include <stdio.h>
#include <stdlib.h>
#include "LR.h"




int main()
{
	LR x;
	LR_creer(&x);
	// if (LR_estVide(&x)){
	// 	printf("Vide \n");
	// }
	// else{
	// 	printf("Non vide\n");
	// }

	LR_inserer(&x,1);

	// if (LR_estVide(&x)){
	// 	printf("Vide\n");
	// }
	// else{
	// 	printf("Non vide\n");
	// }
	
	LR_inserer(&x,2);
	LR_inserer(&x,3);
	LR_inserer(&x,4);


	LR ptr= NULL;
	ptr = LR_rechercher(x,5);
	printf("%p \n",ptr);
	if (ptr == NULL){
		printf("Non trouvé \n");
	}
	else{
		printf("Trouvé \n");
	}

	ptr= NULL;
	ptr = LR_rechercher(x,3);
	printf("%p \n",ptr);
	if (ptr == NULL){
		printf("Non trouvé \n");
	}
	else{
		printf("Trouvé \n");
	}

	// printf("Suppression 4 \n");
	// LR_supprimer(&x,LR_rechercher(x,4));
	// afficher(x);
	// printf("Suppression 3 \n");
	// LR_supprimer(&x,LR_rechercher(x,3));
	// afficher(x);
	// printf("Suppression 2 \n");
	// LR_supprimer(&x,LR_rechercher(x,2));
	// afficher(x);
	// printf("Suppression 1 \n");
	// LR_supprimer(&x,LR_rechercher(x,1));

	
	afficher(x);
	printf("Suppression: ");
	while((x->succ)!=NULL){
		LR_supprimer(&x,x);
	}

	return 0;
}