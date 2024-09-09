#include "simplexe.h"
#include "probleme.h"
#include "pile.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <glpk.h>
#include <math.h>

int* calculHeuristique(prob_t* probleme)
{
    int* heuristique = (int*)malloc((probleme->n_var) * sizeof(int));
    double* coef = (double*)malloc(probleme->n_var * sizeof(double));

    if (coef == NULL) {
        printf("Failed to allocate memory");
        exit(1);
    }
    int* boolDejaPris = (int*)calloc(probleme->n_var, sizeof(int));
    if (boolDejaPris == NULL) {
        printf("Failed to allocate memory");
        free(coef);
        exit(1);
    }


    for (int i = 0; i < probleme->n_var; i++) {
        if (probleme->a[0][i] != 0) {
            coef[i] = probleme->fonc_obj[i] / probleme->a[0][i];
        } else {
            coef[i] = 0;
        }
    }

    double capacite_restante = probleme->b[0];


    for (int i = 0; i < probleme->n_var && capacite_restante > 0; i++) {
        int indiceMax = -1;
        double max_rapport = -1;
        for (int j = 0; j < probleme->n_var; j++) {
            if (!boolDejaPris[j] && coef[j] > max_rapport) {
                max_rapport = coef[j];
                indiceMax = j;
            }
        }

        if (indiceMax == -1) break;


        int quantite = (int)(capacite_restante / probleme->a[0][indiceMax]);
        heuristique[indiceMax] = quantite;
        capacite_restante -= probleme->a[0][indiceMax] * quantite;

        boolDejaPris[indiceMax] = 1;
    }
    return heuristique;

    free(coef);
    free(boolDejaPris);
}

void affichage(prob_t probleme){
    printf("\n========================\n");
    printf("Valeur : %.3lf\n", probleme.solution[0]);
    for (int i = 1; i < probleme.n_var + 1; i++)
    {
        if (probleme.solution[i] != 0)
            printf("x%d : %.3lf\n", i, probleme.solution[i]);
    }
    printf("========================\n");
}

void evaluationMethod(prob_t* probleme, int boolAffichage) {
    glp_prob *lp;
    int* ia = (int*)malloc((probleme->n_cont * probleme->n_var + 1) * sizeof(int));
    int* ja = (int*)malloc((probleme->n_cont * probleme->n_var + 1) * sizeof(int));
    double* ar = (double*)malloc((probleme->n_cont * probleme->n_var + 1) * sizeof(double));

    probleme->solution = (double*)malloc((1 + probleme->n_var) * sizeof(double));

    if (ia == NULL || ja == NULL || ar == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        free(ia);
        free(ja);
        free(ar);
        return;
    }

    // Création du problème
    lp = glp_create_prob();
    if (boolAffichage == 0){
        glp_term_out(GLP_OFF);
    }
    else if (boolAffichage == 1){
        glp_term_out(GLP_ON);
    }

    glp_set_prob_name(lp, "probleme");
    glp_set_obj_dir(lp, probleme->type_opt == 0 ? GLP_MIN : GLP_MAX);

    // Ajout des contraintes
    glp_add_rows(lp, probleme->n_cont);
    for (int i = 0; i < probleme->n_cont; i++) {
        glp_set_row_bnds(lp, i + 1, GLP_UP, 0.0, probleme->b[i]);
    }

    // Ajout des variables et application des fixations
    glp_add_cols(lp, probleme->n_var);
    for (int i = 0; i < probleme->n_var; i++) {
        if (probleme->valFixe != NULL && probleme->valFixe[i] != -1) {
            glp_set_col_bnds(lp, i + 1, GLP_FX, (double)probleme->valFixe[i], (double)probleme->valFixe[i]);
        } else {
            glp_set_col_bnds(lp, i + 1, GLP_LO, 0.0, 0.0);
        }
        glp_set_obj_coef(lp, i + 1, probleme->fonc_obj[i]);
    }

    // Chargement de la matrice de contraintes
    int k = 1;
    for (int i = 0; i < probleme->n_cont; i++) {
        for (int j = 0; j < probleme->n_var; j++) {
            ia[k] = i + 1;
            ja[k] = j + 1;
            ar[k] = probleme->a[i][j];
            k++;
        }
    }

    glp_load_matrix(lp, k - 1, ia, ja, ar);
    glp_simplex(lp, NULL);

    // Stockage des résultats
    probleme->solution[0] = glp_get_obj_val(lp);
    for (int i = 0; i < probleme->n_var; i++) {
        probleme->solution[i + 1] = glp_get_col_prim(lp, i + 1);
    }

    // Libération des ressources
    free(ia);
    free(ja);
    free(ar);
    glp_delete_prob(lp);
}

int verification_probleme(prob_t* prob, double* solution){
    int fix_needed = 0;
    double intpart;

    // Vérifier et fixer les valeurs non entières
    for (int i = 1; i <= prob->n_var; i++) {
        if (modf(solution[i], &intpart) != 0.0) {
            fix_needed = 1;
            prob->valFixe[i-1] = (int)solution[i];
        }
    }

    return fix_needed;
}

int separation_evaluation(prob_t* probleme, double borneInitiale, int boolAffichage){
    pile_t* pile = creer_pile();
    double meilleureValeur = borneInitiale;
    prob_t* meilleureSolution = NULL;

    
    probleme->valFixe = (int*)malloc(probleme->n_var * sizeof(int));
    for (int i = 0; i < probleme->n_var; i++) {
        probleme->valFixe[i] = -1;
    }

    probleme->visited = (int*)malloc((probleme->n_var) * sizeof(int));
    for (int i = 0; i < probleme->n_var; i++) {
        probleme->visited[i] = 0;
    }
    // calcul de la racine
    evaluationMethod(probleme, boolAffichage);
    //affichage(*probleme);
    empiler(&pile, probleme);
    int iter = 0;
    while(!pile_vide(pile)){
    if (boolAffichage)
        printf("Iteration %d\n", iter);
        iter++;
        prob_t* probCurrent = depiler(&pile);
       
        evaluationMethod(probCurrent, boolAffichage);

        if (probCurrent->solution[0] > meilleureValeur){
            int boolEntier = verification_probleme(probCurrent, probCurrent->solution);
            //affichage(*probCurrent);
            if (!boolEntier){
                // solution exacte
                meilleureValeur = probCurrent->solution[0];
                meilleureSolution = copie_profonde_prob_t(probCurrent);
            }
            else {
                // solution non exacte
                int indice = visited_variable(probCurrent);
                
                for (int j = 0; j < probCurrent->valFixe[indice]+1; j++){ 
                    prob_t* probNew = copie_profonde_prob_t(probCurrent);
                    probNew->valFixe[indice] = j;
                    empiler(&pile, probNew);
                }
            }
        }
    }
    // Afficher la meilleure solution trouvée
    if (meilleureSolution != NULL) {
        printf("Meilleure solution trouvée:");
        affichage(*meilleureSolution);
        detruire_pile(&pile);
        return 1;
    } else {
        printf("\nAucune solution améliorant la borne initiale de %.3lf n'a été trouvée.\n", borneInitiale);
        return 0;
    }
    return 1;
}

int visited_variable(prob_t *probleme)
{
    int i;
    for (i = 0; i < probleme->n_var; i++)
    {
        if (probleme->visited[i] != 1 && probleme->valFixe[i] != -1)
        { 
            probleme->visited[i] = 1;
            break;
        }
    }
    return i;
}

prob_t* copie_profonde_prob_t(prob_t* source) {
    prob_t* destination = malloc(sizeof(prob_t));
    if (!destination) return NULL;

    *destination = *source; 

    // Allocation et copie de chaque tableau
    destination->fonc_obj = malloc(source->n_var * sizeof(double));
    memcpy(destination->fonc_obj, source->fonc_obj, source->n_var * sizeof(double));

    destination->a = malloc(source->n_cont * sizeof(double*));
    for (int i = 0; i < source->n_cont; i++) {
        destination->a[i] = malloc(source->n_var * sizeof(double));
        memcpy(destination->a[i], source->a[i], source->n_var * sizeof(double));
    }

    destination->b = malloc(source->n_cont * sizeof(double));
    memcpy(destination->b, source->b, source->n_cont * sizeof(double));

    destination->signe_cont = malloc(source->n_cont * sizeof(int));
    memcpy(destination->signe_cont, source->signe_cont, source->n_cont * sizeof(int));

    destination->solution = malloc((source->n_var + 1) * sizeof(double));
    memcpy(destination->solution, source->solution, (source->n_var + 1) * sizeof(double));

    destination->valFixe = malloc(source->n_var * sizeof(int));
    memcpy(destination->valFixe, source->valFixe, source->n_var * sizeof(int));

    destination->visited = malloc(source->n_var * sizeof(int));
    memcpy(destination->visited, source->visited, source->n_var * sizeof(int));

    return destination;
}