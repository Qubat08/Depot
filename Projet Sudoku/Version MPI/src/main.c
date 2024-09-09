#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mpi.h>

#include "sudoku.h"

void initVariable(int argc, char **argv, char *nameFile, int *n, int *boolAffichage)
{
    if (argc < 4)
    {
        fprintf(stderr, "Erreur, le programme a besoin de plus de paramètres (nom du fichier, taille d'une case sudoku, iteration max et boolAffichage)\n");
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
        fprintf(stderr, "Erreur, le programme a besoin d'un nombre d'itération max \n");
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
int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

   srand(time(NULL) + rank);

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

    if (rank == 0) {
        if (n == 3) {
            nbLignes = randomLigne(pathFile, n);
            printf("%d\n", nbLignes);
        }
    }

//    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&nbLignes, 1, MPI_INT, 0, MPI_COMM_WORLD);
//    MPI_Bcast(&boolAffichage, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (n == 3) {
        sudoku_init_ligne(pathFile, n, &s, nbLignes);
        if (rank == 0 && boolAffichage == 1)
            sudoku_print(s, 0);
    }

    int solutionFound = 0;
    int localSolutionFound = 0;

    start = MPI_Wtime();
    int printedResult = 0;
    int localprintedResult = 0;
    int localNbIteration = 0;
    int local_nbConflitsThread = 100;
    remplirCaseVide(&s);
while (!solutionFound && !localSolutionFound) {
    nbBoucleTotal += calculRecuitSimule(&s);
    local_nbConflitsThread = calculNbConflitsTotal(s);
    localNbIteration++;

    if (boolAffichage == 1) {
        printf("Processus %d: Nombre de conflits : %d\n", rank, local_nbConflitsThread);
    }

    if (local_nbConflitsThread == 0 && !solutionFound) {

        localSolutionFound = 1;
        solutionFound = 1;
        localprintedResult = rank + 1; // Utiliser le rang + 1 pour indiquer quel processus a trouvé la solution en premier

    }

    MPI_Allreduce(&localprintedResult, &printedResult, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&localSolutionFound, &solutionFound, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Reduce(&localNbIteration, &nbIteration, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (boolAffichage == 1 && local_nbConflitsThread == 0 && printedResult == (rank + 1)) {
        sudoku_print(s, 0);
    }
    if (printedResult == (rank + 1))
    {
        end = MPI_Wtime();
        printf("%f\n", (end - start));
    }
}
    if (rank == 0) {
        printf("%d\n%lld\n", nbIteration, nbBoucleTotal);
    }

    sudoku_delete(&s);

    MPI_Finalize();
    return 0;
}