#ifndef SUDOKU_H
#define SUDOKU_H

#include <string.h>
#include "case.h"

typedef struct sudoku
{
    case_t **grid; // tableau 2 dimensions de 3 entiers
    int n;

} sudoku_t;

void sudoku_init(char[], sudoku_t *);
void initStruct(sudoku_t *);
void sudoku_print(sudoku_t, int);
void sudoku_delete(sudoku_t *);
void remplirCaseVide(sudoku_t *);
int calculerNbConflits(sudoku_t, int, int);
int calculRecuitSimule(sudoku_t *, unsigned int );
int calculNbConflitsTotal(sudoku_t);
void sudoku_init_ligne(char[], int, sudoku_t *, int);
int randomLigne(char[], int);

#endif