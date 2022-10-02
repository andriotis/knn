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

    VPTree *node = (VPTree *)malloc(sizeof(VPTree));

    node->idx = X.end;
    node->vp = points[X.end];

    calc_dist_seq(X);
    node->md = get_median(X);

    Set L = {X.start, (X.start + X.end) / 2 - 1};
    Set R = {(X.start + X.end) / 2, X.end - 1};

    node->inner = make_vp_tree(L);
    node->outer = make_vp_tree(R);
}