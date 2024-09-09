#include "graphe.h"
#include <limits.h>
#include <unistd.h>
#include "file.h"
#include <math.h>

// fonction qsort pour trier les arêtes
int compare_aretes(const void *a, const void *b)
{
    return (*(arete **)a)->poids - (*(arete **)b)->poids;
}

// initialisation du graphe
void initGraphe(graphe *g, char *nom_file)
{

    FILE *fichier;
    fichier = fopen(nom_file, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }
    char str1[20];
    char ch_temp[20];
    int test = 0;
    int i = 0, j = 0, k = 0;
    g->nbaretes = 0;

    if (fichier != NULL)
    {
        // LECTURE 3 PREMIERES LIGNES
        fscanf(fichier, "%s %d", ch_temp, &g->nb_sommets);
        fscanf(fichier, "%s %d", ch_temp, &g->oriente);
        fscanf(fichier, "%s %d", ch_temp, &g->value);

        // MALLOC M_STOCKAGE et M_ADJ
        g->m_stockage = (int *)malloc(sizeof(int) * g->nb_sommets * g->nb_sommets);
        g->m_adj = (int **)malloc(sizeof(int *) * g->nb_sommets);
        for (int i = 0; i < g->nb_sommets; i++)
        {
            g->m_adj[i] = &g->m_stockage[i * g->nb_sommets];
        }
        // MALLOC L_ADJ
        // g->l_adj = (liste2C *)malloc(sizeof(liste2C *) * g->nb_sommets);
        // for (i = 0; i < g->nb_sommets; i++)
        // {
        //     initListe(&g->l_adj[i]);
        // }
        // i = 0;
        fscanf(fichier, "%s", ch_temp); /*DEBUT_DEF_ARETES */

        // Creation arretes
        // MALLOC ARRETES
        g->aretes = (arete **)malloc(sizeof(arete *) * g->nb_sommets * g->nb_sommets);
        for (i = 0; i < g->nb_sommets * g->nb_sommets; i++)
        {
            g->aretes[i] = NULL;
        }

        int cpt = 0;
        do
        {

            fscanf(fichier, "%s", ch_temp);
            if (strcmp(ch_temp, "FIN_DEF_ARETES"))
            {
                i = atoi(ch_temp);         // origine
                fscanf(fichier, "%d", &j); // extremite
                if (g->value == 1)
                {
                    fscanf(fichier, "%d", &k); // poids
                }
                arete *newAre = (arete *)malloc(sizeof(arete));
                newAre->extremite = j;
                newAre->origine = i;
                newAre->poids = k;
                newAre->bloque = 0;
                g->aretes[cpt] = newAre; // insertion dans le tableau d'arrete
                g->nbaretes += 1;
                cpt++;

                g->m_stockage[i * g->nb_sommets + j] = k;
                // cellule *c = (cellule *)malloc(sizeof(cellule));
                // initCellule(c, j, k);

                // inserer_liste(&g->l_adj[i], c);
                if (g->oriente == 0)
                {
                    g->m_stockage[j * g->nb_sommets + i] = k;
                    // cellule *d = (cellule *)malloc(sizeof(cellule));
                    // initCellule(d, i, k);

                    // inserer_liste(&g->l_adj[j], d);
                }
            }
            else
            {
                test = 1;
            }
        } while (test == 0);
    }
    fclose(fichier);
}

void initGrosGraphe(graphe* g, char* nom_file){
    FILE *fichier = fopen(nom_file, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    char line[256];
    int nb_sommets = 0;
    int reading_nodes = 0;

    // Lire les informations du fichier
    while (fgets(line, sizeof(line), fichier)) {
        if (strncmp(line, "DIMENSION", 9) == 0) {
            sscanf(line, "DIMENSION : %d", &nb_sommets);
            g->nb_sommets = nb_sommets;
        } else if (strncmp(line, "NODE_COORD_SECTION", 18) == 0) {
            reading_nodes = 1;
            break;
        }
    }

    // Allouer de la mémoire pour m_stockage et m_adj
    g->m_stockage = (int *)malloc(sizeof(int) * g->nb_sommets * g->nb_sommets);
    g->m_adj = (int **)malloc(sizeof(int *) * g->nb_sommets);
    for (int i = 0; i < g->nb_sommets; i++) {
        g->m_adj[i] = &g->m_stockage[i * g->nb_sommets];
    }

    // Initialiser la matrice d'adjacence à zéro
    for (int i = 0; i < g->nb_sommets; i++) {
        for (int j = 0; j < g->nb_sommets; j++) {
            g->m_adj[i][j] = 0;
        }
    }

    // Lire les coordonnées des nœuds et calculer les distances
    float *x_coords = (float *)malloc(sizeof(float) * g->nb_sommets);
    float *y_coords = (float *)malloc(sizeof(float) * g->nb_sommets);
    int index = 0;

    for (int i = 0; i < g->nb_sommets; i++) {
        if (fgets(line, sizeof(line), fichier) && reading_nodes) {
            int node;
            float x, y;
            sscanf(line, "%d %f %f", &node, &x, &y);
            x_coords[node - 1] = x;
            y_coords[node - 1] = y;
        }
    }

    // Calculer les distances euclidiennes et remplir la matrice d'adjacence
    g->nbaretes = (g->nb_sommets * (g->nb_sommets - 1)) / 2;
    g->aretes = (arete **)malloc(sizeof(arete *) * g->nbaretes);
    int arete_index = 0;

    for (int i = 0; i < g->nb_sommets; i++) {
        for (int j = i + 1; j < g->nb_sommets; j++) {
            float x1 = x_coords[i];
            float y1 = y_coords[i];
            float x2 = x_coords[j];
            float y2 = y_coords[j];
            int distance = (int)(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) * 1000 + 0.5);
            g->m_adj[i][j] = distance;
            g->m_adj[j][i] = distance;

            // Créer une nouvelle arête et l'ajouter à g->aretes
            arete *newArete = (arete *)malloc(sizeof(arete));
            newArete->origine = i;
            newArete->extremite = j;
            newArete->poids = distance;
            newArete->bloque = 0;
            g->aretes[arete_index++] = newArete;
        }
    }

    free(x_coords);
    free(y_coords);

    // Fermeture du fichier
    fclose(fichier);
}





// trie les arêtes par poids
arete **trier_aretes(graphe *g)
{
    qsort(g->aretes, g->nbaretes, sizeof(arete *), compare_aretes);
    return g->aretes;
}

// affichage du graphe
void afficherGraphe(graphe g)
{
    if (g.nb_sommets != 0)
    {
        // printf("NB sommets : %d \n", g.nb_sommets);
        // printf("Oriente: %d \n", g.oriente);
        // printf("Value : %d \n", g.value);
        // printf("Liste d'adjacences : \n");
        // for (int i = 0; i < g.nb_sommets; i++)
        // {
        //     printf("%d :", i);
        //     afficherListe(g.l_adj[i]);
        // }
        // printf("\nMatrice d'adjacences:\n");

//         for (int i = 0; i < g.nb_sommets; i++)
//         {
//             for (int j = 0; j < g.nb_sommets; j++)
//             {
//                 printf("%d ", g.m_stockage[i * g.nb_sommets + j]);
//             }
//             printf("\n");
//         }
        printf("\nAretes : %d\n", g.nbaretes);
        for (int i = 0; i < g.nbaretes; i++)
        {
            afficherArete(g.aretes[i]);
        }
    }
    else
    {
        printf("\nGraphe Vide \n");
    }
}

// libération de la mémoire allouée pour le graphe
void detruireGraphe(graphe *g)
{
    g->nb_sommets = 0;
    g->oriente = 0;
    g->value = 0;
    free(g->m_stockage);
    // for (int i = 0; i < g->nb_sommets; i++)
    // {
    //     viderListe(&g->l_adj[i]);
    // }

    free(g->aretes);
    // free(g->l_adj);
    free(g->m_adj);
    if (g->solutions != NULL)
    {
        free(g->solutions);
    }
}

// fonction qui génère un arbre couvrant minimal en excluant les arêtes bloquées et 0
arete** generer_acpm_kruskal_sans_0_tableau(arete **a, int taille, int nbaretes)
{
    int cc[taille];
    int b = 0;
    int j = 0;
    int k = 0;
    int poids = 0;
    int icc = 0;
    arete **tabArete = (arete **)malloc(sizeof(arete *) * taille);
    for (int i = 0; i < taille; i++)
    {
        cc[i] = i;
    }

    for (int j = 0; j < nbaretes; j++)
    {
        if ( a[j]->bloque != 1){
            if (a[j]->origine != 0 && a[j]->extremite != 0){
                if (cc[a[j]->origine] != cc[a[j]->extremite])
                {
                    tabArete[b] = a[j];
                    poids += a[j]->poids;
                    icc = cc[a[j]->extremite];
                    b++;
                    
                    for (int l = 0; l < taille; l++)
                    {
                        if (cc[l] == icc)
                        {
                            cc[l] = cc[a[j]->origine];
                        }
                    }
                }
            }
        }
       
        
    }
    
    // printf("Reponse : \n");
    // for (int i = 0; i < taille; i++)
    // {
    //     afficherArete(tabArete[i]);
    // }
   // printf("Poids: %d \n", poids);

    return tabArete;
}

// ajout des 2 plus petites aretes de 0
arete** ajoutareteavec0(arete **a, arete **kruskalTab, int taille, int nbaretes) {
    // Allocation de mémoire pour le tableau des arêtes du sommet 0
    arete **tabArete = (arete **)malloc(sizeof(arete *) * taille);
    if (tabArete == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour tabArete\n");
        exit(EXIT_FAILURE);
    }

    // Allocation de mémoire pour le tableau résultant
    arete **resTab = (arete **)malloc(sizeof(arete *) * taille);
    if (resTab == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour resTab\n");
        exit(EXIT_FAILURE);
    }

    // Copie des arêtes de kruskalTab vers resTab
    for (int i = 0; i < taille - 2; i++) {
        resTab[i] = kruskalTab[i];
    }

    // Remplissage du tableau tabArete avec les arêtes du sommet 0
    int b = 0;
    for (int i = 0; i < nbaretes; i++) {
        if ((a[i]->origine == 0 || a[i]->extremite == 0)) {
            tabArete[b] = a[i];
            b++;
        }
    }

    // Tri du tableau tabArete selon les poids des arêtes
    qsort(tabArete, b, sizeof(arete *), compare_aretes);
   

    // printf("DEBUG: Arêtes du sommet 0\n");
    // for (int i = 0; i < b; i++) { 
    //         afficherArete(tabArete[i]);
    // }
    // printf("FIN DEBUG \n");

    if (b < 2) {
        fprintf(stderr, "Erreur: moins de 2 arêtes pour le sommet 0\n");
        exit(EXIT_FAILURE);
    }

    // Ajout des deux premières arêtes non bloquées du tableau tabArete à resTab
    int cpt = 0;
    for (int i = 0; i < b; i++) {
        if (tabArete[i]->bloque == 0) {
            resTab[taille - 2 + cpt] = tabArete[i];
            cpt++;
        }
        if (cpt == 2) {
            break;
        }
    }

    // Libération de la mémoire allouée pour tabArete
    free(tabArete);

    return resTab;
}

// calcul de la borne initiale par la méthode Heuristique du plus proche voisin
int  calculBorneInitiale(graphe g, int sommetDepart)
{
    int sommetActuel = sommetDepart;
    int poids = 0;
    int nbSommets = g.nb_sommets;
    int *marque = (int *)malloc(sizeof(int) * nbSommets);
    // printf("Sommet actuel : %d ", sommetDepart);
    for (int i = 0; i < nbSommets; i++)
    {
        marque[i] = 0;
    }
    marque[sommetActuel] = 1;
    for (int i = 0; i < nbSommets - 1; i++)
    {
        int min = INT_MAX;
        int sommetSuivant = -1;
        for (int j = 0; j < nbSommets; j++)
        {
            if (marque[j] == 0 && g.m_stockage[sommetActuel * nbSommets + j] < min)
            {
                min = g.m_stockage[sommetActuel * nbSommets + j];
                sommetSuivant = j;
            }
        }
        marque[sommetSuivant] = 1;
        poids += min;
        sommetActuel = sommetSuivant;
        
        // printf("%d ", sommetActuel);
    }
    // printf("%d\n", sommetDepart);
    poids += g.m_stockage[sommetActuel * nbSommets + sommetDepart];
    // printf("Borne initiale : %d\n", poids);
    free(marque);
    return poids;
}

// fonction qui vérifie si un graphe est hamiltonien (degré de chaque sommet = 2)
int estHamiltonien(arete** solution, int taille){
    int *degre = (int *)malloc(sizeof(int) * taille);
    for (int i = 0; i < taille; i++)
    {
        degre[i] = 0;
    }
    for (int i = 0; i < taille; i++)
    {
        degre[solution[i]->origine] += 1;
        degre[solution[i]->extremite] += 1;
    }
    for (int i = 0; i < taille; i++)
    {
        if (degre[i] != 2)
        {
            //printf("Le graphe n'est pas hamiltonien\n");
            return 0;
        }
    }
    //printf("Le graphe est hamiltonien\n");
    return 1;

}

// fonction qui retourne un tableau de degré pour tous les sommets
int* trouverLeSommetDegreSup2(arete** solutions, int taille){
    int *degre = (int *)malloc(sizeof(int) * taille);
    for (int i = 0; i < taille; i++)
    {
        degre[i] = 0;
    }
    for (int i = 0; i < taille; i++)
    {
        degre[solutions[i]->origine] += 1;
        degre[solutions[i]->extremite] += 1;
    }
    return degre;

}

// trouve l'indice du sommet qui a un degré supérieur à 2
int trouverIndiceSommetDegreSup2(int *degre, int taille){
    for (int i = 0; i < taille; i++)
    {
        if (degre[i] > 2)
        {
            return i;
        }
    }
    return -1;
}

// trouve les arêtes incidentes à un sommet
arete*** areteIncidente(arete** solutions, int sommet, int degre, int nbSommet){
    arete ***tabArete = (arete ***)malloc(sizeof(arete **) * degre);
    int cpt = 0;
    for (int i = 0; i < nbSommet; i++)
    {
        if (solutions[i]->origine == sommet || solutions[i]->extremite == sommet)
        {
            tabArete[cpt] = &solutions[i];
            cpt++;
        }
    }
    return tabArete;
}

// fonction qui évalue la racine
void evaluerRacine(graphe *g, int boolAffichage) {
    if (boolAffichage)
     printf("Évaluation de la racine...\n");

    // Réinitialiser le poids à 0 chaque fois que cette fonction est appelée
    g->poidsSolutions = 0;

    // Générer un arbre couvrant minimal en excluant les arêtes bloquées
    g->solutions = generer_acpm_kruskal_sans_0_tableau(g->aretes, g->nb_sommets, g->nbaretes);

    // Ajouter les meilleures arêtes du sommet 0 pour former un cycle potentiellement hamiltonien
    g->solutions = ajoutareteavec0(g->aretes, g->solutions, g->nb_sommets, g->nbaretes);

    // Calculer le poids total des arêtes dans la solution
    for (int i = 0; i < g->nb_sommets; i++) {
        if (g->solutions[i] != NULL) {
            g->poidsSolutions += g->solutions[i]->poids;
            if (boolAffichage)
             afficherArete(g->solutions[i]);  // Supposé afficher les détails de chaque arête
        }
    }
     if (boolAffichage)
     printf("Poids total de la solution générée : %d\n", g->poidsSolutions);
}

// fonction qui bloque une arête
void bloquerArete(graphe* graphe, arete* arete){

    // Rechercher dans le tableau du graphe l'arrete et la bloquer
    for (int i = 0; i < graphe->nbaretes; i++)
    {
        if (graphe->aretes[i]->origine == arete->origine && graphe->aretes[i]->extremite == arete->extremite)
        {
            graphe->aretes[i]->bloque = 1;
        }
    }

}

// fonction qui débloque une arête
void debloquerArete(graphe* graphe, arete* arete){

    // Rechercher dans le tableau du graphe l'arrete et la bloquer
    for (int i = 0; i < graphe->nbaretes; i++)
    {
        if (graphe->aretes[i]->origine == arete->origine && graphe->aretes[i]->extremite == arete->extremite)
        {
            graphe->aretes[i]->bloque = 0;
        }
    }

}

// fonction qui fait le branch and bound
void fonctionEvaluation(graphe *g, int boolAffichage) {
    Tas_t *file = (Tas_t *)malloc(sizeof(Tas_t));

    initTas(file, 1000); // Initialiser la file
    int borneInitiale = calculBorneInitiale(*g, 0);  // Calculer la borne initiale
    if (boolAffichage)
        printf("Borne initiale : %d\n", borneInitiale);
    element_t element;
    graphe* meilleurGraphe = NULL;
    // Évaluer la racine et l'insérer dans la file
    evaluerRacine(g, boolAffichage);
    if (boolAffichage)
    printf("=====================================================\n");
    element.sommet = g->poidsSolutions;
    element.g = copieGraphe(g);
    insererElement(file, element);
    
    while (file->size > 0) {
        //afficherTas(file);
        element_t currentElement = extraire_min(file);
        graphe *currentGraphe = currentElement.g;

        if (currentGraphe->poidsSolutions < borneInitiale){
            int *degre = trouverLeSommetDegreSup2(currentGraphe->solutions, g->nb_sommets);
            int sommetDegreSup2 = trouverIndiceSommetDegreSup2(degre, g->nb_sommets); // trouve le sommet qui a degre > 2
            arete ***aretesIncidentes = areteIncidente(currentGraphe->solutions, sommetDegreSup2, degre[sommetDegreSup2], currentGraphe->nb_sommets);
            if (boolAffichage){
            printf("Sommet de degre > 2 : %d (%d)\n ", sommetDegreSup2, degre[sommetDegreSup2]);
            // printf("Arêtes incidentes : \n");
            // for (int i = 0; i < degre[sommetDegreSup2]; i++) {
            //     afficherArete(*aretesIncidentes[i]);
            // }
            printf("=====================================================\n");
            
             printf("Generation des fils...\n");
             }
            for (int i = 0; i < degre[sommetDegreSup2]; i++) {
                if (boolAffichage)
                 printf("Numéro : %d\n", i);
                // Afficher l'état avant blocage
                // (*aretesIncidentes[i])->bloque = 1;  // Bloquer l'arête
                // printf("Arrete à bloquer: ");
                // afficherArete(*aretesIncidentes[i]);
                bloquerArete(currentGraphe, *aretesIncidentes[i]);

                // afficher toutes les arretes du graphe bloquées
                if (boolAffichage){
                    printf("Arretes bloquées: \n");
                    for (int j = 0; j < currentGraphe->nbaretes; j++) {
                        if (currentGraphe->aretes[j]->bloque == 1){
                            afficherArete(currentGraphe->aretes[j]);
                        }
                    }
                }


                // Evaluation des fils 
                currentGraphe->solutions = generer_acpm_kruskal_sans_0_tableau(currentGraphe->aretes, currentGraphe->nb_sommets, g->nbaretes);
                // Ajouter les meilleures arêtes du sommet 0 pour former un cycle potentiellement hamiltonien
                currentGraphe->solutions = ajoutareteavec0(currentGraphe->aretes, currentGraphe->solutions, currentGraphe->nb_sommets, currentGraphe->nbaretes);
                if (boolAffichage)
                    printf("Solution: \n");
                int sommeActuel = 0;
                for (int j = 0; j < currentGraphe->nb_sommets; j++) {
                    if (boolAffichage)
                        afficherArete(currentGraphe->solutions[j]);
                    sommeActuel += currentGraphe->solutions[j]->poids;
                }
                 currentGraphe->poidsSolutions = sommeActuel;
                if (boolAffichage){
                    printf("Poids total: %d\n", sommeActuel);
                    printf("=====================================================\n");
                }

                // Insérer les fils dans la file si leur évaluation est inférieure à la borne
                if (currentGraphe->poidsSolutions < borneInitiale) {
                    if (estHamiltonien(currentGraphe->solutions, currentGraphe->nb_sommets)) {
                    borneInitiale = currentGraphe->poidsSolutions;
                    if (boolAffichage){
                        printf("=====================================================\n");
                        printf("Nouvelle borne trouvée : %d\n", borneInitiale);
                        printf("Solution actuelle : \n");
                        for (int i = 0; i < currentGraphe->nb_sommets; i++) {
                            afficherArete(currentGraphe->solutions[i]);
                        }
                        printf("=====================================================\n");
                    }
                    //Sauvegarde de la meilleure solution pour affichage à la fin
                    meilleurGraphe = copieGraphe(currentGraphe);
                    } else{
                        if (boolAffichage){
                            printf("Non_hamiltonien\n");
                        }
                        element_t newElement;
                        newElement.sommet = sommeActuel;
                        newElement.g = copieGraphe(currentGraphe);
                        insererElement(file, newElement);
                        entasser_min(file, file->size - 1);
                    }

                }
                else{
                    // printf("Fils non inséré dans la file car poids > borne\n");
                    //detruireGraphe(currentGraphe);
                }
                // Débloquer l'arête pour le prochain fils
                debloquerArete(currentGraphe, *aretesIncidentes[i]);
            }
        }

    }
    detruireTas(file);  // Nettoyer la file

    // Afficher la meilleure solution
    printf("=====================================================\n");
   
    int poids =0;
    if (meilleurGraphe == NULL){
        printf("Aucune solution trouvée\n");
    }
    else{
        printf("Meilleure solution trouvée : \n");
        printf("%d \n", meilleurGraphe->nb_sommets);
        for (int i = 0; i < meilleurGraphe->nb_sommets; i++) {
            afficherArete(meilleurGraphe->solutions[i]);
            poids += meilleurGraphe->solutions[i]->poids;
        }

        printf("Poids total de la solution : %d\n", poids);
    }
    printf("=====================================================\n");

}

// fonction qui copie un graphe
graphe *copieGraphe(graphe *src) {
    if (!src) return NULL;

    graphe *dest = malloc(sizeof(graphe));
    if (!dest) return NULL;

    dest->nb_sommets = src->nb_sommets;
    dest->oriente = src->oriente;
    dest->value = src->value;
    dest->nbaretes = src->nbaretes;
    dest->poidsSolutions = src->poidsSolutions;

    // Copie du tableau de stockage
    dest->m_stockage = malloc(sizeof(int) * src->nb_sommets * src->nb_sommets);
    if (dest->m_stockage) {
        memcpy(dest->m_stockage, src->m_stockage, sizeof(int) * src->nb_sommets * src->nb_sommets);
    }

    // Copie de la matrice d'adjacence
    dest->m_adj = malloc(sizeof(int*) * src->nb_sommets);
    for (int i = 0; i < src->nb_sommets; i++) {
        dest->m_adj[i] = dest->m_stockage + i * src->nb_sommets;
    }

    // Copie des arêtes
    dest->aretes = malloc(sizeof(arete*) * src->nbaretes);
    for (int i = 0; i < src->nbaretes; i++) {
        dest->aretes[i] = malloc(sizeof(arete));
        *dest->aretes[i] = *src->aretes[i];
    }

    // Copie des solutions
    dest->solutions = malloc(sizeof(arete*) * src->nb_sommets);
    for (int i = 0; i < src->nb_sommets; i++) {
        dest->solutions[i] = malloc(sizeof(arete));
        *dest->solutions[i] = *src->solutions[i];
    }

    return dest;
}