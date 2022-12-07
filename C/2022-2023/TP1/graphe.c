#include "graphe.h"

void initGraphe(graphe* g, char* nom_file){
    FILE* fichier;
    fichier = fopen(nom_file, "r");
    char str1[20];
    char ch_temp[20];
    int test=0;
    int i=0,j=0;

    if (fichier != NULL){
        fscanf(fichier,"%s %d", ch_temp, &g->nb_sommets);
        fscanf(fichier,"%s %d", ch_temp, &g->oriente);
        fscanf(fichier,"%s %d", ch_temp, &g->value);

        g->m_stockage = (int*)malloc(sizeof(int)*g->nb_sommets*g->nb_sommets);
        g->m_adj = (int**)malloc(sizeof(int*)*g->nb_sommets);
        for (int i = 0 ; i< g->nb_sommets; i++){
            g->m_adj[i] = &g->m_stockage[i*g->nb_sommets];
        }

        g->l_adj = (liste2C*)malloc(sizeof(liste2C*)*g->nb_sommets);
        for (i=0;i<g->nb_sommets;i++){
            initListe(&g->l_adj[i]);
        }
        i = 0;
        fscanf(fichier, "%s", ch_temp);  /*DEBUT_DEF_ARETES */

        do{
            fscanf(fichier, "%s",ch_temp);
            if (strcmp(ch_temp,"FIN_DEF_ARETES")){
                i = atoi(ch_temp);
                fscanf(fichier,"%d",&j);

                g->m_stockage[i*g->nb_sommets+j] = 1;
                cellule* c = (cellule*)malloc(sizeof(cellule));
                initCellule(c,j);
                inserer_liste(&g->l_adj[i],c);
                if (g->oriente == 0){
                    g->m_stockage[j*g->nb_sommets+i] = 1;
                    cellule* d = (cellule*)malloc(sizeof(cellule));
                    initCellule(d,i);
                    inserer_liste(&g->l_adj[j],d);
                }
            }
            else{
                test = 1;
            }
        } while(test == 0);
    }
    fclose(fichier);
}

void afficherGraphe(graphe g){
    if (g.nb_sommets != 0){
        printf("NB sommets : %d \n",g.nb_sommets);
        printf("Oriente: %d \n",g.oriente);
        printf("Value : %d \n",g.value);
        printf("Liste d'adjacences : \n");
        for (int i=0; i< g.nb_sommets; i++){
            printf("%d :",i);
            afficherListe(g.l_adj[i]);
            
        }
        printf("\nMatrice d'adjacences:\n");

        for (int i=0;i<g.nb_sommets;i++){
            for (int j = 0; j<g.nb_sommets; j++){
                printf("%d ",g.m_stockage[i*g.nb_sommets +j]);
            }
            printf("\n");
        }
    }
    else{
        printf("\nGraphe Vide \n");
    }

}

void detruireGraphe(graphe* g){
    g->nb_sommets = 0;
    g->oriente = 0;
    g->value =0;
    free(g->m_stockage);
    for (int i =0; i<g->nb_sommets;i++){
        viderListe(&g->l_adj[i]);
    }
    free(g->l_adj);
    free(g->m_adj);
}