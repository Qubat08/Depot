#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "probleme.h"

int* calculHeuristique(prob_t*);
void evaluationMethod(prob_t*, int);
void affichage(prob_t);
int verification_probleme(prob_t*, double*);
int  separation_evaluation(prob_t*, double, int);
prob_t* copie_profonde_prob_t(prob_t*);
int visited_variable(prob_t*);
void initialize_unvisited(prob_t *);
#endif