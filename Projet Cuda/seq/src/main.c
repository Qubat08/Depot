#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "systeme.h"

void initVariable(int argc, char **argv, char *nameFile, int* boolAffichage){
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <nom_fichier_input> <boolAffichage>\n", argv[0]);
        exit(1);
    }
    strcpy(nameFile, argv[1]);
    *boolAffichage = atoi(argv[2]);



}

int main(int argc, char **argv) {
    char nameFile[50]; 
    char pathFile[50] = "./data/";
    char pathFile2[50] = "./data/";
    clock_t start, end;
    int boolAffichage = 0;
    initVariable(argc, argv, nameFile, &boolAffichage);

    strcat(pathFile, nameFile); 
    strcat(pathFile, ".txt");


    systeme_t s;
    systeme_init(&s);
    systeme_lecture(&s, pathFile);
    
    start = clock();
   // printf("Systeme avant resolution:\n");
  //  systeme_afficher(s);
    systeme_resoudre(&s, boolAffichage);

    
    strcat(pathFile2, nameFile); 
    strcat(pathFile2, "_resultat");
    strcat(pathFile2, ".txt");

    systeme_output(&s, pathFile2, boolAffichage);

    end = clock();
    printf("Temps d'execution: %f\n", (double)(end - start) / CLOCKS_PER_SEC);


    systeme_detruire(&s);
    return 0;
}
