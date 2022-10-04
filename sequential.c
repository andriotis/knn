#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "utils.h"
#include "quickselect.h"

extern int n;
extern int d;

extern double **points;
extern double *distances;

void make_vp_tree(VPTree *node, Set X)
{
    node->idx = X.end;
    node->vp = points[X.end];
    node->md = 0;
    node->inner = node->outer = NULL;

    if (X.start == X.end)
        return;

    for (int i = X.start; i < X.end; i++)
        distances[i] = euclidean_dist(points[i], node->vp);

    node->md = get_median(X);

    Set L = {X.start, (X.start + X.end) / 2 - 1};
    Set R = {(X.start + X.end) / 2, X.end - 1};

    node->outer = (VPTree *)malloc(sizeof(VPTree));
    make_vp_tree(node->outer, R);

    if (L.end < L.start)
        return;

    node->inner = (VPTree *)malloc(sizeof(VPTree));
    make_vp_tree(node->inner, L);
}

extern double tau;
extern int best;

void search(VPTree *node, double *query)
{
    if (node == NULL)
        return;
    double x = euclidean_dist(query, node->vp);
    printf("query distance from current pivot is %f\n", x);
    if (x < tau)
    {
        tau = x;
        best = node->idx;
    }

    printf("tau is %f and best is %d\n", tau, best);
    printf("radius is %f\n", node->md);
    if (x > node->md)
        search(node->outer, query);
    else
        search(node->inner, query);
}