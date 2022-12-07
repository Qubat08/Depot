#include "table_de_hachage.h"

void initialiser_TH(TH *tab)
{
    for (int i = 0; i < MAX; i++)
    {
        initListe2C((&((*tab)[i])));
    }
}

void detruire_TH(TH *tab)
{
    for (int i = 0; i < MAX; i++)
    {
        viderListe((&((*tab)[i])));
    }
}

void afficher_TH(TH tab)
{
    for (int i = 0; i < MAX; i++)
    {
        printf("%d: ", i);
        afficherListe(tab[i]);
        printf("\n");
    }
    printf("\n");
}

unsigned long long convertir_ch_long(char *s)
{
    unsigned long long k = 0;
    int puiss = 1;
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        k = k + puiss * s[i];
        puiss = puiss * 128;
    }

    return k;
}
int hachage(unsigned long long x)
{
    return x % (MAX - 1);
}

void inserer_TH(TH *tab, cellule *c)
{
    unsigned long long k = convertir_ch_long(c->valeur);
    inserer_liste((&(*tab)[hachage(k)]), c->valeur);
}

cellule *rechercher_hachage(char *s, TH tab)
{
    unsigned long long k = convertir_ch_long(s);
    return liste_Rechercher(tab[hachage(k)], s);
}

void supprimer_hachage(cellule *c, TH *tab)
{
    if (c != NULL)
    {
        unsigned long long k = convertir_ch_long(c->valeur);
        supprimer_liste2C(tab[hachage(k)], c);
    }
}

int compter_TH(TH tab)
{
    int total = 0;
    for (int i = 0; i < MAX; i++)
    {
        total += compterListe(tab[i]);
    }
    return total;
}
