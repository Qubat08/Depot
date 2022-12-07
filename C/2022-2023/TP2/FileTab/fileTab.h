#ifndef __fileTab_TAB_H__
#define __fileTab_TAB_H__

typedef struct fileTab
{
    int *tab;
    int tete;
    int queue;
    int nbElement;
    int longueur;
} fileTab;

void initialiser_file(fileTab *file, int longueur);
void detruire_file(fileTab *file);
int file_vide(fileTab file);
int file_pleine(fileTab file);
void enfiler(fileTab *file, int element);
int defiler(fileTab *file);
void afficher_file(fileTab f);

#endif // __fileTab_TAB_H__