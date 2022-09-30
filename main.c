#include <stdlib.h>
#include "parallel.h"
#include <time.h>
#include <stdio.h>

int n = 1000;
int d = 5;
int t = 10;

double **points;

int main()
{
    srand(42);

    points = (double **)malloc(n * sizeof(double *));
    Set *S = (Set *)malloc(sizeof(Set));
    S->ids = (int *)malloc(n * sizeof(int));
    S->size = n;

    for (int i = 0; i < n; i++)
    {
        points[i] = (double *)malloc(d * sizeof(double));
        S->ids[i] = i;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            points[i][j] = (double)rand() / RAND_MAX;

    clock_t begin = clock();
    VPTree *root = make_vp_tree(S);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);

    return 0;
}