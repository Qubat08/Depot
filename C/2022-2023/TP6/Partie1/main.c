#include "liste/liste.h"

int lireFichier(liste2C *l, char *nomFichier)
{
    FILE *fichier;
    fichier = fopen(nomFichier, "r");

    char buffer[100];
    char temp[27];
    int test = 0;
    int total = 0;
    if (fichier != NULL)
    {
        do
        {

            if (strlen(buffer) < 27 && strlen(buffer) > 0)
            {
                if (strcmp(temp, buffer))
                {
                    strcpy(temp, buffer);
                    // printf("%s\n", temp);
                    inserer_liste(l, temp);
                    total += 1;
                }
            }
        } while (fscanf(fichier, "%s", buffer) != EOF);
    }
    return total;
}

int main(void)
{

    liste2C liste;
    initListe2C(&liste);
    int total = 0;

    // for (int i = 0; i < 5; i++)
    // {

    //     char val[27];
    //     printf("\nSaisir mot : ");
    //     scanf("%s", val);

    //     inserer_liste(&liste, val);
    //     afficherListe(liste);
    // }
    // afficherListe(liste);

    // supprimer_liste2C(&liste, liste_Rechercher(liste, "test"));

    // afficherListe(liste);

    total = lireFichier(&liste, "../histoire_quebec.txt");
    // afficherListe(liste);

    printf("Mot récupérés : %d\n", total);
    compterListe(liste);

    viderListe(&liste);

    return 0;
}