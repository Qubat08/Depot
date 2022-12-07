#include "fileTab.h"
#include <stdio.h>
#include <stdlib.h>

void initialiser_file(fileTab *file, int longueur)
{
    file->tab = (int *)malloc((longueur + 1) * sizeof(int));
    file->tete = 0;
    file->queue = 0;
    file->nbElement = 0;
    file->longueur = longueur;
}

void detruire_file(fileTab *file)
{
    file->tab = NULL;
    free(file->tab);
    file->tete = 0;
    file->queue = 0;
    file->nbElement = 0;
}

int file_vide(fileTab file)
{
    return file.tete == file.queue;
}

int file_pleine(fileTab f)
{
    return (f.queue == (f.tete - 1) || (f.tete == 0 && f.queue == f.longueur));
}

void enfiler(fileTab *file, int element)
{
    if (!file_pleine(*file))
    {
        file->tab[file->queue] = element;
        file->queue = (file->queue + 1) % (file->longueur + 1);
        file->nbElement++;
    }
    else
    {
        printf("File pleine\n");
        return;
    }
}

int defiler(fileTab *file)
{
    if (!file_vide(*file))
    {
        int element = file->tab[file->tete];
        file->tete = (file->tete + 1) % (file->longueur + 1);
        file->nbElement--;
        return element;
    }
    printf("File vide\n");
    return -1;
}

void afficher_file(fileTab f)
{
    printf("file : ");
    if (file_vide(f))
    {
        printf("vide\n");
        return;
    }
    int i = f.tete;
    while (i != f.queue)
    {
        printf("%d ", f.tab[i]);
        i = (i + 1) % (f.longueur + 1);
    }
    printf("\n");
}