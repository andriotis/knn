#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "utils.h"

int n = 8;
int d = 2;
double **original_set;

VPTree *make_vp_tree(int *ids, int size)
{
    if (size == 0)
        return NULL;

    VPTree *node;
    node = (VPTree *)malloc(sizeof(VPTree));
    node->idx = ids[size - 1];

    double *distances = (double *)malloc((size - 1) * sizeof(double));
    double *distances_copy = (double *)malloc((size - 1) * sizeof(double));

    for (int i = 0; i < size - 1; i++)
    {
        double dist = euclidean_dist(original_set[ids[i]], original_set[ids[size - 1]]);
        distances[i] = dist;
        distances_copy[i] = dist;
    }

    node->md = get_median(distances_copy, size - 1);

    int *L = (int *)malloc((size - 1) * sizeof(int));
    int L_sz = 0;
    int *R = (int *)malloc((size - 1) * sizeof(int));
    int R_sz = 0;

    for (int i = 0; i < size - 1; i++)
    {
        if (distances[i] < node->md)
        {
            L[L_sz] = ids[i];
            L_sz++;
        }
        else
        {
            R[R_sz] = ids[i];
            R_sz++;
        }
    }

    L = (int *)realloc(L, L_sz * sizeof(int));
    R = (int *)realloc(R, R_sz * sizeof(int));

    node->inner = make_vp_tree(L, L_sz);
    node->outer = make_vp_tree(R, R_sz);

    return node;
}

int main()
{
    srand(42);

    original_set = (double **)malloc(n * sizeof(double *));
    int *original_ids = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        original_set[i] = (double *)malloc(d * sizeof(double));
        original_ids[i] = i;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            original_set[i][j] = (double)rand() / RAND_MAX;

    VPTree *root = make_vp_tree(original_ids, n);

    return 0;
}