#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int *a, *b, *c, *d, *e;
    int n, i = 0;
    int somme = 0, res = 0;

    printf("Saisir taille");
    scanf("%d", &n);

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));
    d = (int *)malloc(n * sizeof(int));
    e = (int *)malloc(n * sizeof(int));

    printf("Saisir valeur tableau a: \n");

    for (i = 0; i < n; i++)
    {
        scanf("\n%d", &a[i]);
    }

    printf("Saisir valeur tableau b: \n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &b[i]);
    }

    // Somme

    for (i = 0; i < n; i++)
    {
        c[i] = a[i] + b[i];
    }

    // soustraction
    for (i = 0; i < n; i++)
    {
        d[i] = a[i] - b[i];
    }
    // produit
    for (i = 0; i < n; i++)
    {
        e[i] = a[i] * b[i];
    }

    for (i = 0; i < n; i++)
    {
        res += a[i] * b[i];
    }

    printf("\nSomme 2 vecteurs: ");
    for (i = 0; i < n; i++)
    {
        printf("%d", c[i]);
    }
    printf("\nSoustraction 2 vecteurs: ");
    for (i = 0; i < n; i++)
    {
        printf("%d", d[i]);
    }

    printf("\nProduit 2 vecteurs: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", e[i]);
    }
    printf("\n Produit scalaire : %d", res);

    free(a);
    free(b);
    return 0;
}
