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
extern double *query;

extern double tau;
extern int vp_best;

void make_vp_tree(VPTree *node, Set X)
{
    node->idx = X.end;
    node->inner = node->outer = NULL;
    node->S.start = X.start;
    node->S.end = X.end - 1;

    if (X.start == X.end)
        return;

    for (int i = X.start; i < X.end; i++)
        distances[i] = euclidean_dist(points[i], points[node->idx]);

    double md = get_median(X);

    Set R = {(X.start + X.end) / 2,
             X.end - 1,
             quickselect(R.start, R.end, 1),
             quickselect(R.start, R.end, R.end - R.start + 1)};
    node->R = R;
    node->outer = (VPTree *)malloc(sizeof(VPTree));
    make_vp_tree(node->outer, node->R);

    Set L = {X.start,
             (X.start + X.end) / 2 - 1,
             quickselect(L.start, L.end, 1),
             quickselect(L.start, L.end, L.end - L.start + 1)};

    if (L.end < L.start)
        return;

    node->L = L;
    node->inner = (VPTree *)malloc(sizeof(VPTree));
    make_vp_tree(node->inner, node->L);
}

void search(VPTree *node)
{
    if (node == NULL)
        return;

    double x = euclidean_dist(query, points[node->idx]);
    if (x < tau)
    {
        tau = x;
        vp_best = node->idx;
    }

    double middle = (node->L.high + node->R.low) / 2;

    if (x < middle)
    {
        if (x > node->L.low - tau && x < node->L.high + tau)
            search(node->inner);
        if (x > node->R.low - tau && x < node->R.high + tau)
            search(node->outer);
    }
    else
    {
        if (x > node->R.low - tau && x < node->R.high + tau)
            search(node->outer);
        if (x > node->L.low - tau && x < node->L.high + tau)
            search(node->inner);
    }
}