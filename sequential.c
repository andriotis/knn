#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "utils.h"

extern int n;
extern int d;
extern double **points;

VPTree *make_vp_tree(Set *X)
{

    if (X->size == 0)
        return NULL;

    VPTree *node;
    node = (VPTree *)malloc(sizeof(VPTree));
    node->idx = X->ids[X->size - 1];

    double *distances = (double *)malloc((X->size - 1) * sizeof(double));
    double *distances_copy = (double *)malloc((X->size - 1) * sizeof(double));

    for (int i = 0; i < X->size - 1; i++)
    {
        double dist = euclidean_dist(points[X->ids[i]],
                                     points[X->ids[X->size - 1]]);
        distances[i] = dist;
        distances_copy[i] = dist;
    }

    node->md = get_median(distances_copy, X->size - 1);

    Set *L = (Set *)malloc(sizeof(Set));
    L->ids = (int *)malloc((X->size - 1) * sizeof(int));
    L->size = 0;
    Set *R = (Set *)malloc(sizeof(Set));
    R->ids = (int *)malloc((X->size - 1) * sizeof(int));
    R->size = 0;

    for (int i = 0; i < X->size - 1; i++)
    {
        if (distances[i] < node->md)
        {
            L->ids[L->size] = X->ids[i];
            L->size++;
        }
        else
        {
            R->ids[R->size] = X->ids[i];
            R->size++;
        }
    }

    L->ids = (int *)realloc(L->ids, L->size * sizeof(int));
    R->ids = (int *)realloc(R->ids, R->size * sizeof(int));

    node->inner = make_vp_tree(L);
    node->outer = make_vp_tree(R);

    return node;
}