#include "systeme.h"
#include <ctype.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 256

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
         int temp =  fscanf(fichier, "%lf", &s->matrice[i][j]);
        }
    }

    fclose(fichier);
}

void systeme_afficher(systeme_t s) {
    printf("======Affichage du système:======\n");
    for (int i = 0; i < s.n; i++) {
        for (int j = 0; j < s.n + 1; j++) {
            printf("%lf ", s.matrice[i][j]);
        }
        printf("\n");
    }
}

__device__ void systeme_echanger_lignes(double* d_matrice, int n, int iter, int i) {
    double tmp;
    for (int j = 0; j < n + 1; j++) {
        tmp = d_matrice[iter * (n + 1) + j];
        d_matrice[iter * (n + 1) + j] = d_matrice[i * (n + 1) + j];
        d_matrice[i * (n + 1) + j] = tmp;
    }
}

__global__ void solve_system(double* d_matrice, int n) {
    extern __shared__ double shared[];

    for (int iter = 0; iter < n - 1; iter++) {
        int idx = threadIdx.x + blockIdx.x * blockDim.x;

        // Sélection du pivot
        double max_val = fabs(d_matrice[iter * (n + 1) + iter]);
        int pivot_row = iter;
        for (int i = iter + 1; i < n; i++) {
            double val = fabs(d_matrice[i * (n + 1) + iter]);
            if (val > max_val) {
                max_val = val;
                pivot_row = i;
            }
        }

        // Échange des lignes si nécessaire
        if (pivot_row != iter) {
            if (idx == 0) {
                systeme_echanger_lignes(d_matrice, n, iter, pivot_row);
            }
            __syncthreads();
        }

//         // afficher matrice
//         if (idx == 0) {
//             printf("Matrice après échange de lignes:\n");
//             for (int i = 0; i < n; i++) {
//                 for (int j = 0; j < n + 1; j++) {
//                     printf("%lf ", d_matrice[i * (n + 1) + j]);
//                 }
//                 printf("\n");
//             }
//             printf("\n");
//         }

        // Copie la ligne pivot dans la mémoire partagée
        if (threadIdx.x < n + 1 && idx < n+1) {
            shared[threadIdx.x] = d_matrice[iter * (n + 1) + threadIdx.x];
        }
        __syncthreads();

        // Normalise la ligne pivot
        double pivot = shared[iter];
        if (pivot == 0.0) continue; // Évite la division par zéro
        if (threadIdx.x < n + 1) {
            shared[threadIdx.x] /= pivot;
            d_matrice[iter * (n + 1) + threadIdx.x] = shared[threadIdx.x];
        }
        __syncthreads();

        // Soustraction des lignes
        if (idx >= iter + 1 && idx < n) {
            double coef = d_matrice[idx * (n + 1) + iter];
            for (int j = iter; j < n + 1; j++) {
                d_matrice[idx * (n + 1) + j] -= coef * shared[j];
            }
        }
        __syncthreads();

//         // afficher matrice
//         if (idx == 0) {
//             printf("Matrice après soustraction des lignes:\n");
//             for (int i = 0; i < n; i++) {
//                 for (int j = 0; j < n + 1; j++) {
//                     printf("%lf ", d_matrice[i * (n + 1) + j]);
//                 }
//                 printf("\n");
//             }
//             printf("\n");
//         }



        // Copie les résultats de la mémoire partagée vers la matrice
        if (threadIdx.x < n + 1 && idx < n) {
            d_matrice[iter * (n + 1) + threadIdx.x] = shared[threadIdx.x];
        }
        __syncthreads();
    }
}

void systeme_resoudre(systeme_t *s, int boolAffichage) {
    int size = s->n * (s->n + 1) * sizeof(double);
    double* d_matrice;
    int nbBlocks = (s->n + BLOCK_SIZE - 1) / BLOCK_SIZE;
    size_t sharedSize = (s->n + 1) * sizeof(double);

    // Copie les données vers le GPU
    cudaError_t err = cudaMalloc((void**)&d_matrice, size);
    if (err != cudaSuccess) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour d_matrice\n");
        exit(1);
    }
    err = cudaMemcpy(d_matrice, s->m, size, cudaMemcpyHostToDevice);
    if (err != cudaSuccess) {
        fprintf(stderr, "Erreur de copie de mémoire pour d_matrice\n");
        exit(1);
    }

    // Lance le kernel avec le nombre de blocs optimal
    solve_system<<<s->n, s->n+1, sharedSize>>>(d_matrice, s->n);
    cudaDeviceSynchronize();

    // Copie les données de retour vers le CPU
    err = cudaMemcpy(s->m, d_matrice, size, cudaMemcpyDeviceToHost);
    if (err != cudaSuccess) {
        fprintf(stderr, "Erreur de copie de mémoire pour s->m\n");
        exit(1);
    }

    cudaFree(d_matrice);

    if (boolAffichage == 1) {
        systeme_afficher(*s);
    }
}

void systeme_remontee_de_gauss(systeme_t* s) {
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
            printf("x%d = %.3lf\n", i + 1, s->matrice[i][s->n]);
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
