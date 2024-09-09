#include "systeme.h"

void systeme_init(systeme_t *s) {
   s->m = NULL;
   s->matrice = NULL;
   s->n = 0;
}

void systeme_lecture(systeme_t *s, char* pathFile) {
    printf("Lecture du fichier %s\n", pathFile);
    FILE *fichier = fopen(pathFile, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur: impossible d'ouvrir le fichier\n");
        exit(1);
    }

    fscanf(fichier, "%d", &s->n);
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

    // Allocation de mémoire pour chaque ligne de la matrice
    for (int i = 0; i < s->n; i++) {
        s->matrice[i] = &(s->m[i * (s->n + 1)]);
    }

    for (int i = 0; i < s->n; i++) {
        for (int j = 0; j < (s->n+1) ; j++) {
            fscanf(fichier, "%lf", &s->matrice[i][j]);
        }
    }

    fclose(fichier);
}

void systeme_afficher(systeme_t s) {
    printf("======Affichage du système:======\n");
    for (int i = 0; i < s.n; i++) {
        for (int j = 0; j < s.n +1 ; j++) {
            printf("%lf ", s.matrice[i][j]);
        }
        printf("\n");
    }
}

void systeme_resoudre(systeme_t *s, int boolAffichage) {
    double* pivot;
    int iter = 0;
    for (int i = 0; i < s->n -1; i++) {
        if (boolAffichage == 1)
            printf("Iteration %d\n", iter);
        pivot = systeme_choisir_pivot(s, iter);
        if (pivot == NULL || pivot[iter] == 0) {
            iter++;
        } else {
            if (boolAffichage == 1)
                printf("Pivot: %lf\n", pivot[iter]);
            propagation_pivot_para(s, iter, iter, pivot[iter]);
            if (boolAffichage == 1)
                systeme_afficher(*s);
            iter++;
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

void propagation_pivot_para(systeme_t *s, int lignePiv, int colPiv, double valPiv) {
    double valTmp;

    // On met l'inconnue de la ligne du pivot à 1
    #pragma omp parallel for /*schedule(static, 128)*/
    for(int j = 0; j <= s->n; j++){
        s->matrice[lignePiv][j] = s->matrice[lignePiv][j] / valPiv;
    }

    // On met l'inconnue des autres lignes à 0
    #pragma omp parallel for private(valTmp)
    for(int i = lignePiv + 1; i < s->n; i++){
        // On stocke cette donnée pour éviter de la perdre
        valTmp = s->matrice[i][colPiv];
        for(int j = 0; j <= s->n; j++){
            s->matrice[i][j] = s->matrice[i][j] - (s->matrice[lignePiv][j] * valTmp);
        }
    }
}

void systeme_echanger_lignes(systeme_t*s , int iter, int i) {
    double* temp = s->matrice[iter];
    s->matrice[iter] = s->matrice[i];
    s->matrice[i] = temp;
}

void systeme_remontee_de_gauss(systeme_t* s){
    // remontée de gauss
    for (int i = s->n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < s->n; j++) {
            sum += s->matrice[i][j] * s->matrice[j][s->n];
        }
        if (s->matrice[i][i] == 0) {
            s->matrice[i][s->n] = 0;
        } else {
            s->matrice[i][s->n] = (s->matrice[i][s->n] - sum) / s->matrice[i][i];
        }
    }
}

void systeme_output(systeme_t* s, char* pathFile, int boolAffichage) {
    FILE *fichier = fopen(pathFile, "w+");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur: impossible d'ouvrir le fichier\n");
        exit(1);
    }
    fprintf(fichier, "%d\n", s->n);

    systeme_remontee_de_gauss(s);
    for (int i = 0; i < s->n; i++) {
        if (boolAffichage == 1)
            printf("x%d = %.3lf\n", i+1, s->matrice[i][s->n]);
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
