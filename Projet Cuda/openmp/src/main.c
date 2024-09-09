#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
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
    #ifdef _OPENMP
    printf("OpenMP is supported\n");
    printf("Number of threads: %d\n", omp_get_max_threads());
    #endif

    char nameFile[50];
    char pathFile[50] = "./data/";
    char pathFile2[50] = "./data/";

    double start, end;
    int boolAffichage = 0;
    initVariable(argc, argv, nameFile, &boolAffichage);

    strcat(pathFile, nameFile);
    strcat(pathFile, ".txt");

    systeme_t s;
    systeme_init(&s);
    systeme_lecture(&s, pathFile);

    start = omp_get_wtime();
    systeme_resoudre(&s, boolAffichage);
    end = omp_get_wtime();

    strcat(pathFile2, nameFile);
    strcat(pathFile2, "_resultat");
    strcat(pathFile2, ".txt");

    systeme_output(&s, pathFile2, boolAffichage);

    double time = end - start;
    printf("Temps d'execution: %f secondes\n", time);

    systeme_detruire(&s);
    return 0;
}
