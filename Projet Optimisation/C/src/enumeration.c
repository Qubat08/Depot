#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "enumeration.h"

void afficher_cycle_ham(int *t, int n, int longueur) {
	int i;

	printf("\nLongueur : %d | ", longueur);
	for (i = 0; i < n; i++)
		printf("%d ", t[i]);
	printf("\n");
}

void permuter(int *t, int i, int j) {
	int temp = t[i];
	t[i] = t[j];
	t[j] = temp;
}

void permutations_cycles(int *t, int i, int n, int longueur, int **m_adj, int *tab_min, int *min) {
	int j, fin = 0;

	if (i == n) {
		longueur += m_adj[t[n-1]][t[0]];
		afficher_cycle_ham(t, n, longueur);
		if (longueur < *min) {
			*min = longueur;
			for (j = 0; j < n; j++) {
				tab_min[j] = t[j];
			}
		}
	}
	else {
		j = i;
		while (!fin && j < n) {
			permuter(t, i, j);
			longueur += m_adj[t[i-1]][t[i]];
			permutations_cycles(t, i+1, n, longueur, m_adj, tab_min, min);
			longueur -= m_adj[t[i-1]][t[i]];
			permuter(t, i, j);
			if (t[1] == n - 1)
				fin = 1;
			j++;
		}

	}
}

void enum_cycles_ham(int n_sommets, int **m_adj) {
	int i;
	int *tab_sommets = malloc(sizeof(int) * n_sommets);
	int *tab_cycle_ham_min = malloc(sizeof(int) * n_sommets);
	int longueur = 0;
	int longueur_min = INT_MAX;

	for (i = 0; i < n_sommets; i++) {
		tab_sommets[i] = i;
		tab_cycle_ham_min[i] = 0;
	}
	permutations_cycles(tab_sommets, 1, n_sommets, longueur, m_adj, tab_cycle_ham_min, &longueur_min);
	printf("\nCycle hamiltorien minimum :\n");
	for (i = 0; i < n_sommets; i++)
		printf("%d ", tab_cycle_ham_min[i]);
	printf("\nLongueur : %d\n", longueur_min);

	free(tab_sommets);
	free(tab_cycle_ham_min);
}
