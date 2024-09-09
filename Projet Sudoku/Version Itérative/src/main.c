#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "sudoku.h"

void initVariable(int argc, const char *argv[], char *nameFile, int *n, int *boolAffichage)
{
    if (argc < 4)
    {
        fprintf(stderr, "Erreur, le programme a besoin de plus de paramètres (nom du fichier, taille d'une case sudoku et boolAffichage)\n");
        exit(1);
    }
    if (argv[1] != NULL)
    {
        strcpy(nameFile, argv[1]);
    }
    else
    {
        fprintf(stderr, "Erreur, le programme a besoin d'un nom de fichier \n");
        exit(1);
    }
    if (argv[2] != NULL)
    {
        *n = atoi(argv[2]);
    }
    else
    {
        fprintf(stderr, "Erreur, le programme a besoin d'une taille \n");
        exit(1);
    }

    if (argv[3] != NULL)
    {
        *boolAffichage = atoi(argv[3]);
    }
    else
    {
        fprintf(stderr, "Erreur, le programme a besoin d'un boolean (0 ou 1) \n");
        exit(1);
    }
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    sudoku_t s;
    char nameFile[50];
    char pathFile[50] = "./data/";
    int nbIteration = 0;
    int nbConflits = 10000;
    int n, boolAffichage = 0;
    unsigned long long nbBoucleTotal = 0;
    clock_t start, end;

    initVariable(argc, argv, nameFile, &n, &boolAffichage);

    initStruct(&s);

    strcat(pathFile, nameFile);
    strcat(pathFile, ".txt");

    if (n > 3)
    {
        sudoku_init(pathFile, &s);
    }
    else
    {
        int nbLignes = randomLigne(pathFile, n);
        printf("%d\n", nbLignes);
        sudoku_init_ligne(pathFile, n, &s, nbLignes);
    }

    if (boolAffichage == 1)
    {
        sudoku_print(s);
    }
    start = clock();
    remplirCaseVide(&s);
    while (nbConflits != 0)
    {
        nbBoucleTotal += calculRecuitSimule(&s);
        nbConflits = calculNbConflitsTotal(s);
		if (boolAffichage == 1){
			printf("Nombre de conflits : %d\n", nbConflits);
		}
        nbIteration++;
    }
    end = clock();

    if (nbConflits != 0)
    {
        printf("Echec de la résolution du sudoku en %d (%lld) iterations,\n nombre de conflits restants: %d\n", nbIteration, nbBoucleTotal, nbConflits);
    }
    else
    {
        printf("%d\n%lld\n", nbIteration, nbBoucleTotal);
    }
    printf("%f\n", ((double)(end - start) / CLOCKS_PER_SEC));
    if (boolAffichage == 1)
    {
        sudoku_print(s);
    }

    sudoku_delete(&s);

    return 0;
}