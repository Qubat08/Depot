#include "graphe.h"

void initGraphe(graphe *g, char *nom_file)
{

    FILE *fichier;
    fichier = fopen(nom_file, "r");
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
        g->l_adj = (liste2C *)malloc(sizeof(liste2C *) * g->nb_sommets);
        for (i = 0; i < g->nb_sommets; i++)
        {
            initListe(&g->l_adj[i]);
        }
        i = 0;
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
                newAre->extremetite = j;
                newAre->origine = i;
                newAre->poids = k;
                g->aretes[cpt] = newAre; // insertion dans le tableau d'arrete
                g->nbaretes += 1;
                cpt++;

                g->m_stockage[i * g->nb_sommets + j] = k;
                cellule *c = (cellule *)malloc(sizeof(cellule));
                initCellule(c, j, k);

                inserer_liste(&g->l_adj[i], c);
                if (g->oriente == 0)
                {
                    g->m_stockage[j * g->nb_sommets + i] = 1;
                    cellule *d = (cellule *)malloc(sizeof(cellule));
                    initCellule(d, i, k);

                    inserer_liste(&g->l_adj[j], d);
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
arete **trier_aretes(graphe *g)
{
    arete **temp;
    for (int i = 1; i < g->nbaretes; i++)
    {
        arete *key = g->aretes[i];

        int j = i - 1;
        while (j >= 0 && g->aretes[j]->poids > key->poids)
        {
            g->aretes[j + 1] = g->aretes[j];
            j = j - 1;
        }

        g->aretes[j + 1] = key;
    }
    temp = g->aretes;
    return temp;
}

void afficherGraphe(graphe g)
{
    if (g.nb_sommets != 0)
    {
        printf("NB sommets : %d \n", g.nb_sommets);
        printf("Oriente: %d \n", g.oriente);
        printf("Value : %d \n", g.value);
        printf("Liste d'adjacences : \n");
        for (int i = 0; i < g.nb_sommets; i++)
        {
            printf("%d :", i);
            afficherListe(g.l_adj[i]);
        }
        printf("\nMatrice d'adjacences:\n");

        for (int i = 0; i < g.nb_sommets; i++)
        {
            for (int j = 0; j < g.nb_sommets; j++)
            {
                printf("%d ", g.m_stockage[i * g.nb_sommets + j]);
            }
            printf("\n");
        }
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

void detruireGraphe(graphe *g)
{
    g->nb_sommets = 0;
    g->oriente = 0;
    g->value = 0;
    free(g->m_stockage);
    for (int i = 0; i < g->nb_sommets; i++)
    {
        viderListe(&g->l_adj[i]);
    }

    free(g->aretes);
    free(g->l_adj);
    free(g->m_adj);
}

int getNbArretes(graphe g)
{
    return g.nbaretes;
}

arete **generer_acpm_kruskal_tableau(arete **a, int taille, int taille2)
{
    int cc[taille];
    int b = 0;
    int j = 0;
    int k = 0;
    int poids = 0;
    arete **tabArete = (arete **)malloc(sizeof(arete *) * taille);
    for (int i = 0; i < taille; i++)
    {
        cc[i] = i;
    }

    for (int j = 0; j < taille; j++)
    {
        if (cc[a[j]->origine] != cc[a[j]->extremetite])
        {
            tabArete[b] = a[j];
            poids += a[j]->poids;
            b++;
        }
        for (int l = 0; l < taille; l++)
        {
            if (cc[l] == a[j]->extremetite)
            {
                cc[l] = cc[a[j]->origine];
            }
        }
    }
    printf("Poids: %d \n ", poids);

    for (int i = 0; i < taille; i++)
    {
        afficherArete(tabArete[i]);
    }

    return tabArete;
}
