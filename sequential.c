#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "utils.h"
#include "quickselect.h"
#include "queue.h"

extern int n, d, curr_k;
extern double tau, k_tau;
extern vp_best;
extern double **points;
extern double *distances;
extern double *query;
extern struct LinkedList *nearest;

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
    node->md = md;

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

void search(VPTree *node, int k)
{
    if (node == NULL)
        return;

    double x = euclidean_dist(query, points[node->idx]);

    if (x < k_tau)
    {
        push(&nearest, node->idx, x);
        curr_k++;
        if (curr_k > k)
        {
            pop(&nearest);
            curr_k--;
        }
        if (curr_k == k)
            k_tau = peek(&nearest)->distance;
    }

    if (x < node->md)
    {
        if (x - k_tau <= node->md)
            search(node->inner, k);
        if (x + k_tau >= node->md)
            search(node->outer, k);
    }
    else
    {
        if (x + k_tau >= node->md)
            search(node->outer, k);
        if (x - k_tau <= node->md)
            search(node->inner, k);
    }
}

// void search(VPTree *node)
// {
//     // printf("search tau = %f\n", tau);
//     if (node == NULL)
//         return;

//     double x = euclidean_dist(query, points[node->idx]);
//     if (x < tau)
//     {
//         tau = x;
//         vp_best = node->idx;
//     }

//     double middle = (node->L.high + node->R.low) / 2;

//     if (x < middle)
//     {
//         if (x > node->L.low - tau && x < node->L.high + tau)
//             search(node->inner);
//         if (x > node->R.low - tau && x < node->R.high + tau)
//             search(node->outer);
//     }
//     else
//     {
//         if (x > node->R.low - tau && x < node->R.high + tau)
//             search(node->outer);
//         if (x > node->L.low - tau && x < node->L.high + tau)
//             search(node->inner);
//     }
// }

// void k_search(VPTree *node, int k)
// {
//     if (node == NULL)
//         return;

//     double x = euclidean_dist(query, points[node->idx]);

//     if (x < k_tau)
//     {
//         push(&nearest, node->idx, x);
//         curr_k++;
//         if (curr_k > k)
//         {
//             pop(&nearest);
//             curr_k--;
//         }
//         if (curr_k == k)
//             k_tau = peek(&nearest)->distance;
//     }

//     double middle = (node->L.high + node->R.low) / 2;

//     if (x < middle)
//     {
//         if (x > node->L.low - k_tau && x < node->L.high + k_tau)
//             k_search(node->inner, k);
//         if (x > node->R.low - k_tau && x < node->R.high + k_tau)
//             k_search(node->outer, k);
//     }
//     else
//     {
//         if (x > node->R.low - k_tau && x < node->R.high + k_tau)
//             k_search(node->outer, k);
//         if (x > node->L.low - k_tau && x < node->L.high + k_tau)
//             k_search(node->inner, k);
//     }
// }
