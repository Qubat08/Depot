#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sudoku.h"
#include "case.h"

void initStruct(sudoku_t *sudoku)
{
    sudoku->grid = NULL;
    sudoku->n = 0;
}

void sudoku_init(char pathFile[50], sudoku_t *s)
{
    FILE *fichier = fopen(pathFile, "r");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
    }

    if (fscanf(fichier, "%d", &(s->n)) != 1)
    {
        perror("Erreur de lecture de la valeur n");
        fclose(fichier);
    }

    int tailleGrille = s->n * s->n;
    // case_t(*grid)[tailleGrille] = (case_t(*)[tailleGrille])malloc(sizeof(case_t) * tailleGrille * tailleGrille);
    // int(*estFixe)[tailleGrille] = (int(*)[tailleGrille])malloc(sizeof(int) * tailleGrille * tailleGrille);
    s->grid = (case_t **)malloc(sizeof(case_t *) * tailleGrille);
    if (s->grid == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour 'grid'.\n");
        exit(1);
    }
    else
    {
        for (int i = 0; i < tailleGrille; i++)
        {
            s->grid[i] = (case_t *)malloc(sizeof(case_t) * tailleGrille);
            if (s->grid[i] == NULL)
            {
                fprintf(stderr, "Erreur lors de l'allocation de mémoire pour 'grid[%d]'.\n", i);
                exit(1);
            }
        }
    }
    int temp = 0;
    for (int i = 0; i < tailleGrille; i++)
    {
        for (int j = 0; j < tailleGrille; j++)
        {
            if (fscanf(fichier, "%d", &temp) != 1)
            {
                perror("Erreur de lecture des données de la grille");
                fclose(fichier);
                free(s->grid);
            }
            else
            {
                s->grid[i][j].val = temp;
                if (temp > 0)
                {
                    s->grid[i][j].fixe = 1;
                }
                else
                {
                    s->grid[i][j].fixe = 0;
                }
            }
        }
    }
    fclose(fichier);
}


int randomLigne(char pathFile[50], int n)
{
    int tailleGrille = n * n;
    int MAXSIZE = tailleGrille * tailleGrille + 1;
    char buffer[MAXSIZE];
    char caractere;
    int count = 0; // Initialiser à 1 pour inclure la première ligne

    FILE *fichier = fopen(pathFile, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1);
    }

    // Compter le nombre de lignes
    while ((caractere = fgetc(fichier)) != EOF) {
    if (caractere == '\r' || caractere == '\n') {
            // Ignorer les caractères de retour chariot ou de saut de ligne suivant
            if ((caractere == '\r' && fgetc(fichier) == '\n') || caractere == '\n') {
                count++;
            }
        }
    }
    rewind(fichier);

    int randomLine = (rand() % count);

    fclose(fichier);
    return randomLine;
}

void sudoku_init_ligne(char pathFile[50], int n, sudoku_t *s, int nbLignes)
{
    int tailleGrille = n * n;
    s->n = n;
    int MAXSIZE = tailleGrille * tailleGrille +4; // caractères spéciaux de fin de ligne + 1

    char buffer[MAXSIZE];
    FILE *fichier = fopen(pathFile, "r");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    // Parcourir le fichier jusqu'à la ligne nbLignes
    for (int i = 0; i < nbLignes; i++)
    {
        if (fgets(buffer, MAXSIZE, fichier) == NULL)
        {
            fprintf(stderr, "Erreur lors de la lecture de la ligne %d.\n", i);
            fclose(fichier);
            exit(1);
        }
    }

    s->grid = (case_t **)malloc(sizeof(case_t *) * tailleGrille);
    if (s->grid == NULL)
    {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour 'grid'.\n");
        exit(1);
    }
    else
    {
        for (int i = 0; i < tailleGrille; i++)
        {
            s->grid[i] = (case_t *)malloc(sizeof(case_t) * tailleGrille);
            if (s->grid[i] == NULL)
            {
                fprintf(stderr, "Erreur lors de l'allocation de mémoire pour 'grid[%d]'.\n", i);
                exit(1);
            }
        }
    }

    int k = 0;
    for (int i = 0; i < tailleGrille; i++)
    {
        for (int j = 0; j < tailleGrille; j++)
        {
            if (buffer[k] == '0')
            {
                s->grid[i][j].val = 0;
                s->grid[i][j].fixe = 0;
                s->grid[i][j].nbConflits = 0;
            }
            else if (buffer[k] >= '1' && buffer[k] <= '9')
            {
                s->grid[i][j].val = buffer[k] - '0';
                s->grid[i][j].fixe = 1;
                s->grid[i][j].nbConflits = 0;
            }
            k++;
        }
    }
    fclose(fichier);
}



void remplirCaseVide(sudoku_t *s)
{
    // printf("Remplir Case vide \n");
    int tailleGrille = s->n * s->n;
    // case_t(*grid)[tailleGrille] = (case_t(*)[tailleGrille])s->grid;
    // int(*fixes)[tailleGrille] = (int(*)[tailleGrille])s->fixe;

    for (int i = 0; i < tailleGrille; i++)
    {
        for (int j = 0; j < tailleGrille; j++)
        {
            if (s->grid[i][j].fixe == 0)
            {
                s->grid[i][j].val = rand() % tailleGrille + 1;
            }
        }
    }

}

int calculNbConflitsTotal(sudoku_t s)
{
    int tailleGrille = s.n * s.n;
    int somme = 0;
    for (int i = 0; i < tailleGrille; i++)
    {
        for (int j = 0; j < tailleGrille; j++)
        {
            if (s.grid[i][j].fixe == 0)
            {
                s.grid[i][j].nbConflits = calculerNbConflits(s, i, j);
                somme += s.grid[i][j].nbConflits;
            }
        }
    }
    return somme;
}

int calculRecuitSimule(sudoku_t *s, unsigned int seed)
{
    int tailleGrille = s->n * s->n;
    double T;
    double delta = 0.1;
    double ep = 1620 / 2;
    T = ep;
    int nbIterations = 0;
    int cpt = 0;
    int c = calculNbConflitsTotal(*s);
    int valeur = c;
    int rep = 0;
    int cpt2 = 0;
    while (T >= 0.00273852 && c > 0)
    {
        int oldC = c;
        for (int a = 0; a < tailleGrille * tailleGrille; a++)
        {
            int i = rand_r(&seed) % tailleGrille;
            int j = rand_r(&seed) % tailleGrille;

            if (s->grid[i][j].fixe == 0)
            {
                int valeur = rand() % tailleGrille + 1;
                int temp = s->grid[i][j].val;
                int nbConflits = s->grid[i][j].nbConflits;
                s->grid[i][j].val = valeur;
                int nbConflits2 = calculerNbConflits(*s, i, j);

                int cprime = c - nbConflits + nbConflits2;
                double u = (double)rand_r(&seed) / RAND_MAX;

                if (u <= exp(-(cprime - c) / T))
                {
                    s->grid[i][j].nbConflits = nbConflits2;
                    c = cprime;
                    // calculerNbConflitsConcerner(s, i, j);
                }
                else
                {
                    s->grid[i][j].val = temp;
                    s->grid[i][j].nbConflits = nbConflits;
                }
            }
            nbIterations++;
        }
        T = T / (1 + (log10(1 + delta) / (ep + 1)) * T);
        cpt++;
        if (cpt % 10000 == 0)
        {
            if (c == oldC)
            {
                cpt2++;
            }
            oldC = c;
        }

        if (cpt2 > 20)
        {
            break;
        }
    }
    return nbIterations;
}



int calculerNbConflits(sudoku_t s, int i, int j)
{

    int tailleGrille = s.n * s.n;
    int valeur = s.grid[i][j].val;
    int nbConflits = 0;
    // check Line and colomn
    for (int j1 = 0; j1 < tailleGrille; j1++)
    {
        if (s.grid[i][j1].val == valeur && j1 != j)
        {
            nbConflits++;
        }
        if (s.grid[j1][j].val == valeur && j1 != i)
        {
            nbConflits++;
        }
    }

    // check Case
    int startI = i - i % s.n;
    int startJ = j - j % s.n;
    for (int i1 = startI; i1 < startI + s.n; i1++)
    {
        for (int j1 = startJ; j1 < startJ + s.n; j1++)
        {
            if (i1 != i && j1 != j)
            {
                if (s.grid[i1][j1].val == valeur)
                {
                    nbConflits++;
                }
            }
        }
    }
    return nbConflits;
}

void sudoku_print(sudoku_t s, int boolAffichage)
{

    if (s.n == 3)
    {
        // printf("Dimension : %d\n", s.n);
        int tailleGrille = s.n * s.n;
        printf("\n╔═══════╦═══════╦═══════╗\n");
        for (int i = 0; i < s.n * s.n; i++)
        {
            for (int j = 0; j < s.n * s.n; j++)
            {
                if (j % s.n == 0)
                {
                    printf("║ ");
                }
                printf("%d ", s.grid[i][j].val);
            }
            printf("║\n");
            if ((i + 1) % s.n == 0)
            {
                if (i != s.n * s.n - 1)
                    printf("╠═══════╬═══════╬═══════╣\n");
                else
                    printf("╚═══════╩═══════╩═══════╝\n");
            }
        }
        if (boolAffichage == 1){
            printf("\n╔═══════╦═══════╦═══════╗\n");
            for (int i = 0; i < s.n * s.n; i++)
            {
                for (int j = 0; j < s.n * s.n; j++)
                {
                    if (j % s.n == 0)
                    {
                        printf("║ ");
                    }
                    printf("%d ", s.grid[i][j].nbConflits);
                }
                printf("║\n");
                if ((i + 1) % s.n == 0)
                {
                    if (i != s.n * s.n - 1)
                        printf("╠═══════╬═══════╬═══════╣\n");
                    else
                        printf("╚═══════╩═══════╩═══════╝\n");
                }
            }
        }
        // printf("\n╔═══════╦═══════╦═══════╗\n");
        // for (int i = 0; i < s.n * s.n; i++)
        // {
        //     for (int j = 0; j < s.n * s.n; j++)
        //     {
        //         if (j % s.n == 0)
        //         {
        //             printf("║ ");
        //         }
        //         printf("%d ", s.grid[i][j].fixe);
        //     }
        //     printf("║\n");
        //     if ((i + 1) % s.n == 0)
        //     {
        //         if (i != s.n * s.n - 1)
        //             printf("╠═══════╬═══════╬═══════╣\n");
        //         else
        //             printf("╚═══════╩═══════╩═══════╝\n");
        //     }
        // }
    }
    else if (s.n == 4)
    {
        for (int i = 0; i < s.n * s.n; i++)
        {
            if (i % s.n == 0)
            {
                printf(" --------------------------------------------------------------\n");
            }
            for (int j = 0; j < 16; j++)
            {
                if (j % s.n == 0)
                {
                    printf(" | ");
                }
                printf("%2d ", s.grid[i][j].val);
            }
            printf(" |\n");
        }
        printf(" --------------------------------------------------------------\n");
        for (int i = 0; i < s.n * s.n; i++)
        {
            if (i % s.n == 0)
            {
                printf(" --------------------------------------------------------------\n");
            }
            for (int j = 0; j < 16; j++)
            {
                if (j % s.n == 0)
                {
                    printf(" | ");
                }
                printf("%2d ", s.grid[i][j].nbConflits);
            }
            printf(" |\n");
        }
        printf(" --------------------------------------------------------------\n");
    }
}

void sudoku_delete(sudoku_t *s)
{
    int tailleGrille = s->n * s->n;
    for (int i = 0; i < tailleGrille; i++)
    {
        free(s->grid[i]);
        s->grid[i] = NULL;
    }
    free(s->grid);
    s->grid = NULL;
    // La ligne suivante est incorrecte, elle ne désalloue pas la structure elle-même.
    // s = NULL;
}