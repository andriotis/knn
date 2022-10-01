#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sequential.h"
#include <time.h>
#include "utils.h"

int n = 8;
int d = 2;
int t = 10;

double **points;
double *distances;

int main()
{
    srand(42);

    points = (double **)malloc(n * sizeof(double *));
    distances = (double *)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
        points[i] = (double *)malloc(d * sizeof(double));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            points[i][j] = (double)rand() / RAND_MAX;

    VPTree *root = (VPTree *)malloc(sizeof(VPTree));

    Set S = {0, n - 1};
    clock_t t;
    t = clock();
    root = make_vp_tree(S);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("%f\n", time_taken);

    // double *a = (double *)malloc(3 * sizeof(double));
    // a[0] = 0.1;
    // a[1] = 0.3;
    // a[2] = 0.5;
    // double b = get_median(a, 3);
    // printf("%f\n", b);

    return 0;
}