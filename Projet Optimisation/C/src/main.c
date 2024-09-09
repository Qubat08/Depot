#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>

#include "probleme.h"
#include "simplexe.h"
#include "graphe.h"
#include "arete.h"


int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <type> <type_file> <nom_fichier> <boolAffichage>\n", argv[0]);
        return -1;
    }
    int type, type_file;

    type = atoi(argv[1]);
    type_file = atoi(argv[2]);
    char pathFile[50];

    int boolAffichage = atoi(argv[4]);
    clock_t start, end;
    // Sac à dos
    if (type == 0){
        prob_t probleme;
        sprintf(pathFile, "./data/sac/%s.txt", argv[3]);
        if (type_file == 0){
            if (!lire_probleme(pathFile, &probleme)){
                if (boolAffichage)
                afficher_probleme(&probleme);
                start = clock();
                int* tabHeuristique = calculHeuristique(&probleme);
                double somme = 0;
                for (int i = 0; i < probleme.n_var; i++) {
                    somme += tabHeuristique[i] * probleme.fonc_obj[i];
                    if (boolAffichage)
                    printf("x%d = %d\n", i+1, tabHeuristique[i]);
                }
                if (boolAffichage)
                printf("Borne Intiale : %lf\n", somme);
                int test = separation_evaluation(&probleme, somme, boolAffichage);
                end = clock();
                if (test == 0){
                    printf("Solution initiale : \n");
                    for (int i = 0; i < probleme.n_var; i++) {
                        if (tabHeuristique[i] != 0)
                            printf("x%d = %d\n", i+1, tabHeuristique[i]);
                    }
                    printf("Valeur de la solution initiale : %.3lf\n", somme);
                }

                printf("Temps d'execution : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
                }
        }
        else if (type_file == 1){
            lire_gros_probleme(pathFile, &probleme);
            if (boolAffichage)
            afficher_probleme(&probleme);
            start = clock();
            int* tabHeuristique = calculHeuristique(&probleme);
            double somme = 0;
            for (int i = 0; i < probleme.n_var; i++) {
                somme += tabHeuristique[i] * probleme.fonc_obj[i];
                if (boolAffichage)
                printf("x%d = %d\n", i+1, tabHeuristique[i]);
            }
            if (boolAffichage)
            printf("Borne Intiale : %lf\n", somme);
            separation_evaluation(&probleme, somme, boolAffichage);
            end = clock();
            printf("Temps d'execution : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
        }
    }
    else if (type == 1){ // TSP
        graphe g;
        arete ** tabArete;
        clock_t start, end;
        if (type_file == 0){
            sprintf(pathFile, "./data/tsp/%s.txt", argv[3]);
            initGraphe(&g, pathFile);
       // afficherGraphe(g);
      } else if (type_file == 1){
        sprintf(pathFile, "./data/tsp/%s.tsp", argv[3]);
        initGrosGraphe(&g, pathFile);
      }
        start = clock();
        tabArete = trier_aretes(&g);
        fonctionEvaluation(&g, boolAffichage);
        end = clock();
        printf("Temps d'execution : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
        detruireGraphe(&g);
    }
    else{
        printf("Type non reconnu %d\n", type);
        return -1;
    }
    return 0;
}