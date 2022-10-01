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

int main()
{

    // points = (double **)malloc(n * sizeof(double *));

    // for (int i = 0; i < n; i++)
    //     points[i] = (double *)malloc(d * sizeof(double));

    // srand(42);
    // for (int i = 0; i < n; i++)
    //     for (int j = 0; j < d; j++)
    //         points[i][j] = (double)rand() / RAND_MAX;

    // VPTree *root = (VPTree *)malloc(sizeof(VPTree));

    // Set S = {0, n - 1};

    // make_vp_tree(root, S);

    double *a = (double *)malloc(3 * sizeof(double));
    a[0] = 0.1;
    a[1] = 0.3;
    a[2] = 0.5;
    double b = get_median(a, 3);
    printf("%f\n", b);

    return 0;
}