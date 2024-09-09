#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>

#include "sudoku.h"

void initVariable(int argc, const char *argv[], char *nameFile, int *n,  int *boolAffichage)
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
        fprintf(stderr, "Erreur, le programme a besoin d'un nombre d'itération max \n");
        exit(1);
    }
}

int main(int argc, char const *argv[])
{
    unsigned int seed = 0;
    #ifdef _OPENMP
    #pragma omp parallel
     {
        unsigned int seed = time(NULL) + omp_get_thread_num();
        srand(time(NULL) + omp_get_thread_num());
    }
    #else
        srand(time(NULL));
    #endif
    sudoku_t s;
    char nameFile[50];
    char pathFile[50] = "./data/";
    int nbIteration = 0;
    int nbConflits = 10000;
    int n, boolAffichage = 0;
    unsigned long long nbBoucleTotal = 0;
    double start, end;
    int nbLignes = 0;
    initVariable(argc, argv, nameFile, &n, &boolAffichage);

    initStruct(&s);

    strcat(pathFile, nameFile);
    strcat(pathFile, ".txt");
#pragma omp parallel
{
    #pragma omp master
    {
        #ifdef _OPENMP
        if (boolAffichage == 1)
        {
            printf("Nombre de threads :  %d\n", omp_get_num_threads());
        }
        #endif
        if (n == 3)
        {
            nbLignes = randomLigne(pathFile, n);
            printf(" Numero ligne : %d\n", nbLignes);
        }
    }
}

    int solutionFound = 0;
  
    #pragma omp parallel shared(n, nbLignes,solutionFound) private(s) reduction(+:nbBoucleTotal) reduction(+:nbIteration)
    {
        if (n == 3)
        {
            sudoku_init_ligne(pathFile, n, &s, nbLignes);
            #pragma omp single
            {
            if (boolAffichage == 1)
                {
                    sudoku_print(s,0);
                }
            }
            remplirCaseVide(&s);
        }

        int local_nbConflitsThread = 100;
        start = omp_get_wtime();
        while(local_nbConflitsThread != 0 && !solutionFound)
        {
            // Chaque thread fait son travail ici
            nbBoucleTotal += calculRecuitSimule(&s, seed);
            local_nbConflitsThread = calculNbConflitsTotal(s);

            nbIteration++;
            if (boolAffichage == 1 )
            {
                printf("Proc %d: Nombre de conflits : %d\n", omp_get_thread_num(), local_nbConflitsThread);
            }

            if (local_nbConflitsThread == 0 && !solutionFound)
            {
				#pragma omp atomic write
                solutionFound = 1;
                nbConflits = 0;
                if (boolAffichage == 1){
                    sudoku_print(s, 0);
                }
            }
        }
    }

    end = omp_get_wtime();
    if (nbConflits != 0)
    {
        printf("Echec de la résolution du sudoku en %d (%lld) iterations,\n nombre de conflits restants: %d\n", nbIteration, nbBoucleTotal, nbConflits);
    }
    else
    {
        printf("Sudoku résolu en %d (%lld) iterations\n", nbIteration, nbBoucleTotal);
        printf("Temps d'exécution : %f secondes\n", end - start);
    }
    #pragma omp parallel
    {
        sudoku_delete(&s);
    }


    return 0;
}