#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int n, i = 0, SManhattan = 0, DEuclidienne = 0, DMinkowski = 0, p = 0, temp, max = -1;
    int *a, *b;
    double res, g, res1;

    printf("Saisir n \n");
    scanf("%d", &n);

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));

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

    // Somme Manhattan

    for (i = 0; i < n; i++)
    {
        SManhattan = SManhattan + abs(a[i] - b[i]);
    }

    // distance Euclidienne
    for (i = 0; i < n; i++)
    {
        DEuclidienne = DEuclidienne + a[i] * a[i] - 2 * a[i] * b[i] + b[i] * b[i];
    }

    res1 = sqrt(DEuclidienne);

    // Distance Minkowski
    printf("Saisir valeur p:");
    scanf("%d", &p);
    for (i = 0; i < n; i++)
    {
        DMinkowski = DMinkowski + pow(a[i] - b[i], p);
    }

    g = (double)1 / p;
    res = pow(DMinkowski, g);

    // Distance Tchebychev
    for (i = 0; i < n; i++)
    {
        if (max < abs(a[i] - b[i]))
        {
            max = abs(a[i] - b[i]);
        }
    }

    printf("\nResultat Somme Manhattan: %d", SManhattan);
    printf("\nDistance Euclidienne: %.2lf", res1);
    printf("\nDistance Minjowski: %.2lf", res);
    printf("\nDistance Tchebychev: %d", max);
    free(a);
    free(b);
    return 0;
}
