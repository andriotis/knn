#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "utils.h"
#include "quickselect.h"
#include "queue.h"

extern int n, d;
extern double tau;
extern double **points;
extern double *distances;
extern struct LinkedList *nearest;

void make(VPTree *node, int start, int end)
{
    node->idx = end;
    node->inner = node->outer = NULL;
    node->md = 0;

    if (start == end)
        return;

    for (int i = start; i < end; i++)
        distances[i] = euclidean_dist(points[i], points[node->idx]);

    double md = get_median(start, end);
    node->md = md;

    node->outer = malloc(sizeof(VPTree));
    make(node->outer, (start + end) / 2, end - 1);

    if ((start + end) / 2 - 1 < start)
        return;

    node->inner = malloc(sizeof(VPTree));
    make(node->inner, start, (start + end) / 2 - 1);
}

void search(VPTree *node, double *query, int k)
{
    if (node == NULL)
        return;

    double x = euclidean_dist(query, points[node->idx]);

    if (x < tau)
    {
        push(&nearest, node->idx, x);
        if (size(&nearest) > k)
            pop(&nearest);
        if (size(&nearest) == k)
            tau = peek(&nearest)->distance;
    }

    if (x < node->md)
    {
        if (x - tau <= node->md)
            search(node->inner, query, k);
        if (x + tau >= node->md)
            search(node->outer, query, k);
    }
    else
    {
        if (x + tau >= node->md)
            search(node->outer, query, k);
        if (x - tau <= node->md)
            search(node->inner, query, k);
    }
}