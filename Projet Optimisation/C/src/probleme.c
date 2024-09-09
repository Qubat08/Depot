#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "probleme.h"

void afficher_probleme(prob_t *prob){
	int i,j;

	printf("\n");
	if (prob->type_opt)
		printf("Maximiser z = ");
	else
		printf("Minimiser z = ");

	for (j = 0; j < prob->n_var; j++) {
		if (prob->fonc_obj[j] < 0)
			printf("- ");
		else
			printf("+ ");
		printf("%6.2lf ", fabs(prob->fonc_obj[j]));
		printf("x%d ", j + 1);
	}
	printf("\n\n");
	printf("Sous les contraintes\n\n");
	for (i = 0; i < prob->n_cont; i++){
		for (j = 0; j < prob->n_var; j++) {
			if (prob->a[i][j] < 0)
				printf("- ");
			else
				printf("+ ");
			printf("%6.2lf ", fabs(prob->a[i][j]));
			printf("x%d ", j + 1);
		}
		if (prob->signe_cont[i] == 0)
			printf("<= ");
		else if (prob->signe_cont[i] == 1)
			printf(">= ");
		if (prob->b[i] < 0)
			printf("- ");
		else
			printf("+ ");
		printf("%6.2lf\n", fabs(prob->b[i]));
	}
	printf("\n");
	for (j = 0; j < prob->n_var; j++) {
		printf("x%d >= 0", j + 1);
		if (j < prob->n_var - 1)
			printf(", ");
	}
	printf("\n");

}

int lire_probleme(char *nom_fichier, prob_t *prob){
/*Lit les donnees d'un probleme a partir d'un fichier specifie*/
/*et les place dans la structure prob*/

	FILE *fichier;
	char ch_temp[20], signe[3];
	int i, j;

	if ((fichier = fopen(nom_fichier, "r"))) {
		fscanf(fichier, "%s", ch_temp);
		fscanf(fichier, "%d", &prob->n_var);
		fscanf(fichier, "%s", ch_temp);
		fscanf(fichier, "%d", &prob->n_cont);
		fscanf(fichier, "%s", ch_temp);
		if (!strcmp(ch_temp, "max"))
			prob->type_opt = 1;
		else
			prob->type_opt = 0;
		prob->fonc_obj = (double *) malloc(sizeof(double) * prob->n_var);
		for (j = 0; j < prob->n_var; j++) {
			fscanf(fichier, "%s", signe);
			fscanf(fichier, "%lf", &prob->fonc_obj[j]);
			if (!strcmp(signe, "-"))
				prob->fonc_obj[j] = - prob->fonc_obj[j];
			fscanf(fichier, "%s", ch_temp);
		}
		prob->a = (double **) malloc(sizeof(double *) * prob->n_cont);
		prob->signe_cont = (int *) malloc(sizeof(int) * prob->n_cont);
		prob->b = (double *) malloc(sizeof(double) * prob->n_cont);



		for (i = 0; i < prob->n_cont; i++){
			prob->a[i] = (double *) malloc(sizeof(double) * prob->n_var);
			for (j = 0; j < prob->n_var; j++) {
				fscanf(fichier, "%s", signe);
				fscanf(fichier, "%lf", &prob->a[i][j]);
				if (!strcmp(signe, "-"))
					prob->a[i][j] = - prob->a[i][j];
				fscanf(fichier, "%s", ch_temp);
			}
			fscanf(fichier, "%s", signe);
			if (!strcmp(signe, "<="))
				prob->signe_cont[i] = 0;
			else if (!strcmp(signe, ">="))
				prob->signe_cont[i] = 1;
			fscanf(fichier, "%lf", &prob->b[i]);
		}
		fclose(fichier);
	}
	else {
		printf("Probleme lecture fichier\n");
		return -1;
	}

	return 0;
}

void lire_gros_probleme(char *filename, prob_t *prob){
 FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[256];
    int n, capacity;

    // Read number of items (n) and capacity
    fgets(line, sizeof(line), file);
    sscanf(line, "n: %d", &n);
    fgets(line, sizeof(line), file);
    sscanf(line, "c: %d", &capacity);

    // lire ligne vide
    fgets(line, sizeof(line), file);

    prob->n_var = n;
    prob->n_cont = 1; // Only one constraint
    prob->type_opt = 1; // Maximization problem

    prob->fonc_obj = (double *)malloc(n * sizeof(double));
    prob->a = (double **)malloc(sizeof(double *));
    prob->a[0] = (double *)malloc(n * sizeof(double));
    prob->signe_cont = (int *)malloc(sizeof(int));
    prob->b = (double *)malloc(sizeof(double));

    if (prob->fonc_obj == NULL || prob->a == NULL || prob->a[0] == NULL ||
        prob->signe_cont == NULL || prob->b == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return;
    }

    prob->signe_cont[0] = 0; // Sign of the constraint (0 for <=)
    prob->b[0] = (double)capacity;

    // Read volumes and utilities
    int volume, utility;
    for (int i = 0; i < n; ++i) {
        fgets(line, sizeof(line), file);
        sscanf(line, "%d %d", &volume, &utility);
        prob->a[0][i] = (double)volume;
        prob->fonc_obj[i] = (double)utility;
    }

    fclose(file);
}

void liberer_memoire_probleme(prob_t *prob){
	int i;

	if (prob->fonc_obj != NULL)
		free(prob->fonc_obj);
	for (i = 0; i < prob->n_cont; i++)
		if (prob->a[i] != NULL)
			free(prob->a[i]);
	if (prob->a != NULL)
		free(prob->a);
	if (prob->signe_cont != NULL)
		free(prob->signe_cont);
	if (prob->b != NULL)
		free(prob->b);

}
