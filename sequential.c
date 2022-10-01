#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "utils.h"
#include "quickselect.h"

extern int n;
extern int d;
extern double **points;
extern double *distances;

VPTree *make_vp_tree(Set X)
{
    if (X.end < X.start)
        return NULL;
    printf("%d,%d\n", X.start, X.end);
    VPTree *node = (VPTree *)malloc(sizeof(VPTree));

    node->idx = X.end;
    node->vp = points[X.end];

    for (int i = X.start; i < X.end; i++)
        distances[i] = euclidean_dist(points[i], points[X.end]);

    node->md = get_median(X);
    // Set to split in L and R
    Set S = {X.start, X.end - 1};
    int set_size = S.end - S.start + 1;

    // Find inner set's bounds
    Set L = {S.start, S.start + (set_size / 2) - 1};

    // Find outer set's bounds
    Set R = {L.end + 1, S.end};

    node->inner = make_vp_tree(L);
    node->outer = make_vp_tree(R);
    return node;
}