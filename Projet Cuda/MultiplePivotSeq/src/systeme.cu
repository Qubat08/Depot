#include "systeme.h"
#include <ctype.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>

void systeme_init(systeme_t *s) {
   s->m = NULL;
   s->matrice = NULL;
   s->n = 0;
   s->nb_pivots = 3;
}

void systeme_lecture(systeme_t *s, char* pathFile) {
    printf("Lecture du fichier %s\n", pathFile);
    FILE *fichier = fopen(pathFile, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur: impossible d'ouvrir le fichier\n");
        exit(1);
    }

    int temp = fscanf(fichier, "%d", &s->n);
    s->m = (double *)malloc((s->n * (s->n + 1)) * sizeof(double));
    if (s->m == NULL) {
        fprintf(stderr, "Erreur: impossible d'allouer la mémoire\n");
        exit(1);
    }

    s->matrice = (double **)malloc(s->n * sizeof(double *));
    if (s->matrice == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour matrice\n");
        exit(1);
    }

    for (int i = 0; i < s->n; i++) {
        s->matrice[i] = &(s->m[i * (s->n + 1)]);
    }

    for (int i = 0; i < s->n; i++) {
        for (int j = 0; j < (s->n + 1); j++) {
            int temp = fscanf(fichier, "%lf", &s->matrice[i][j]);
        }
    }

    fclose(fichier);
}

void systeme_afficher(systeme_t s) {
    printf("======Affichage du système:======\n");
    for (int i = 0; i < s.n; i++) {
        for (int j = 0; j < s.n + 1; j++) {
            printf("%.3lf ", s.matrice[i][j]);
        }
        printf("\n");
    }
}

void systeme_resoudre(systeme_t *s, int boolAffichage) {
    double** pivots;
    int iter = 0;
    while (iter < s->n-1) {
        if (boolAffichage == 1)
            printf("Iteration %d\n", iter);
        int nb_pivots_to_use = (s->n - iter < s->nb_pivots) ? s->n - iter : s->nb_pivots;
        if (boolAffichage == 1)
            printf("nb_pivots_to_use = %d\n", nb_pivots_to_use);
        if (boolAffichage == 1)
            printf("Iteration %d\n", iter);

        pivots = systeme_choisir_pivot_multiple(s, iter, nb_pivots_to_use, boolAffichage);
        if (pivots == NULL) {
            iter++;
        } else {
            for (int k = 0; k < nb_pivots_to_use; k++) {
                if (pivots[k][iter + k] != 0){
                    pivot_diviser_ligne(pivots[k], iter + k, s->n);
                    if (boolAffichage == 1) {
                        printf("Pivot après division %d:\n", k);
                        afficher_pivots(pivots, nb_pivots_to_use, s->n);
                    }
                    pivot_soustraction_lignes(pivots, k, nb_pivots_to_use, s->n, iter);
                    if (boolAffichage == 1) {
                        printf("Pivot après Soustraction:\n");
                        afficher_pivots(pivots, nb_pivots_to_use, s->n);
                    }
                }
            }
            if (boolAffichage == 1)
                printf("Apres :\n");
            if (boolAffichage == 1)
                afficher_pivots(pivots, nb_pivots_to_use, s->n);
            
            for (int k = 0; k < nb_pivots_to_use; k++) {
                for (int i = 0; i < s->n + 1; i++) {
                    s->matrice[iter + k][i] = pivots[k][i];
                }
            }
            if (boolAffichage == 1) {
                printf("\nMatrice après modif des lignes pivots déjà fait :\n");
                systeme_afficher(*s);
            }
            
            for (int i = iter + nb_pivots_to_use; i < s->n; i++) {
                for (int k = 0; k < nb_pivots_to_use; k++) {
                    double coef = s->matrice[i][iter + k];
                    for (int j = 0; j < s->n + 1; j++) {
                        s->matrice[i][j] -= coef * s->matrice[iter + k][j];
                    }
                }
            }

            if (boolAffichage == 1) {
                printf("\nMatrice après propagation dans dernières lignes:\n");
                systeme_afficher(*s);
            }
            iter += nb_pivots_to_use;
            if (boolAffichage == 1)
                systeme_afficher(*s);
        }
    }
}

double* systeme_choisir_pivot(systeme_t *s, int j) {
    double *pivot = s->matrice[j];
    int indiceDuPivot = j;

    for (int i = j; i < s->n; i++) {
        if (fabs(s->matrice[i][j]) > fabs(pivot[j])) {
            pivot = s->matrice[i];
            indiceDuPivot = i;
        }
    }
    systeme_echanger_lignes(s, j, indiceDuPivot);

    if (pivot[j] == 0) {
        return NULL;
    }

    return pivot;
}

double** systeme_choisir_pivot_multiple(systeme_t *s, int j, int nb_pivots, int boolAffichage) {
    double **pivots = (double **)malloc(s->nb_pivots * sizeof(double *));
    int *indicesDuPivot = (int *)malloc(s->nb_pivots * sizeof(int));

    for (int k = 0; k < nb_pivots; k++) {
        pivots[k] = s->matrice[j + k];
        indicesDuPivot[k] = j + k;

        for (int i = j + k; i < s->n; i++) {
            if (fabs(s->matrice[i][j + k]) > fabs(pivots[k][j + k])) {
                pivots[k] = s->matrice[i];
                indicesDuPivot[k] = i;
            }
        }
        systeme_echanger_lignes(s, j + k, indicesDuPivot[k]);
    }

    if (boolAffichage == 1) {
        printf("Pivots choisis:\n");
        for (int k = 0; k < nb_pivots; k++) {
            printf("Pivot[%d] = %lf : Ligne pivot complete = ", k, pivots[k][j + k]);
            for (int i = 0; i < s->n + 1; i++) {
                printf("%lf ", pivots[k][i]);
            }
            printf("\n");
        }
    }
    free(indicesDuPivot);
    return pivots;
}

void pivot_diviser_ligne(double* row, int k, int n) {
    double pivot = row[k];
    for (int i = k; i < n + 1; i++) {
        row[i] /= pivot;
    }
}

void pivot_soustraction_lignes(double** pivots, int pivot_index, int nb_pivots_to_use, int n, int iter) {
    for (int i = pivot_index + 1; i < nb_pivots_to_use; i++) {
        double coef = pivots[i][pivot_index + iter] / pivots[pivot_index][pivot_index + iter];
        for (int j = iter ; j < n + 1; j++) {
            pivots[i][j] -= coef * pivots[pivot_index][j];
        }
    }
}

void systeme_echanger_lignes(systeme_t *s, int iter, int i) {
    double* temp = s->matrice[iter];
    s->matrice[iter] = s->matrice[i];
    s->matrice[i] = temp;
}

void systeme_remontee_de_gauss(systeme_t *s) {
    for (int i = s->n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < s->n; j++) {
            sum += s->matrice[i][j] * s->matrice[j][s->n];
        }
        s->matrice[i][s->n] = (s->matrice[i][s->n] - sum) / s->matrice[i][i];
        s->matrice[i][i] = 1;
        for (int k = 0; k < i; k++) {
            s->matrice[k][s->n] -= s->matrice[k][i] * s->matrice[i][s->n];
            s->matrice[k][i] = 0;
        }
    }
}

void pivot_remontee_de_gauss(double **pivots, int n, int iter_colonne) {
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += pivots[i][iter_colonne + j] * pivots[j][iter_colonne + n];
        }
        pivots[i][iter_colonne + n] = (pivots[i][iter_colonne + n] - sum) / pivots[i][iter_colonne + i];
        pivots[i][iter_colonne + i] = 1;
        for (int k = 0; k < i; k++) {
            pivots[k][iter_colonne + n] -= pivots[k][iter_colonne + i] * pivots[i][iter_colonne + n];
            pivots[k][iter_colonne + i] = 0;
        }
    }
}

void afficher_pivots(double** pivots, int nb_pivots, int n) {
    printf("====== Affichage des pivots: ======\n");
    for (int i = 0; i < nb_pivots; i++) {
        for (int j = 0; j < n + 1; j++) {
            printf("%.3lf ", pivots[i][j]);
        }
        printf("\n");
    }
}

void systeme_output(systeme_t *s, char* pathFile, int boolAffichage) {
    FILE *fichier = fopen(pathFile, "w+");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur: impossible d'ouvrir le fichier\n");
        exit(1);
    }
    fprintf(fichier, "%d\n", s->n);

    systeme_remontee_de_gauss(s);
    for (int i = 0; i < s->n; i++) {
       
        if (boolAffichage) printf("x%d = %.3lf\n", i + 1, s->matrice[i][s->n]);
        fprintf(fichier, "%lf ", s->matrice[i][s->n]);
    }
    fclose(fichier);
}

void systeme_detruire(systeme_t *s) {
    free(s->m);
    free(s->matrice);
    s->matrice = NULL;
    s->m = NULL;
    s->n = 0;
}
