#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "utils.h"

int n = 7;
int d = 2;

VPTree *make_vp_tree(double **original_set, int *ids, int size)
{
    printf("Call start with size : %d\n", size);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", ids[i]);
        for (int j = 0; j < d; j++)
            printf("%f ", original_set[ids[i]][j]);
        printf("\n");
    }

    if (size == 0)
    {
        printf("empty set\n");
        return EXIT_SUCCESS;
    }

    VPTree *node;
    node = (VPTree *)malloc(sizeof(VPTree));
    node->idx = ids[size - 1];
    if (size == 1)
    {
        printf("set with one point\n");
        node->md = 0;
        node->inner = NULL;
        node->outer = NULL;
        return node;
    }

    double *distances = (double *)malloc((size - 1) * sizeof(double));
    double *distances_copy = (double *)malloc((size - 1) * sizeof(double));

    for (int i = 0; i < size - 1; i++)
    {
        double dist = euclidean_dist(original_set[ids[i]], original_set[node->idx]);
        printf("euclidean_dist result: %f\n", dist);
        distances[i] = dist;
        distances_copy[i] = dist;
    }

    printf("Distances: ");
    for (int i = 0; i < size - 1; i++)
        printf("%f ", distances[i]);
    printf("\n");

    if (size - 1 > 1)
        node->md = get_median(distances_copy, size - 1);
    else
    {
        node->md = distances_copy[0];
    }

    printf("median : %f\n", node->md);
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

    printf("inner: ");
    for (int i = 0; i < L_sz; i++)
        printf("%d ", L[i]);
    printf("\n");

    printf("outer: ");
    for (int i = 0; i < R_sz; i++)
        printf("%d ", R[i]);
    printf("\n");

    printf("going into inner..\n");
    node->inner = make_vp_tree(original_set, L, L_sz);
    printf("going into outer..\n");
    node->outer = make_vp_tree(original_set, R, R_sz);

    return node;
}

int main()
{
    srand(42);
    double **S;
    S = (double **)malloc(n * sizeof(double *));
    int *ids = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        S[i] = (double *)malloc(d * sizeof(double));
        ids[i] = i;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            S[i][j] = (double)rand() / RAND_MAX;

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < d; j++)
    //         printf("%f ", S[i][j]);
    //     printf("\n");
    // }

    VPTree *root = make_vp_tree(S, ids, n);
    return 0;
}