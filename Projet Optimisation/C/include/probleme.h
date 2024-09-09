#ifndef PROBLEME_H
#define PROBLEME_H

typedef struct {
	int n_var;			/*nombre de variables*/
	int n_cont;			/*nombre de contraintes*/
	int type_opt;		/*type d'optimisation : 0 si min et 1 si max*/
	double *fonc_obj;	/*fonction objectif, coefficients des xj*/
	double **a;			/*contraintes, coefficients des aij*/
	int *signe_cont;	/*signe de chaque contrainte, 0 si <=, 1 si >= */
	double *b;			/*valeur des contraintes : bi*/
	double* solution;   /*solution du probleme*/
	int* valFixe;    	/*tableau des valeurs fixées*/ 
	int *visited;       /*Tableau des variables visitées*/
} prob_t;


int lire_probleme(char *, prob_t *);

void afficher_probleme(prob_t *);

void lire_gros_probleme(char *, prob_t *);

void liberer_memoire_probleme(prob_t *);




#endif