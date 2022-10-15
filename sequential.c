#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "structures.h"
#include "utils.h"
#include "queue.h"

// EXPERIMENT VARIABLES SHOULD BE GLOBAL
extern int n, d, k;
double **points;
double *query;
double *distances;
extern double tau;

// RUNTIME VARIABLES SHOULD BE LOCAL
struct LinkedList *nearest;

// CONSTRUCT VP-TREE AND SEARCH IN SEQUENCE
void make(VPTree *node, int start, int end)
{
    // initialize the node
    node->idx = end;
    node->inner = node->outer = NULL;
    node->md = 0;

    // base case
    if (start == end)
        return;

    // calculate all the set's distances
    for (int i = start; i < end; i++)
        distances[i] = euclidean_dist(points[i], points[node->idx]);

    // store median
    double md = get_median(start, end);
    node->md = md;

    // make the right child
    node->outer = malloc(sizeof(VPTree));
    make(node->outer, (start + end) / 2, end - 1);

    // additional check to reduce make calls
    if ((start + end) / 2 - 1 < start)
        return;

    // make the left child
    node->inner = malloc(sizeof(VPTree));
    make(node->inner, start, (start + end) / 2 - 1);
}

void search(VPTree *node, double *query)
{
    if (node == NULL)
        return;

    // calculate the distance from the query of the current vp
    double x = euclidean_dist(query, points[node->idx]);

    // add or remove the point according to priority
    if (x < tau)
    {
        push(&nearest, node->idx, x);
        if (size(&nearest) > k)
            pop(&nearest);
        if (size(&nearest) == k)
            tau = peek(&nearest)->distance;
    }
    // prioritize where to look
    if (x < node->md)
    {
        if (x - tau <= node->md)
            search(node->inner, query);
        if (x + tau >= node->md)
            search(node->outer, query);
    }
    else
    {
        if (x + tau >= node->md)
            search(node->outer, query);
        if (x - tau <= node->md)
            search(node->inner, query);
    }
}

// wrapper function for main
void run_sequential()
{
    VPTree *root = (VPTree *)malloc(sizeof(VPTree));
    nearest = newNode(-1, RAND_MAX);
    tau = RAND_MAX;

    make(root, 0, n - 1);
    clock_t start = clock();
    search(root, query);
    clock_t end = clock();
    printf("Sequential took : %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);
}