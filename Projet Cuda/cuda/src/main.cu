#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cublas_v2.h>

#include "systeme.h"

void initVariable(int argc, char **argv, char *nameFile, int* boolAffichage) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <nom_fichier_input> <boolAffichage>\n", argv[0]);
        exit(1);
    }
    strcpy(nameFile, argv[1]);
    *boolAffichage = atoi(argv[2]);
}

int main(int argc, char** argv) {
    char nameFile[50];
    char pathFile[50] = "./data/";
    char pathFile2[50] = "./data/";
    int boolAffichage = 0;
    initVariable(argc, argv, nameFile, &boolAffichage);

    strcat(pathFile, nameFile);
    strcat(pathFile, ".txt");

    systeme_t s;
    systeme_init(&s);
    systeme_lecture(&s, pathFile);

    cudaEvent_t start, stop;
    float milliseconds = 0;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    systeme_resoudre(&s, boolAffichage);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    cudaEventElapsedTime(&milliseconds, start, stop);

    strcat(pathFile2, nameFile);
    strcat(pathFile2, "_resultat");
    strcat(pathFile2, ".txt");

    systeme_output(&s, pathFile2, boolAffichage);

    printf("Temps d'execution: %f secondes\n", milliseconds / 1000);

    systeme_detruire(&s);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    return 0;
}