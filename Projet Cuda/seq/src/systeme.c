#include "systeme.h"
#include <ctype.h>

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
        if (pivot == NULL) {
            //fprintf(stderr, "Erreur: pivot nul\n");
            iter++;
        }
        else{
            if (boolAffichage == 1)
                printf("Pivot: %lf\n", pivot[iter]);
            systeme_diviser_ligne(s, iter);
            systeme_soustraction_lignes(s, pivot, iter);
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
        //fprintf(stderr, "Erreur: pivot nul\n");
        return NULL;
    }
    
    return pivot;
}

void systeme_soustraction_lignes(systeme_t *s, double* pivot, int iter) {
    // fait la soustraction des lignes en dessous du pivot avec un coefficient
    for (int i = iter + 1; i < s->n; i++) {
        double coef = s->matrice[i][iter] / pivot[iter];
        for (int j = iter; j < s->n + 1; j++) {
            s->matrice[i][j] = s->matrice[i][j] - coef * pivot[j];
        }
    }
}

void systeme_diviser_ligne(systeme_t *s, int i) {
    double pivot = s->matrice[i][i];
    for (int j = i; j < s->n + 1; j++) {
        s->matrice[i][j] = s->matrice[i][j] / pivot;
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
            // Gérer le cas de division par zéro
            //fprintf(stderr, "Erreur: division par 0\n");
            s->matrice[i][s->n] = 0; // Affecter une valeur par défaut
        } else {
            s->matrice[i][s->n] = (s->matrice[i][s->n] - sum) / s->matrice[i][i];
        }
        //printf("x%d = %.3lf\n", i+1, s->matrice[i][s->n]); // Affichage pour débogage
    }
}

void systeme_output(systeme_t* s, char* pathFile, int boolAffichage) {
    FILE *fichier = fopen(pathFile, "w+");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur: impossible d'ouvrir le fichier\n");
        exit(1);
    }
    // ecriture de la taille de la matrice
    fprintf(fichier, "%d\n", s->n);

    // écriture de la matrice supérieur sans les 0
    // for (int i = 0; i < s->n; i++) {
    //     for (int j = 0; j < s->n+1; j++) {
    //         if (i <= j)
    //             fprintf(fichier, "%lf ", s->matrice[i][j]);
    //     }
    //     fprintf(fichier, "\n");
    // }

    // écriture des résultats (remontée de Gauss)
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
