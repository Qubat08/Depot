#include "graphe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void intisaliser_graphe(graphe *g, char *NomDuFichier)
{
    FILE *f = fopen(NomDuFichier, "r");
    if (f == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        exit(1);
    }
    char tmp[30];
    fscanf(f, "%s", tmp);
    fscanf(f, "%d", &(g->n_sommet));
    fscanf(f, "%s", tmp);
    fscanf(f, "%d", &(g->oriente));
    fscanf(f, "%s", tmp);
    fscanf(f, "%d", &(g->valeur));
    fscanf(f, "%s", tmp);
    g->liste_adj = (liste *)malloc(g->n_sommet * sizeof(liste));

    g->m_stockage = (int *)calloc((g->n_sommet * g->n_sommet), sizeof(int)); // pour stocker les valeurs de la matrices d'adjacence
    g->m_adj = (int **)malloc(g->n_sommet * sizeof(int *));                  // pour stocker les pointeurs de la matrices d'adjacence
    for (int i = 0; i < g->n_sommet; i++)
    {
        initialiser_liste(&(g->liste_adj[i]));
        g->m_adj[i] = &(g->m_stockage[i * g->n_sommet]);
    }

    strcpy(tmp, "0"); // tmp prend le char 0 pour rentrer dans la boucle while

    int nb1, nb2;

    while (!isalpha(*tmp))
    {
        fscanf(f, "%s", tmp);

        if (isalpha(*tmp)) // si on arrive a la fin on sort de la boucle
        {
            break;
        }

        nb1 = atoi(tmp);

        fscanf(f, "%d", &nb2);

        cellule *c1 = (cellule *)malloc(sizeof(cellule));
        cellule *c2 = (cellule *)malloc(sizeof(cellule));
        initialiser_cellule(c1, nb1);
        initialiser_cellule(c2, nb2);

        inserer(&(g->liste_adj[nb1]), c2);
        g->m_adj[nb1][nb2] = 1;

        if (g->oriente == 0) // si le graphe est orienté on insere dans les 2 sens
        {
            inserer(&(g->liste_adj[nb2]), c1);
            g->m_adj[nb2][nb1] = 1;
        }
    }
    fclose(f);
}

void afficher_graphe(graphe g)
{
    printf("Nombre de sommets : %d\n", g.n_sommet);
    printf("%s", g.oriente == 0 ? "Non oriente\n" : "Oriente\n");
    printf("%s", g.valeur == 0 ? "Non value\n" : "value\n");

    // affichage de la liste d'adjacence
    if (g.liste_adj != NULL)
    {
        printf("Listes d'adjacences :\n");
        for (int i = 0; i < g.n_sommet; i++)
        {
            printf("%d --> ", i);
            afficher_liste((g.liste_adj[i]));
        }
    }

    // affichage de la matrice d'adjacence
    if (g.m_stockage != NULL)
    {
        printf("\nMatrices d'adjacences :\n");
        for (int i = 0; i < g.n_sommet; i++)
        {

            for (int j = 0; j < g.n_sommet; j++)
            {
                printf("%d ", g.m_adj[i][j]);
            }
            printf("\n");
        }
    }
}

void detruire_graphe(graphe *g)
{
    for (int i = 0; i < g->n_sommet; i++)
    {
        detruire_liste(&(g->liste_adj[i]));
        detruire_sommet(&(g->tableau_sommet[i]));
    }
    g->liste_adj = NULL;
    free(g->liste_adj);
    *g->m_adj = NULL;
    free(*g->m_adj);
    g->m_stockage = NULL;
    free(g->m_stockage);

    g->tableau_sommet = NULL;
    free(g->tableau_sommet);
}

void parcours_largeur(graphe *g, int s)
{
    if (g->liste_adj == NULL)
    {
        printf("parcours_largeur : Le graphe n'a pas de liste d'adjacence\n");
        return;
    }

    g->tableau_sommet = (sommet *)malloc(g->n_sommet * sizeof(sommet));
    for (int i = 0; i < g->n_sommet; i++)
    {
        g->tableau_sommet[i] = *initialiser_sommet(i);
    }

    g->tableau_sommet[s].couleur = 2;

    // initialisation de la file
    fileTab f;
    initialiser_file(&f, g->n_sommet);

    enfiler(&f, s);

    cellule *actuel;
    while (!file_vide(f))
    {

        int valeur = defiler(&f);
        actuel = (g->liste_adj[valeur]).tete;
        while (actuel != NULL)
        {
            if (g->tableau_sommet[actuel->sommet].couleur == BLANC)
            {
                g->tableau_sommet[actuel->sommet].couleur = GRIS;
                g->tableau_sommet[actuel->sommet].pere = &(g->tableau_sommet[valeur]);
                g->tableau_sommet[actuel->sommet].distance = g->tableau_sommet[valeur].distance + 1;
                enfiler(&f, actuel->sommet);
            }
            actuel = actuel->succ;
        }
        g->tableau_sommet[valeur].couleur = NOIR;
    }
}

void afficher_chemin(graphe g, int s) // fonction de lancement de la fonction recursive pour l'affichage du parcours en largeur
{
    if (g.tableau_sommet == NULL)
    {
        printf("afficher_chemin : Le graphe n'a pas de tableau de sommet\n");
        return;
    }
    for (int i = 0; i < g.n_sommet; i++) // affiche toute les lignes pour chaque sommet
    {
        chemin_recursif(g, s, i);
        printf("\n");
    }
}

void chemin_recursif(graphe g, int s, int i) // fonction recursive pour afficher le chemin du parcours en largeur
{
    if (g.tableau_sommet[i].valeur == g.tableau_sommet[s].valeur) // si la valeur du sommet est egale a la valeur du sommet de depart
    {
        printf("%d ", g.tableau_sommet[i].valeur);
    }
    else if (g.tableau_sommet[i].pere == NULL) // si le pere n'existe pas c'est un graphe non connexe
    {
        printf("Pas de chemin du sommet %d au sommet %d", s, i);
    }
    else // sinon on affiche tout les pères de la valeur
    {
        chemin_recursif(g, s, g.tableau_sommet[i].pere->valeur);
        printf("%d ", g.tableau_sommet[i].valeur);
    }
}

void information_sommet(graphe g)
{
    if (g.tableau_sommet == NULL)
    {
        printf("information_sommet : Le graphe n'a pas de tableau de sommet\n");
        return;
    }
    printf("\nInformation sur les sommets :\n");
    for (int i = 0; i < g.n_sommet; i++)
    {
        if (g.tableau_sommet[i].pere != NULL)
        {
            printf("Sommet[%d] : Predecesseur = %d , distance = %d \n", i, g.tableau_sommet[i].pere->valeur, g.tableau_sommet[i].distance);
        }
        else
        {
            printf("Sommet[%d] : Predecesseur = NULL , distance = %d \n", i, g.tableau_sommet[i].distance);
        }
    }
}

// debut

int DATE_REC = 0;
int DATE_ITT = 0;
void parcours_profondeur(graphe *g, int s)
{
    if (g->liste_adj == NULL)
    {
        printf("parcours_profondeur : Le graphe n'a pas de liste d'adjacence\n");
        return;
    }
    g->tableau_sommet = (sommet *)malloc(g->n_sommet * sizeof(sommet));
    for (int i = 0; i < g->n_sommet; i++)
    {
        g->tableau_sommet[i] = *initialiser_sommet(i);
    }

    for (int i = s, compteur = 0; compteur < g->n_sommet; i++, compteur++)
    {
        i %= g->n_sommet;
        parcours_profondeur_recursif(g, &g->tableau_sommet[i]);
    }
}

void parcours_profondeur_recursif(graphe *g, sommet *s)
{

    if (s->couleur == BLANC)
    {
        printf("%d ", s->valeur);
        s->couleur = GRIS;
        DATE_REC++;
        s->d = DATE_REC;
        cellule *actuel;
        actuel = (g->liste_adj[s->valeur]).tete;
        while (actuel != NULL)
        {
            if (g->tableau_sommet[actuel->sommet].couleur == BLANC)
            {
                // g->tableau_sommet[actuel->sommet].pere = s->valeur;
                g->tableau_sommet[actuel->sommet].pere = &(g->tableau_sommet[s->valeur]);
                parcours_profondeur_recursif(g, &g->tableau_sommet[actuel->sommet]);
            }

            actuel = actuel->succ;
        }
        s->couleur = NOIR;
        DATE_REC++;
        s->f = DATE_REC;
    }
}

void afficher_parcours_profondeur(graphe g) // fonction de lancement de la fonction recursive pour l'affichage du parcours en profondeur
{
    if (g.tableau_sommet == NULL)
    {
        printf("afficher_parcours_profondeur : Le graphe n'a pas de tableau de sommet\n");
        return;
    }
    printf("\nInformation sur les sommets :\n");
    for (int i = 0; i < g.n_sommet; i++)
    {
        if (g.tableau_sommet[i].pere != NULL)
        {
            printf("Sommet[%d] : Date de debut = %d , Date de fin = %d , Pere = %d\n", i, g.tableau_sommet[i].d, g.tableau_sommet[i].f, g.tableau_sommet[i].pere->valeur);
        }
        else
        {
            printf("Sommet[%d] : Date de debut = %d , Date de fin = %d , Pere = NULL\n", i, g.tableau_sommet[i].d, g.tableau_sommet[i].f);
        }
    }
}

void parcours_profondeur_iteratif(graphe *g, int i)
{
    if (g->liste_adj == NULL)
    {
        printf("parcours_profondeur_iteratif : Le graphe n'a pas de liste d'adjacence\n");
        return;
    }
    g->tableau_sommet = (sommet *)malloc(g->n_sommet * sizeof(sommet));
    for (int i = 0; i < g->n_sommet; i++) // on initialise tout les sommets
    {
        g->tableau_sommet[i] = *initialiser_sommet(i);
    }

    for (int s = i, compteur = 0; compteur < g->n_sommet; s++, compteur++) // on parcours tout les sommets
    {
        s %= g->n_sommet;
        if (g->tableau_sommet[s].couleur == BLANC) // si le sommet n'est pas parcouru on le parcours
        {
            g->tableau_sommet[s].couleur = GRIS; // le premier sommet est parcourue
            DATE_ITT++;
            g->tableau_sommet[s].d = DATE_ITT;
            // initialisation de la pile
            pileTab *p = (pileTab *)malloc(sizeof(pileTab));
            initialiser_pile(p, g->n_sommet);

            empiler(p, s);
            printf("%d ", s);
            cellule *actuel = (cellule *)malloc(sizeof(cellule));

            while (!pile_vide(*p)) // tant que la pile n'est pas vide le parcours continue
            {
                int valeur = sommet_pile(*p);
                actuel = (g->liste_adj[valeur]).tete; // actuel prend la tete de la liste d'adjacence
                while (actuel != NULL)                // tant que tout les elements de la liste d'adjacence ne sont pas parcourue on continue
                {
                    if (g->tableau_sommet[actuel->sommet].couleur == BLANC) // si le sommet n'a pas été parcouru
                    {
                        g->tableau_sommet[actuel->sommet].couleur = GRIS;
                        DATE_ITT++;
                        g->tableau_sommet[actuel->sommet].d = DATE_ITT;
                        g->tableau_sommet[actuel->sommet].pere = &(g->tableau_sommet[valeur]);

                        printf("%d ", actuel->sommet);

                        empiler(p, actuel->sommet);
                        valeur = sommet_pile(*p);
                        actuel = (g->liste_adj[valeur]).tete;
                    }
                    else
                    {
                        actuel = actuel->succ;
                    }
                }

                g->tableau_sommet[valeur].couleur = NOIR; // une fois que le parcours du sommet est terminé on change la couleur
                DATE_ITT++;
                g->tableau_sommet[valeur].f = DATE_ITT;
                depiler(p); // on depile tout a la fin
            }
        }
    }
}