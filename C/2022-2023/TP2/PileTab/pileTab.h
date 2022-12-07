#ifndef __PILE_TAB_H__
#define __PILE_TAB_H__

typedef struct pileTab
{
    int *tab;
    int taille;
    int sommet;
} pileTab;

void initialiser_pile(pileTab *p, int taille);
void detruire_pile(pileTab *p);
int pile_pleine(pileTab p);
int pile_vide(pileTab p);
int sommet_pile(pileTab p);
void empiler(pileTab *p, int valeur);
int depiler(pileTab *p);
void afficher_pile(pileTab p);

#endif // __PILE_TAB_H__