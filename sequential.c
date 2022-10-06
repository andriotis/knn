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

    double R_min = RAND_MAX;
    double R_max = -RAND_MAX;

    double current_distance;
    for (int i = (X.start + X.end) / 2; i < X.end; i++)
    {
        current_distance = distances[i];
        if (current_distance < R_min)
            R_min = current_distance;
        if (current_distance > R_max)
            R_max = current_distance;
    }

    Set R = {
        (X.start + X.end) / 2,
        X.end - 1,
        R_min,
        R_max};
    node->R = R;
    node->outer = (VPTree *)malloc(sizeof(VPTree));

    make_vp_tree(node->outer, node->R);

    if ((X.start + X.end) / 2 - 1 < X.start)
        return;

    double L_min = RAND_MAX;
    double L_max = -RAND_MAX;
    for (int i = X.start; i < (X.start + X.end) / 2; i++)
    {
        if (distances[i] < L_min)
            L_min = distances[i];
        if (distances[i] > L_max)
            L_max = distances[i];
    }

    Set L = {
        X.start,
        (X.start + X.end) / 2 - 1,
        L_min,
        L_max};
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