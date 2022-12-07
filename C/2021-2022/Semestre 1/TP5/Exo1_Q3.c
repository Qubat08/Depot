#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, temp, i, cpt = 0, taille = 0, nb0 = 0, nb1 = 0;
    int *array;

    printf("Saisir nombre de convertir: ");
    scanf("%d", &n);
    temp = n;
    for (i = 0; temp > 0; i++)
    {
        temp = temp / 2;
        cpt++;
    }

    array = (int *)malloc(cpt * sizeof(int));

    for (i = cpt - 1; i >= 0; i--)
    {
        array[i] = n % 2;
        n = n / 2;
    }

    for (i = 0; i < cpt; i++)
    {

        printf("%d", array[i]);
    }
    for (i = 0; i < sizeof(array) / sizeof(int); i++)
    {
        if (array[i] == 1)
        {
            nb1++;
        }
        if (array[i] == 0)
        {
            nb0++;
        }
        taille++;
    }

    printf("\nTaille %d", taille);
    printf("\nNB 0 %d", nb0);
    printf("\nNB 1 %d", nb1);

    free(array);
    return 0;
}
