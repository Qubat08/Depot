#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, temp, i, cpt;
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
    return 0;
}
